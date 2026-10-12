#pragma once

#include <functional>
#include "Common.h"

class Material;

// Linear weak form: integral(k grad(N_i).grad(N_j)) = integral(f N_i).
// The material must outlive this kernel. Source is problem data, not material.
class PoissonKernel
{
public:
    using Source = std::function<double(double, double)>;
    explicit PoissonKernel(const Material& material,
                           Source source = [](double, double) { return 1.0; });
    void add_contribution(double x, double y, const Vector& values,
                          const std::vector<Node2D>& gradients, double weight,
                          Matrix& stiffness, Vector& load) const;
private:
    const Material& material_;
    Source source_;
};
