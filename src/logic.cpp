#include "logic.hpp"
#include "definitions.hpp"
#include <map>

bool check(std::pair<int, int> p)
{
  if (p.first < 0 || p.first + BLOCK_SIZE > SCREEN_WIDTH)
    return false;
  if (p.second < 0 || p.second + BLOCK_SIZE > SCREEN_HEIGHT)
    return false;
  return true;
}

bool SparseMatrix::add_point(std::pair<int, int> p)
{
  if (check(p))
  {
    auto ret = points.insert(p);
    return ret.second;
  }

  return false;
}

bool SparseMatrix::delete_point(std::pair<int, int> p)
{
  if (points.erase(p) == 0)
    return false;

  return true;
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
    for (auto direction : directions)
    {
      std::pair<int,int> toCheck = { 
        p.first+direction.first*BLOCK_SIZE,
        p.second+direction.second*BLOCK_SIZE
      };

      neighsCount[toCheck]++;
    }
  }

  std::set<std::pair<int,int>> new_points;
  for (auto p : neighsCount)
  {
    if (p.second == 4 && is_present(p.first))
    {
      if(check(p.first))
        new_points.insert(p.first);
    }
  }

  points = new_points;

  for (auto p : neighsCount)
  {
    if (p.second == 3)
      add_point(p.first);
  }
}