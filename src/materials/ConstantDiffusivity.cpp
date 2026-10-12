#include "materials/ConstantDiffusivity.h"

ConstantDiffusivity::ConstantDiffusivity(double value) : value_(value) {}

double ConstantDiffusivity::diffusivity(double, double) const
{
    return value_;
}
