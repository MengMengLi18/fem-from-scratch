#include "kernels/PoissonKernel.h"

#include <utility>
#include "materials/Material.h"

PoissonKernel::PoissonKernel(const Material& material, Source source)
    : material_(material), source_(std::move(source)) {}

void PoissonKernel::add_contribution(
    double x, double y, const Vector& values,
    const std::vector<Node2D>& gradients, double weight,
    Matrix& stiffness, Vector& load) const
{
    const double k = material_.diffusivity(x, y);
    const double f = source_(x, y);
    for (std::size_t i = 0; i < values.size(); ++i)
    {
        load[i] += f * values[i] * weight;
        for (std::size_t j = 0; j < values.size(); ++j)
            stiffness[i][j] += k * (gradients[i][0] * gradients[j][0]
                                   + gradients[i][1] * gradients[j][1]) * weight;
    }
}
