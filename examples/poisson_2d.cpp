#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "bcs/DirichletBC.h"
#include "elements/Element.h"
#include "assembly/FEMSystem.h"
#include "solvers/LinearSolver.h"
#include "mesh/Mesh.h"
#include "materials/ConstantDiffusivity.h"
#include "kernels/PoissonKernel.h"
#include "postprocess/Output.h"

static Vector solve_poisson_2d(const Mesh& mesh, const PoissonKernel& kernel)
{
    FEMSystem system(mesh.num_nodes());

    for (int e = 0; e < mesh.num_elements(); ++e)
    {
        const std::size_t nodes_per_element = mesh.elements[e].size();

        if (nodes_per_element == 3)
        {
            TriangleElement element;
            element.compute(mesh, e, kernel);
            system.assemble(mesh, e, element);
        }
        else if (nodes_per_element == 4)
        {
            QuadrilateralElement element;
            element.compute(mesh, e, kernel);
            system.assemble(mesh, e, element);
        }
        else
        {
            throw std::runtime_error("Unsupported element type in 2D demo.");
        }
    }

    for (int n = 0; n < mesh.num_nodes(); ++n)
    {
        const double x = mesh.nodes[n][0];
        const double y = mesh.nodes[n][1];
        const bool on_boundary = (x < 1e-12 || x > 1.0 - 1e-12 ||
                                  y < 1e-12 || y > 1.0 - 1e-12);

        if (on_boundary)
            apply_dirichlet(system.A, system.b, n, 0.0);
    }

    return solve_linear_system(system.A, system.b);
}

int main()
{
    ConstantDiffusivity material;
    PoissonKernel kernel(material);
    std::cout << std::setprecision(8);

    // Triangle mesh: square split into four triangles around a center node.
    std::vector<Node2D> tri_nodes = {
        {0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}, {0.5, 0.5}
    };
    std::vector<std::vector<int>> tri_elements = {
        {0, 1, 4}, {1, 2, 4}, {2, 3, 4}, {3, 0, 4}
    };
    Mesh tri_mesh(2, tri_nodes, tri_elements);

    std::cout << "Triangle mesh:\n";
    print_center_value(tri_mesh, solve_poisson_2d(tri_mesh, kernel), std::cout);

    // Quadrilateral mesh: square split into 2x2 quadrilaterals.
    std::vector<Node2D> quad_nodes = {
        {0.0, 0.0}, {0.5, 0.0}, {1.0, 0.0},
        {0.0, 0.5}, {0.5, 0.5}, {1.0, 0.5},
        {0.0, 1.0}, {0.5, 1.0}, {1.0, 1.0}
    };
    std::vector<std::vector<int>> quad_elements = {
        {0, 1, 4, 3}, {1, 2, 5, 4},
        {3, 4, 7, 6}, {4, 5, 8, 7}
    };
    Mesh quad_mesh(2, quad_nodes, quad_elements);

    std::cout << "Quadrilateral mesh:\n";
    print_center_value(quad_mesh, solve_poisson_2d(quad_mesh, kernel), std::cout);

    return 0;
}
