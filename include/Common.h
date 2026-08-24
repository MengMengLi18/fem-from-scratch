#pragma once

#include <array>
#include <vector>
// std::vector 是 STL 的动态数组容器,
// Vector 只是它的别名, 本质还是 STL 容器
using Vector = std::vector<double>;

// 动态数组的动态数组, 外层是 vector，内层每个元素也是 vector<double>。
using Matrix = std::vector<std::vector<double>>;

// std::array<double, 2> 是 STL 的固定大小数组
// 内部存 2 个 double, 也是类模板, 只是大小不能变
using Node2D = std::array<double, 2>;  // {x, y}
