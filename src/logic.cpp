#include "logic.hpp"
#include <map>

bool check(std::pair<int,int> p)
{
    if(p.first < 0 || p.first + BLOCK_SIZE > SCREEN_WIDTH)
        return false;
    if(p.second < 0 || p.second + BLOCK_SIZE > SCREEN_HEIGHT)
        return false;
    return true;
}

void SparseMatrix::nextGeneration()
{
    std::map<std::pair<int,int>, int> neighsCount;
    
    for (auto p : points)
    {
        for (auto direction : directions)
        {
            std::pair<int,int> toCheck = { 
                p.first+direction.first,
                p.second+direction.second
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