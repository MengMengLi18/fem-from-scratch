#include <iomanip>
#include <iostream>

#include "BCs/DirichletBC.h"
#include "Elements/Element.h"
#include "System/FEMSystem.h"
#include "Solvers/LinearSolver.h"
#include "Mesh/Mesh.h"
#include "Physics/Physics.h"

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
    PoissonPhysics physics;

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
        element.compute(mesh,e,physics);
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


    for (int i = 0;
         i < mesh.num_nodes();
         ++i)
    {
        std::cout
            << "x = "
            << mesh.nodes[i][0]
            << ", u = "
            << u[i]
            << '\n';
    }


    return 0;
}
