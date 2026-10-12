#include "postprocess/Output.h"

#include <cmath>
#include <ostream>
#include "mesh/Mesh.h"

void print_nodal_solution(const Mesh& mesh, const Vector& u, std::ostream& out)
{
    for (int i = 0; i < mesh.num_nodes(); ++i)
        out << "x = " << mesh.nodes[i][0] << ", u = " << u[i] << '\n';
}

void print_center_value(const Mesh& mesh, const Vector& u, std::ostream& out)
{
    for (int i = 0; i < mesh.num_nodes(); ++i)
    {
        if (std::abs(mesh.nodes[i][0] - 0.5) < 1e-12 &&
            std::abs(mesh.nodes[i][1] - 0.5) < 1e-12)
        {
            out << "center u = " << u[i] << '\n';
            return;
        }
    }
}
