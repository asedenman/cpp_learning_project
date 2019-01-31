#include "stdafx.h"
#include "Prob2.h"
#include "Resource.h"




Prob2::Prob2() : ProblemBase(IDS_PROB2_EXP, 1)
{
    Params.emplace_back(TEXT("max num"), 4000000);
}


Prob2::~Prob2()
{
}



/**
 * \brief 
 * \param params : length 1: max value for fibonacci numbers to sum
 * \return 
 */
std::wstring Prob2::Solve(const std::vector<int>& params)
{
    SetParams(params);

    unsigned int max_value = Params[0].Value;

    return TEXT("Answer = ") + std::to_wstring(SumOfFibonnaciNumsLessThan(max_value));


}

unsigned long long Prob2::SumOfFibonnaciNumsLessThan(int max_num)
{
    if (max_num <= 0)
    {
        return 0;
    }
    //Initial values given are: 1 , 1
    unsigned int a = 1;
    unsigned int b = 1;

    // Basic iterative approach
    unsigned long long sum = 0;

    unsigned int c = 0;

    while (true)
    {
        c = a + b;
        if (c > max_num)
        {
            break;
        }
        if (!(c & 1))
        {
            sum += c;
        }
        a = b;
        b = c;
    }

    return sum;
}



