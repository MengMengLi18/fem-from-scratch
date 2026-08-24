#pragma once

#include "Common.h"

class Mesh;
class Element;

class FEMSystem
{
public:
    Matrix A;
    Vector b;

    FEMSystem(int n_dof);

    void assemble(const Mesh& mesh,
                  int element_id,
                  const Element& element);
};
