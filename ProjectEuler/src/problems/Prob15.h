#pragma once
#include <unordered_map>
#include "Prob_base.h"
/*
 * Starting in the top left corner of a 2×2 grid, and only being able to move to the right and down, there are exactly 6 routes to the bottom right corner.
 * How many such routes are there through a 20×20 grid?
 */
class Prob15 : public Prob_base
{
public:
	Prob15();

    struct int_pair_hash;

    typedef std::pair<int,int> int_pair;
    typedef std::unordered_map<int_pair, long long int, int_pair_hash> int_pair_map;

    static long long num_paths(int xDim, int yDim);

    static long long pathfinder(int x, int y, int_pair_map* p_map);

    std::wstring solve(const std::vector<long long>& new_params) override;

    struct int_pair_hash : public std::unary_function<int_pair, std::size_t>
    {
        std::size_t operator()(const int_pair& val) const
        {
            size_t seed = 0;
            hash_combine(seed, val.first);
            hash_combine(seed, val.second);
            return seed;
        }

        void hash_combine(std::size_t& seed, const int& val) const
        {
            std::hash<int> hasher;
            seed ^= hasher(val) + + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
    };
};

