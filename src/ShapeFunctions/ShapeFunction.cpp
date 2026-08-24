#include "ShapeFunctions/ShapeFunction.h"

#include <stdexcept>

int LineShapeFunction::num_nodes() const
{
    return 2;
}
// 一次 Lagrange 多项式
double LineShapeFunction::value(int i, double xi, double) const
{
    if (i == 0)
        return 0.5 * (1.0 - xi);
    if (i == 1)
        return 0.5 * (1.0 + xi);
    throw std::invalid_argument("Invalid node index for line shape function.");
}

std::array<double, 2> LineShapeFunction::derivative(int i, double, double) const
{
    if (i == 0)
        return {-0.5, 0.0};
    if (i == 1)
        return {0.5, 0.0};
    throw std::invalid_argument("Invalid node index for line shape function.");
}

int TriangleShapeFunction::num_nodes() const
{
    return 3;
}
// 参考三角形上的线性 Lagrange 函数, 也就是面积坐标
double TriangleShapeFunction::value(int i, double xi, double eta) const
{
    if (i == 0)
        return 1.0 - xi - eta;
    if (i == 1)
        return xi;
    if (i == 2)
        return eta;
    throw std::invalid_argument("Invalid node index for triangle shape function.");
}

std::array<double, 2> TriangleShapeFunction::derivative(int i, double, double) const
{
    if (i == 0)
        return {-1.0, -1.0};
    if (i == 1)
        return {1.0, 0.0};
    if (i == 2)
        return {0.0, 1.0};
    throw std::invalid_argument("Invalid node index for triangle shape function.");
}

int QuadrilateralShapeFunction::num_nodes() const
{
    return 4;
}
// 1D Lagrange 函数的张量积，形成双线性形函数
double QuadrilateralShapeFunction::value(int i, double xi, double eta) const
{
    static constexpr double xi_node[4] = {-1.0, 1.0, 1.0, -1.0};
    static constexpr double eta_node[4] = {-1.0, -1.0, 1.0, 1.0};

    if (i < 0 || i >= 4)
        throw std::invalid_argument("Invalid node index for quadrilateral shape function.");

    return 0.25 * (1.0 + xi_node[i] * xi) * (1.0 + eta_node[i] * eta);
}

std::array<double, 2> QuadrilateralShapeFunction::derivative(int i, double xi, double eta) const
{
    static constexpr double xi_node[4] = {-1.0, 1.0, 1.0, -1.0};
    static constexpr double eta_node[4] = {-1.0, -1.0, 1.0, 1.0};

    if (i < 0 || i >= 4)
        throw std::invalid_argument("Invalid node index for quadrilateral shape function.");

    return {
        0.25 * xi_node[i] * (1.0 + eta_node[i] * eta),
        0.25 * eta_node[i] * (1.0 + xi_node[i] * xi)
    };
}
