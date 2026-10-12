#   - add_library(...)：创建库
#   - add_executable(...)：创建可执行文件
#   - target_include_directories(...)：指定头文件路径
#   - target_compile_features(...)：指定 C++ 标准
#   - target_compile_options(...)：编译选项
#   - target_link_libraries(...)：链接库

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
    src/mesh/Mesh.cpp
    src/materials/ConstantDiffusivity.cpp
    src/kernels/PoissonKernel.cpp
    src/postprocess/Output.cpp
    src/elements/ShapeFunction.cpp
    src/quadrature/Quadrature.cpp
    src/elements/Element.cpp
    src/assembly/FEMSystem.cpp
    src/bcs/DirichletBC.cpp
    src/solvers/LinearSolver.cpp
)

# CMake 先把公共 FEM 源码编译成一个静态库 libfemcore.a
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
# 定义两个可执行文件
add_executable(solver1d examples/poisson_1d.cpp)
# 让这两个可执行文件链接 femcore
target_link_libraries(solver1d PRIVATE femcore)

add_executable(solver2d examples/poisson_2d.cpp)
target_link_libraries(solver2d PRIVATE femcore)
