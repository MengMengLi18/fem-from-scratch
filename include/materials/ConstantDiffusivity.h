#pragma once

#include "materials/Material.h"

class ConstantDiffusivity : public Material
{
public:
    explicit ConstantDiffusivity(double value = 1.0);
    double diffusivity(double x, double y) const override;

private:
    double value_;
};
