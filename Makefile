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

all: solver1d solver2d

solver1d: $(COMMON_SOURCES) src/main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $(COMMON_SOURCES) src/main.cpp

solver2d: $(COMMON_SOURCES) src/main_2d.cpp
	$(CXX) $(CXXFLAGS) -o $@ $(COMMON_SOURCES) src/main_2d.cpp

clean:
	rm -f solver1d solver2d

.PHONY: all clean
