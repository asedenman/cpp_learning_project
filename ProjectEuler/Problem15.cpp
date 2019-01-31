#include "stdafx.h"
#include "Prob15.h"
#include <unordered_map>
#include "resource.h"


Prob15::Prob15() : ProblemBase(IDS_PROB15_EXP, 2)
{
    Params.emplace_back(TEXT("max x"), 20);
    Params.emplace_back(TEXT("max y"), 20);
}


std::wstring Prob15::Solve(const std::vector<int>& params)
{
    long long answer;
    if (static_cast<int>(params.size()) == numberOfParameters())
    {
        answer = num_paths(params[0] > 0? params[0] : Params[0].Value, params[1] > 0? params[0] : Params[1].Value);
    }
	else
	{
        answer = num_paths(Params[0].Value, Params[1].Value);
	}

    return TEXT("Answer: ") + std::to_wstring(answer); 
}

long long Prob15::num_paths(int xDim, int yDim)
{
    auto map = intLongMap();

    return pathfinder(xDim, yDim, &map);

}


long long Prob15::pathfinder(int x, int y, intLongMap* p_map)
{
    if (x == 0 && y == 0)
    {
        return 1;
    }

    if(p_map->count(std::make_tuple(x, y)) > 0)
    {

        return p_map->at(std::make_tuple(x, y));
    }

    const long long x_result = (x > 0? pathfinder(x - 1, y, p_map) : 0);
    const long long y_result = (y > 0? pathfinder(x, y - 1, p_map) : 0);

    if (x_result > 0 && y_result > 0)
    {
        p_map->operator[](std::make_tuple(x,y)) = x_result + y_result;
        
    }


    return x_result + y_result;
}
