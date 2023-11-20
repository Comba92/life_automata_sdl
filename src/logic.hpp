#pragma once
#include <set>
#include <utility>
#include "engine.hpp"
using namespace std;

bool is_valid_point(std::pair<int,int> p);

static const int DIRECTIONS[9][2] = {
  {0, 1}, {0, -1}, {1, 0}, {-1, 0}, {-1, 1}, {1, -1}, {1, 1}, {-1, -1}, {0, 0}
};

class SparseMatrix 
{
public:
  set<pair<int,int>> points;
  
  bool add_point(pair<int, int> p);
  bool delete_point(pair<int, int> p);
  bool is_present(pair<int, int> p);
  void clear_points();
  void next_generation();
};
