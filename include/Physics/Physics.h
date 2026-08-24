#pragma once

#include "Common.h"

class Physics
{
public:
    virtual double diffusivity(double x, double y) const = 0;
    virtual double source(double x, double y) const = 0;
    virtual ~Physics() = default;
};

class PoissonPhysics : public Physics
{
public:
    double diffusivity(double x, double y) const override;
    double source(double x, double y) const override;
};
