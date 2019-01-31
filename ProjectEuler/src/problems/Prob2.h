#pragma once
#include "Prob_base.h"
/**
 * \brief Prob2: The sum of all even fibonacci numbers 
 */
class Prob2 :
	public Prob_base
{
public:
	Prob2();
	~Prob2() = default;


   std::wstring solve(const std::vector<long long>& new_params) override;

    static unsigned long long SumOfFibonnaciNumsLessThan(int max_num);

};

