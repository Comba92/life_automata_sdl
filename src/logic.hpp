#pragma once
#include <set>
#include <utility>
#include "engine.hpp"

bool check(std::pair<int,int> p);

class SparseMatrix
{
public:
    bool add_point(std::pair<int,int> p)
    {
        if( check(p) )
        {
            auto ret = points.insert(p);
            return ret.second;
        }

        return false;
    }

    bool delete_point(std::pair<int,int> p)
    {
        if ( points.erase(p) == 0 )
            return false;

        return true;
    }

    bool is_present(std::pair<int,int> p)
    {
        return points.count(p) > 0;
    }

    void clear_points()
    {
        points.clear();
    }

    void nextGeneration();

    std::set<std::pair<int,int>> points;
    
    const std::pair<int,int> directions[9] = {
        {0, BLOCK_SIZE}, {0, -BLOCK_SIZE},
        {BLOCK_SIZE, 0}, {-BLOCK_SIZE, 0},
        {-BLOCK_SIZE, BLOCK_SIZE}, {BLOCK_SIZE, -BLOCK_SIZE},
        {BLOCK_SIZE, BLOCK_SIZE}, {-BLOCK_SIZE, -BLOCK_SIZE},
        {0, 0}
    };
};