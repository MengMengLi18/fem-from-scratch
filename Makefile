#   - CXX：使用哪个 C++ 编译器，这里是 g++
#   - CXXFLAGS：编译参数
#   - -std=c++17：使用 C++17 标准
#   - -Wall：显示常见警告
#   - -Wextra：显示更多警告
#   - -Iinclude：告诉编译器去 include/ 目录找头文件

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

COMMON_SOURCES = \
	src/Mesh/Mesh.cpp \
	src/Models/PoissonPhysics.cpp \
	src/ShapeFunctions/ShapeFunction.cpp \
	src/Quadrature/Quadrature.cpp \
	src/Elements/Element.cpp \
	src/System/FEMSystem.cpp \
	src/BCs/DirichletBC.cpp \
	src/Solvers/LinearSolver.cpp

# 你运行 make 或 make all, 它会尝试构建 solver1d 和 solver2d 两个目标
all: solver1d solver2d

solver1d: $(COMMON_SOURCES) src/main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $(COMMON_SOURCES) src/main.cpp

solver2d: $(COMMON_SOURCES) src/main_2d.cpp
	$(CXX) $(CXXFLAGS) -o $@ $(COMMON_SOURCES) src/main_2d.cpp

clean:
	rm -f solver1d solver2d

.PHONY: all clean
