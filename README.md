# fem-from-scratch

A small, readable finite element solver built from scratch in modern C++.

The project starts with a 1D Poisson solver and grows toward 2D elements, more
boundary conditions, and more solvers.

## Current Features

- 1D linear line element
- 2D linear triangle element
- 2D bilinear quadrilateral element
- Poisson physics model with constant coefficients
- Dirichlet boundary conditions
- Direct linear solver: Gaussian elimination with partial pivoting
- 1D and 2D example programs

## Project Structure

```text
include/                  # Public headers
  assembly/               # FEMSystem: local-to-global matrix/load assembly
  bcs/                    # Dirichlet conditions
  elements/               # Elements, shape functions and geometry mapping
  kernels/                # Poisson weak-form integration contributions
  materials/              # Material coefficients, e.g. ConstantDiffusivity
  mesh/                   # Nodes and element connectivity
  postprocess/            # Nodal and center-value output
  quadrature/             # Numerical integration rules
  solvers/                # Dense reference linear solver
  petsc/                  # Reserved: not implemented yet
  Common.h
src/                      # Implementations matching include/
examples/
  poisson_1d.cpp
  poisson_2d.cpp
```

### Module responsibilities

`Element` evaluates geometry, shape values, physical gradients and integration
weights. It delegates each integration-point contribution to `PoissonKernel`.
The kernel evaluates the linear Poisson weak form using a `Material` diffusion
coefficient and a callable source. `FEMSystem` maps element matrices and loads
to the global system. Boundary conditions and the solver operate on that system;
postprocessing formats the solution.

`ConstantDiffusivity` replaces the coefficient part of `PoissonPhysics`; the
source now belongs to `PoissonKernel`, separate from material data:

```cpp
ConstantDiffusivity material(1.0);
PoissonKernel kernel(material, [](double x, double) { return x; });
```

The material must outlive the kernel. Examples default to diffusivity 1 and
source 1, preserving the original numerical problem. The current kernel forms
linear stiffness/load contributions; nonlinear residual and Jacobian kernels
are a later stage. PETSc directories reserve the integration boundary and do not
provide an implemented backend yet.

### Directory migration

| Previous location | Current location |
|---|---|
| `Mesh/`, `BCs/`, `Solvers/`, `Quadrature/` | `mesh/`, `bcs/`, `solvers/`, `quadrature/` |
| `Elements/`, `ShapeFunctions/` | `elements/` |
| `System/` | `assembly/` |
| `Physics/`, `Models/PoissonPhysics` | `materials/` and `kernels/` |
| `src/main.cpp`, `src/main_2d.cpp` | `examples/poisson_1d.cpp`, `examples/poisson_2d.cpp` |
| Output embedded in examples | `postprocess/` |

## Build with Make

```bash
make all
```

This produces two executables:

- `solver1d`: one-dimensional Poisson example.
- `solver2d`: two-dimensional triangle and quadrilateral Poisson examples.

## Build with CMake

```bash
cmake -S . -B build
cmake --build build
```

The executables are created in the `build/` directory.

## Run

```bash
./solver1d
./solver2d
```

With CMake:

```bash
./build/solver1d
./build/solver2d
```

## Example Results

The 1D example solves `-u'' = 1` on `[0, 1]` with `u(0) = u(1) = 0`.
The center value is:

```text
x = 0.5, u = 0.125
```

The 2D examples solve `-Δu = 1` on the unit square with homogeneous Dirichlet
boundary conditions on a coarse mesh.

## Next Steps

- Add Neumann and mixed boundary conditions.
- Add a 3-node quadratic line element.
- Validate P1/P2 error norms and mesh convergence.
- Integrate PETSc Mat/Vec/KSP after linear FEM validation.
- Implement nonlinear Poisson residual/Jacobian, then integrate SNES.
