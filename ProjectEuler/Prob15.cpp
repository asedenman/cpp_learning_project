#include "stdafx.h"
#include "Prob15.h"
#include <unordered_map>
#include "resource.h"


Prob15::Prob15() : Prob_base(IDS_PROB15_EXP)
{
    prob_params.emplace_back(TEXT("max x"), 20);
    prob_params.emplace_back(TEXT("max y"), 20);
}


std::wstring Prob15::solve(const std::vector<long long>& new_params)
{
    set_params(new_params);

    return TEXT("Answer: ") + std::to_wstring(num_paths(prob_params[0].value, prob_params[1].value));
}

long long Prob15::num_paths(int xDim, int yDim)
{
    auto map = int_pair_map();

    return pathfinder(xDim, yDim, &map);
}


long long Prob15::pathfinder(int x, int y, int_pair_map* p_map)
{
    if (x == 0 && y == 0)
    {
        return 1;
    }

    if (p_map->count(std::make_pair(x, y)) > 0)
    {
        return p_map->at(std::make_pair(x, y));
    }

    const auto x_result = (x > 0 ? pathfinder(x - 1, y, p_map) : 0);
    const auto y_result = (y > 0 ? pathfinder(x, y - 1, p_map) : 0);

    if (x_result > 0 && y_result > 0)
    {
        p_map->operator[](std::make_pair(x, y)) = x_result + y_result;
    }


    return x_result + y_result;
}
