#pragma once

#include <array>

#include "Common.h"

class ShapeFunction
{
public:
// 造函数 ShapeFunction()：对象出生时做什么
// 析构函数 ~ShapeFunction()：对象销毁时做什么

    virtual ~ShapeFunction() = default;   // 析构函数, ~ 表示析构函数它在这个对象销毁时自动调用

    virtual int num_nodes() const = 0;
    virtual double value(int i, double xi, double eta = 0.0) const = 0;
    virtual std::array<double, 2> derivative(int i, double xi, double eta = 0.0) const = 0;
};

class LineShapeFunction : public ShapeFunction
{
public:
    int num_nodes() const override;
    double value(int i, double xi, double eta = 0.0) const override;
    std::array<double, 2> derivative(int i, double xi, double eta = 0.0) const override;
};

class TriangleShapeFunction : public ShapeFunction
{
public:
    int num_nodes() const override;
    double value(int i, double xi, double eta = 0.0) const override;
    std::array<double, 2> derivative(int i, double xi, double eta = 0.0) const override;
};

class QuadrilateralShapeFunction : public ShapeFunction
{
public:
    int num_nodes() const override;
    double value(int i, double xi, double eta = 0.0) const override;
    std::array<double, 2> derivative(int i, double xi, double eta = 0.0) const override;
};
