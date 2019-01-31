#pragma once
#include "ProblemBase.h"
/**
 * \brief Prob2: The sum of all even fibonacci numbers 
 */
class Prob2 :
	public ProblemBase
{
public:
	Prob2();
	~Prob2();


   std::wstring Solve(const std::vector<int>& params) override;

    static unsigned long long SumOfFibonnaciNumsLessThan(int max_num);

};

