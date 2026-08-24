#include "Physics/Physics.h"

double PoissonPhysics::diffusivity(double, double) const
{
    return 1.0;
}

double PoissonPhysics::source(double, double) const
{
    return 1.0;
}
