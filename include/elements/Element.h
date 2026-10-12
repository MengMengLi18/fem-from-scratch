#pragma once

#include "Common.h"

class Mesh;
class PoissonKernel;

class Element
{
public:
    Matrix Ke;
    Vector Fe;

    virtual ~Element() = default;

    virtual int num_nodes() const = 0;
    virtual void compute(const Mesh& mesh,
                         int element_index,
                         const PoissonKernel& kernel) = 0;
};

class LineElement : public Element
{
public:
    int num_nodes() const override;
    void compute(const Mesh& mesh,
                 int element_index,
                 const PoissonKernel& kernel) override;
};

class TriangleElement : public Element
{
public:
    int num_nodes() const override;
    void compute(const Mesh& mesh,
                 int element_index,
                 const PoissonKernel& kernel) override;
};

class QuadrilateralElement : public Element
{
public:
    int num_nodes() const override;
    void compute(const Mesh& mesh,
                 int element_index,
                 const PoissonKernel& kernel) override;
};
