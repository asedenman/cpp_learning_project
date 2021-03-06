#include "stdafx.h"
#include "Prob2.h"
#include "../../Resource.h"




Prob2::Prob2() : Prob_base(IDS_PROB2_EXP)
{
    prob_params.emplace_back(TEXT("max num"), 4000000);
}


/**
 * \brief 
 * \param new_params : length 1: max value for fibonacci numbers to sum
 * \return 
 */
std::wstring Prob2::solve(const std::vector<long long>& new_params)
{
    set_params(new_params);

    const unsigned long long max_value = prob_params[0].value;

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

    while (true)
    {
        auto c = a + b;
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



