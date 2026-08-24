CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

COMMON_SOURCES = \
	src/Mesh.cpp \
	src/Physics.cpp \
	src/ShapeFunction.cpp \
	src/Quadrature.cpp \
	src/Element.cpp \
	src/FEMSystem.cpp \
	src/DirichletBC.cpp \
	src/LinearSolver.cpp

all: solver1d solver2d

solver1d: $(COMMON_SOURCES) src/main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $(COMMON_SOURCES) src/main.cpp

solver2d: $(COMMON_SOURCES) src/main_2d.cpp
	$(CXX) $(CXXFLAGS) -o $@ $(COMMON_SOURCES) src/main_2d.cpp

clean:
	rm -f solver1d solver2d

.PHONY: all clean
