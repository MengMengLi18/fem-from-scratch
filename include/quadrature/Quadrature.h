#pragma once

#include <vector>

#include "Common.h"

struct QuadraturePoint
{
    double xi;
    double eta;
    double weight;
};

class Quadrature
{
public:
    virtual ~Quadrature() = default;
    virtual std::vector<QuadraturePoint> points() const = 0;
};

class LineQuadrature : public Quadrature
{
public:
    std::vector<QuadraturePoint> points() const override;
};

class TriangleQuadrature : public Quadrature
{
public:
    std::vector<QuadraturePoint> points() const override;
};

class QuadrilateralQuadrature : public Quadrature
{
public:
    std::vector<QuadraturePoint> points() const override;
};
