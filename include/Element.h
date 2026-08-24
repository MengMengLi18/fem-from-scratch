#pragma once

#include "Common.h"

class Mesh;
class Physics;

class Element
{
public:
    Matrix Ke;
    Vector Fe;

    virtual ~Element() = default;

    virtual int num_nodes() const = 0;
    virtual void compute(const Mesh& mesh,
                         int element_index,
                         const Physics& physics) = 0;
};

class LineElement : public Element
{
public:
    int num_nodes() const override;
    void compute(const Mesh& mesh,
                 int element_index,
                 const Physics& physics) override;
};

class TriangleElement : public Element
{
public:
    int num_nodes() const override;
    void compute(const Mesh& mesh,
                 int element_index,
                 const Physics& physics) override;
};

class QuadrilateralElement : public Element
{
public:
    int num_nodes() const override;
    void compute(const Mesh& mesh,
                 int element_index,
                 const Physics& physics) override;
};
