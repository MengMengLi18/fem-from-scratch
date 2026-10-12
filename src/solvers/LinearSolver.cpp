#include "solvers/LinearSolver.h"

#include <cmath>
#include <stdexcept>

// ============================================================
// Linear solver:
// Gaussian elimination with partial pivoting
//      A x = b
// ============================================================

Vector solve_linear_system(Matrix A, Vector b)
{
    int n = A.size();

    // --------------------------------------------------------
    // Forward elimination: 把矩阵消成上三角矩阵
    // --------------------------------------------------------

    for (int k = 0; k < n; ++k)
    {
        // Find pivot
        int pivot = k;

        for (int i = k + 1; i < n; ++i)
        {
            if (std::abs(A[i][k])
                >
                std::abs(A[pivot][k]))
            {
                pivot = i;
            }
        }

        if (std::abs(A[pivot][k]) < 1e-14)
        {
            throw std::runtime_error(
                "Singular matrix."
            );
        }

        // Swap rows
        std::swap(A[k], A[pivot]);
        std::swap(b[k], b[pivot]);

        // Eliminate
        for (int i = k + 1; i < n; ++i)
        {
            double factor = A[i][k] / A[k][k];

            for (int j = k; j < n; ++j)
            {
                A[i][j] -= factor * A[k][j];
            }

            b[i] -= factor * b[k];
        }
    }

    // --------------------------------------------------------
    // Back substitution: 从最后一个未知量往回求解
    // --------------------------------------------------------

    Vector x(n, 0.0);

    for (int i = n - 1; i >= 0; --i)
    {
        double sum = b[i];

        for (int j = i + 1; j < n; ++j)
        {
            sum -= A[i][j] * x[j];
        }

        x[i] = sum / A[i][i];
    }


    return x;
}
