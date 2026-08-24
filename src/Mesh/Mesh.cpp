#include "Mesh/Mesh.h"

Mesh::Mesh(int n_elements, double length)
    : dimension(1)
{
    const double dx = length / n_elements;

    for (int n = 0; n <= n_elements; ++n)
    {
        nodes.push_back({n * dx, 0.0});
    }

    for (int e = 0; e < n_elements; ++e)
    {
        elements.push_back({e, e + 1});
    }
}

Mesh::Mesh(int dimension_,
           const std::vector<Node2D>& nodes_,
           const std::vector<std::vector<int>>& elements_)
    : dimension(dimension_), nodes(nodes_), elements(elements_)
{
}

int Mesh::num_nodes() const
{
    return nodes.size();
}

int Mesh::num_elements() const
{
    return elements.size();
}
