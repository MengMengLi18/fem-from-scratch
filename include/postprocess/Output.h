#pragma once

#include <iosfwd>
#include "Common.h"

class Mesh;
void print_nodal_solution(const Mesh& mesh, const Vector& solution, std::ostream& out);
void print_center_value(const Mesh& mesh, const Vector& solution, std::ostream& out);
