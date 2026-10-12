#pragma once

// Material supplies physical coefficients; weak forms belong to kernels.
class Material
{
public:
    virtual double diffusivity(double x, double y) const = 0;
    virtual ~Material() = default;
};
