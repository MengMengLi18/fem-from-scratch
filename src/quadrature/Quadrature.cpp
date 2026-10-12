#include "quadrature/Quadrature.h"

#include <cmath>

std::vector<QuadraturePoint> LineQuadrature::points() const
{
    const double a = 1.0 / std::sqrt(3.0);
    return {
        {-a, 0.0, 1.0},
        {a, 0.0, 1.0}
    };
}

std::vector<QuadraturePoint> TriangleQuadrature::points() const
{
    return {
        {1.0 / 3.0, 1.0 / 3.0, 0.5}
    };
}

std::vector<QuadraturePoint> QuadrilateralQuadrature::points() const
{
    const double a = 1.0 / std::sqrt(3.0);
    return {
        {-a, -a, 1.0},
        {a, -a, 1.0},
        {a, a, 1.0},
        {-a, a, 1.0}
    };
}
