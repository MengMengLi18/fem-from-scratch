cmake_minimum_required(VERSION 3.16)

project(fem-from-scratch
    VERSION 0.1.0
    DESCRIPTION "A readable finite element solver built from scratch in C++"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(FEM_SOURCES
    src/Mesh/Mesh.cpp
    src/Models/PoissonPhysics.cpp
    src/ShapeFunctions/ShapeFunction.cpp
    src/Quadrature/Quadrature.cpp
    src/Elements/Element.cpp
    src/System/FEMSystem.cpp
    src/BCs/DirichletBC.cpp
    src/Solvers/LinearSolver.cpp
)

add_library(femcore STATIC ${FEM_SOURCES})

target_include_directories(femcore
    PUBLIC include
)

target_compile_features(femcore
    PUBLIC cxx_std_17
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(femcore PRIVATE -Wall -Wextra)
endif()

add_executable(solver1d src/main.cpp)
target_link_libraries(solver1d PRIVATE femcore)

add_executable(solver2d src/main_2d.cpp)
target_link_libraries(solver2d PRIVATE femcore)
