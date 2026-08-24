#include "BCs/DirichletBC.h"

void apply_dirichlet(
    Matrix& A,
    Vector& b,
    int node,
    double value)
{
    int n = A.size();


    // Modify RHS first
    for (int i = 0; i < n; ++i)
    {
        b[i] -= A[i][node] * value;
    }


    // Zero row
    for (int j = 0; j < n; ++j)
    {
        A[node][j] = 0.0;
    }


    // Zero column
    for (int i = 0; i < n; ++i)
    {
        A[i][node] = 0.0;
    }


    // Put 1 on diagonal
    A[node][node] = 1.0;


    // Set prescribed value
    b[node] = value;
}
