#include "stdafx.h"
#include "Prob233.h"
#include <unordered_map>
#include "../../Resource.h"


Prob233::Prob233() : Prob_base(IDS_PROB233_EXP)
{
	prob_params.emplace_back(TEXT("max num"), 1000000000);
	prob_params.emplace_back(TEXT("filter value"), 420);//unimplemented
}

std::wstring Prob233::solve(const std::vector<long long>& new_params)
{
    set_params(new_params);

    unsigned long long square_num = prob_params[0].value;

    return TEXT("Answer = ") + std::to_wstring(num_lattice_pnts_on_circle(square_num));
}


/**
 * \brief Too slow. TODO consider using sum of squares function
 * \param square_num 
 * \return 
 */
int Prob233::num_lattice_pnts_on_circle(long long const square_num)
{
    constexpr float inv_sqrt_two = 0.70710678118;

    //calc radius^2 
    //centre circle
    //for each y
    //  calc sq_rad - sq_y
    //  check if perfect square
    //  done

    unsigned long long trunc_radius = (square_num * inv_sqrt_two);
    unsigned long long sq_radius = (square_num * square_num) / 2 ; // odd numbers have result == 0???
    unsigned long long min_y = square_num & 1? (square_num + 1)/ 2 : square_num / 2;


    int result = 0;
    std::vector<std::pair<long long, long long>> valid_coords;
	{
        unsigned long long sq_x;
        long double x;

        for (auto y = trunc_radius; y > min_y; --y)
        {

            sq_x = sq_radius - (y * y);

            x = sqrtl(sq_x);

            if (static_cast<long long>(x) == x)
            {
                valid_coords.emplace_back(static_cast<long long>(x), y);
                result++;
            }
        }
	}

    return 4 + result*8;
}

