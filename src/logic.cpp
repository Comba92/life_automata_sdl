#include "logic.hpp"
#include "definitions.hpp"
#include <map>

bool is_valid_point(std::pair<int, int> p)
{
  return (p.first >= 0 && p.first + BLOCK_SIZE <= SCREEN_WIDTH)
    && (p.second >= 0 && p.second + BLOCK_SIZE <= SCREEN_HEIGHT);
}

bool SparseMatrix::add_point(std::pair<int, int> p)
{
  return is_valid_point(p) ? points.insert(p).second : false;
}

bool SparseMatrix::delete_point(std::pair<int, int> p)
{
  return points.erase(p) != 0;
}

bool SparseMatrix::is_present(std::pair<int, int> p)
{
  return points.count(p) > 0;
}

void SparseMatrix::clear_points()
{
  points.clear();
}

void SparseMatrix::next_generation()
{
  std::map<std::pair<int,int>, int> neighsCount;
  
  for (auto p : points)
  {
    for (auto direction : DIRECTIONS)
    {
      std::pair<int,int> toCheck = { 
        p.first  + direction[0]*BLOCK_SIZE,
        p.second + direction[1]*BLOCK_SIZE
      };

      if (is_valid_point(toCheck))
        neighsCount[toCheck]++;
    }
  }

  std::set<std::pair<int,int>> new_points;
  for (auto n : neighsCount)
  {
    if (n.second == 4 && is_present(n.first))
    {
      new_points.insert(n.first);
    } else if (n.second == 3) {
      new_points.insert(n.first);
    }
  }

  points = new_points;
}