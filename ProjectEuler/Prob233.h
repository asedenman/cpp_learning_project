#pragma once
#include "Prob_base.h"
/*
 * Problem:
 * Let f(N) be the number of points with integer coordinates that are on a circle passing through (0,0), (N,0), (0,N), (N,N)
 * It can be shown that f(10000) = 36.
 * What is the sum of all positive integers N <= 10^11 such that f(N) = 420 ?
 */
class Prob233 :
	public Prob_base
{
public:
	Prob233();
	~Prob233() = default;


    std::wstring solve(const std::vector<long long>& new_params) override;

    static int num_lattice_pnts_on_circle(long long square_num);

};

