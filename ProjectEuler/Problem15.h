#pragma once
#include <tuple>
#include <unordered_map>
#include "ProblemBase.h"

class Prob15 : public ProblemBase
{
public:
	Prob15();

    struct key_hash;
    struct key_equal;

    typedef std::tuple<int,int> intTuple;
    typedef std::unordered_map<intTuple, long long int, key_hash, key_equal> intLongMap;

    static long long num_paths(int xDim, int yDim);

    static long long pathfinder(int x, int y, intLongMap* p_map);

    std::wstring Solve(const std::vector<int>& params) override;

    struct key_hash : public std::unary_function<intTuple, std::size_t>
    {
        std::size_t operator()(const intTuple& k) const
        {
            return std::get<0>(k) ^ std::get<1>(k);
        }
    };

    struct key_equal : public std::binary_function<intTuple, intTuple, bool>
    {
        bool operator()(const intTuple& v0, const intTuple& v1) const
        {
            return (
                std::get<0>(v0) == std::get<0>(v1) &&
                std::get<1>(v0) == std::get<1>(v1)
            );
        }
    };
};

