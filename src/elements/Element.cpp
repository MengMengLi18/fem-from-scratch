#include "elements/Element.h"

#include <cmath>
#include <stdexcept>

#include "mesh/Mesh.h"
#include "kernels/PoissonKernel.h"
#include "quadrature/Quadrature.h"
#include "elements/ShapeFunction.h"

int LineElement::num_nodes() const
{
    return 2;
}

void LineElement::compute(const Mesh& mesh,
                          int element_index,
                          const PoissonKernel& kernel)
{
    constexpr int n = 2;
    Ke = Matrix(n, Vector(n, 0.0));
    Fe = Vector(n, 0.0);

    if (mesh.elements[element_index].size() != n)
        throw std::invalid_argument("Line element requires exactly 2 nodes.");

    const int node0 = mesh.elements[element_index][0];
    const int node1 = mesh.elements[element_index][1];
    const double x0 = mesh.nodes[node0][0];
    const double x1 = mesh.nodes[node1][0];
    const double J = (x1 - x0) / 2.0;

    if (std::abs(J) < 1e-14)
        throw std::runtime_error("Degenerate line element.");

    LineShapeFunction shape;
    LineQuadrature quadrature;

    for (const QuadraturePoint& gp : quadrature.points())
    {
        double N[n];
        double dNdx[n];
        // get the shape function values at the quadrature point
        for (int i = 0; i < n; ++i)
        {
            N[i] = shape.value(i, gp.xi);
            const double dNdxi = shape.derivative(i, gp.xi)[0];
            dNdx[i] = dNdxi / J;
        }
        // mapping from reference element to physical element
        const double x = N[0] * x0 + N[1] * x1;
        std::vector<Node2D> gradients(n);
        for (int i = 0; i < n; ++i)
            gradients[i] = {dNdx[i], 0.0};
        kernel.add_contribution(x, 0.0, Vector(N, N + n), gradients,
                                gp.weight * J, Ke, Fe);
    }
}

int TriangleElement::num_nodes() const
{
    return 3;
}

void TriangleElement::compute(const Mesh& mesh,
                              int element_index,
                              const PoissonKernel& kernel)
{
    constexpr int n = 3;
    Ke = Matrix(n, Vector(n, 0.0));
    Fe = Vector(n, 0.0);

    if (mesh.elements[element_index].size() != n)
        throw std::invalid_argument("Triangle element requires exactly 3 nodes.");

    Node2D p[n];
    for (int i = 0; i < n; ++i)
    {
        p[i] = mesh.nodes[mesh.elements[element_index][i]];
    }

    TriangleShapeFunction shape;
    TriangleQuadrature quadrature;

    for (const QuadraturePoint& gp : quadrature.points())
    {
        double N[n];
        double dNdr[n];
        double dNds[n];

        double x = 0.0;
        double y = 0.0;
        double dxdr = 0.0;
        double dxds = 0.0;
        double dydr = 0.0;
        double dyds = 0.0;

        for (int i = 0; i < n; ++i)
        {
            N[i] = shape.value(i, gp.xi, gp.eta);
            const std::array<double, 2> dN = shape.derivative(i, gp.xi, gp.eta);
            dNdr[i] = dN[0];
            dNds[i] = dN[1];

            x += N[i] * p[i][0];
            y += N[i] * p[i][1];
            dxdr += dNdr[i] * p[i][0];
            dxds += dNds[i] * p[i][0];
            dydr += dNdr[i] * p[i][1];
            dyds += dNds[i] * p[i][1];
        }

        const double detJ = dxdr * dyds - dxds * dydr;
        if (std::abs(detJ) < 1e-14)
            throw std::runtime_error("Degenerate triangle element.");

        std::vector<Node2D> gradients(n);
        for (int i = 0; i < n; ++i)
        {
            gradients[i] = {
                (dyds * dNdr[i] - dydr * dNds[i]) / detJ,
                (-dxds * dNdr[i] + dxdr * dNds[i]) / detJ
            };
        }
        kernel.add_contribution(x, y, Vector(N, N + n), gradients,
                                gp.weight * detJ, Ke, Fe);
    }
}

int QuadrilateralElement::num_nodes() const
{
    return 4;
}

void QuadrilateralElement::compute(const Mesh& mesh,
                                   int element_index,
                                   const PoissonKernel& kernel)
{
    constexpr int n = 4;
    Ke = Matrix(n, Vector(n, 0.0));
    Fe = Vector(n, 0.0);

    if (mesh.elements[element_index].size() != n)
        throw std::invalid_argument("Quadrilateral element requires exactly 4 nodes.");

    Node2D p[n];
    for (int i = 0; i < n; ++i)
    {
        p[i] = mesh.nodes[mesh.elements[element_index][i]];
    }

    QuadrilateralShapeFunction shape;
    QuadrilateralQuadrature quadrature;

    for (const QuadraturePoint& gp : quadrature.points())
    {
        double N[n];
        double dNdr[n];
        double dNds[n];

        double x = 0.0;
        double y = 0.0;
        double dxdr = 0.0;
        double dxds = 0.0;
        double dydr = 0.0;
        double dyds = 0.0;

        for (int i = 0; i < n; ++i)
        {
            N[i] = shape.value(i, gp.xi, gp.eta);
            const std::array<double, 2> dN = shape.derivative(i, gp.xi, gp.eta);
            dNdr[i] = dN[0];
            dNds[i] = dN[1];

            x += N[i] * p[i][0];
            y += N[i] * p[i][1];
            dxdr += dNdr[i] * p[i][0];
            dxds += dNds[i] * p[i][0];
            dydr += dNdr[i] * p[i][1];
            dyds += dNds[i] * p[i][1];
        }

        const double detJ = dxdr * dyds - dxds * dydr;
        if (std::abs(detJ) < 1e-14)
            throw std::runtime_error("Degenerate quadrilateral element.");

        std::vector<Node2D> gradients(n);
        for (int i = 0; i < n; ++i)
        {
            gradients[i] = {
                (dyds * dNdr[i] - dydr * dNds[i]) / detJ,
                (-dxds * dNdr[i] + dxdr * dNds[i]) / detJ
            };
        }
        kernel.add_contribution(x, y, Vector(N, N + n), gradients,
                                gp.weight * detJ, Ke, Fe);
    }
}
