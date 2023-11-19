#pragma once
#include <set>
#include <utility>
#include "engine.hpp"

bool check(std::pair<int,int> p);

class SparseMatrix 
{
public:
  std::set<std::pair<int,int>> points;
    
  const std::pair<int,int> directions[9] = {
    {0, 1}, {0, -1},
    {1, 0}, {-1, 0},
    {-1, 1}, {1, -1},
    {1, 1}, {-1, -1},
    {0, 0}
  };

  bool add_point(std::pair<int, int> p);
  bool delete_point(std::pair<int, int> p);
  bool is_present(std::pair<int, int> p);
  void clear_points();
  void next_generation();
};