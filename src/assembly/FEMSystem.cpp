#include "assembly/FEMSystem.h"

#include "elements/Element.h"
#include "mesh/Mesh.h"

FEMSystem::FEMSystem(int n_dof)
    : A(n_dof, Vector(n_dof, 0.0)),
      b(n_dof, 0.0)
{
}

void FEMSystem::assemble(const Mesh& mesh,
                         int element_id,
                         const Element& element)
{
    const std::vector<int>& global_ids = mesh.elements[element_id];
    const int n = element.num_nodes();

    for (int i = 0; i < n; ++i)
    {
        const int global_i = global_ids[i];
        b[global_i] += element.Fe[i];

        for (int j = 0; j < n; ++j)
        {
            const int global_j = global_ids[j];
            A[global_i][global_j] += element.Ke[i][j];
        }
    }
}
