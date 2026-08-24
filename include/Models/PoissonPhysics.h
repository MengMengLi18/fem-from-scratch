#pragma once

#include "Physics/Physics.h"

class PoissonPhysics : public Physics
{
public:
    double diffusivity(double x, double y) const override;
    double source(double x, double y) const override;
};
