#   - CXX：使用哪个 C++ 编译器，这里是 g++
#   - CXXFLAGS：编译参数
#   - -std=c++17：使用 C++17 标准
#   - -Wall：显示常见警告
#   - -Wextra：显示更多警告
#   - -Iinclude：告诉编译器去 include/ 目录找头文件

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

COMMON_SOURCES = \
	src/mesh/Mesh.cpp \
	src/materials/ConstantDiffusivity.cpp \
	src/kernels/PoissonKernel.cpp \
	src/postprocess/Output.cpp \
	src/elements/ShapeFunction.cpp \
	src/quadrature/Quadrature.cpp \
	src/elements/Element.cpp \
	src/assembly/FEMSystem.cpp \
	src/bcs/DirichletBC.cpp \
	src/solvers/LinearSolver.cpp

HEADERS = $(wildcard include/*.h include/*/*.h)

# 你运行 make 或 make all, 它会尝试构建 solver1d 和 solver2d 两个目标
all: solver1d solver2d

solver1d: $(COMMON_SOURCES) examples/poisson_1d.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ $(COMMON_SOURCES) examples/poisson_1d.cpp

solver2d: $(COMMON_SOURCES) examples/poisson_2d.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ $(COMMON_SOURCES) examples/poisson_2d.cpp

clean:
	rm -f solver1d solver2d

.PHONY: all clean
