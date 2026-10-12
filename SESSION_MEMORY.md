# Session Memory

Date: 2026-08-24

## Project

- Repository / folder: `fem-from-scratch`
- Local path: `/home/mmlab_lmm/Projects/FEALMM/LinearSolver`
- Goal: build a readable FEM solver from scratch, then move from linear to nonlinear solvers.

## Current Architecture (updated 2026-10-12)

- Headers and sources are grouped into `mesh`, `elements`, `quadrature`,
  `materials`, `kernels`, `assembly`, `bcs`, `solvers`, and `postprocess`.
- `petsc` is reserved only; no PETSc backend is implemented yet.
- Problem entry points are in `examples/poisson_1d.cpp` and `examples/poisson_2d.cpp`.
- `PoissonPhysics` has been separated into `ConstantDiffusivity` and `PoissonKernel`.
- Element geometry calls the kernel for local weak-form contributions.
- CMake and Make build `solver1d` and `solver2d`.
- See `README.md` for the maintained directory map.

## Implemented FEM Pipeline

- 1D uniform mesh and generic 1D/2D mesh storage
- Poisson physics model
- Line, triangle, and quadrilateral shape functions
- Line, triangle, and quadrilateral quadrature rules
- Line, triangle, and quadrilateral elements
- Generic assembly in `FEMSystem`
- Dirichlet BC using exact row/column elimination
- Dense Gaussian elimination solver with partial pivoting

## Current Validation Results

- 1D Poisson `-u'' = 1`:
  - center value `0.125`
- 2D triangle mesh:
  - center value `1/12 = 0.083333333`
- 2D quadrilateral mesh:
  - center value `0.09375`

## Important Bug Fixed

- 2D triangle/quadrilateral derivative mapping was incorrect.
- Fixed `src/elements/Element.cpp` (line numbers changed during classification).
- Correct mapping:
  - `dNdx = (dyds * dNdr - dydr * dNds) / detJ`
  - `dNdy = (-dxds * dNdr + dxdr * dNds) / detJ`

## Learning Progress

Already understood:

- `.h` declarations vs `.cpp` implementations
- constructors and member initializer lists
- `std::vector` and `std::array` basics
- shape functions and derivatives for line/triangle/quad
- quadrature points and weights
- element local `Ke` and `Fe` calculation
- direct linear solver: Gaussian elimination + back substitution
- Makefile and CMake basics, static library concept

Weak-form contributions now live in `src/kernels/PoissonKernel.cpp`; geometry and physical derivatives remain in `src/elements/Element.cpp`.

## Next Steps

Use `../guid.md` as the single maintained learning/task list: mixed boundary
conditions and P1/P2 error validation, then PETSc KSP, nonlinear Poisson and SNES.

## Resume Trigger

When the user says something like:

- "继续"
- "继续推荐"
- "continue nonlinear"
- "从 linear 推进到 nonlinear"

Read this file and continue from the `Next Steps` section.
