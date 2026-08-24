#pragma once

#include <vector>

#include "Common.h"

// struct 默认成员是 public
// class 默认成员是 private
struct Mesh
{
    int dimension;
    std::vector<Node2D> nodes;
    std::vector<std::vector<int>> elements;

    // Uniform 1D mesh on [0, length].
    Mesh(int n_elements, double length);

    // Generic 1D/2D mesh with explicit nodes and connectivity.
    Mesh(int dimension,
         const std::vector<Node2D>& nodes,
         const std::vector<std::vector<int>>& elements);
    //  member functions for number of nodes and elements
    int num_nodes() const;
    int num_elements() const;
};
