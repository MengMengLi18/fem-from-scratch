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
include/
  BCs/
  Elements/
  Mesh/
  Models/
  Physics/
  Quadrature/
  ShapeFunctions/
  Solvers/
  System/
  Common.h

src/
  BCs/
  Elements/
  Mesh/
  Models/
  Quadrature/
  ShapeFunctions/
  Solvers/
  System/
  main.cpp
  main_2d.cpp
```

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
- Add iterative solvers such as CG and GMRES.
- Add sparse matrix storage and preconditioners.
