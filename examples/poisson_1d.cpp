#include <iomanip>
#include <iostream>

#include "bcs/DirichletBC.h"
#include "elements/Element.h"
#include "assembly/FEMSystem.h"
#include "solvers/LinearSolver.h"
#include "mesh/Mesh.h"
#include "materials/ConstantDiffusivity.h"
#include "kernels/PoissonKernel.h"
#include "postprocess/Output.h"

// ============================================================
// 9. Main
// ============================================================

int main()
{
    // --------------------------------------------------------
    // Problem parameters
    // --------------------------------------------------------
    int n_elem = 10;
    double L = 1.0;

    // --------------------------------------------------------
    // Create mesh
    // --------------------------------------------------------
    Mesh mesh(n_elem, L);

    // --------------------------------------------------------
    // Define physics
    // --------------------------------------------------------
    ConstantDiffusivity material;
    PoissonKernel kernel(material);

    // --------------------------------------------------------
    // Create global system
    // --------------------------------------------------------
    FEMSystem system(mesh.num_nodes());

    // --------------------------------------------------------
    // Element loop
    // --------------------------------------------------------
    for (int e = 0;e < mesh.num_elements(); ++e)
    {
        LineElement element;
        // Calculate local Ke and Fe
        element.compute(mesh,e,kernel);
        // Assemble into global system
        system.assemble(mesh,e,element);
    }

    // --------------------------------------------------------
    // Boundary conditions
    // u(0) = 0
    // u(1) = 0
    // --------------------------------------------------------
    apply_dirichlet(
        system.A,
        system.b,
        0,
        0.0
    );


    apply_dirichlet(
        system.A,
        system.b,
        mesh.num_nodes() - 1,
        0.0
    );


    // --------------------------------------------------------
    // Solve
    //
    // A u = b
    // --------------------------------------------------------

    Vector u =
        solve_linear_system(
            system.A,
            system.b
        );


    // --------------------------------------------------------
    // Output
    // --------------------------------------------------------

    std::cout
        << std::setprecision(8);


    print_nodal_solution(mesh, u, std::cout);


    return 0;
}
