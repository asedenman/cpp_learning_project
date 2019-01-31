#pragma once
#include <vector>
#include "Prob_base.h"
#include <unordered_map>

/*
 * container for all problems
 */
class ProblemManager
{
public:
	ProblemManager();
	~ProblemManager() = default;

    std::unordered_map<int, std::unique_ptr<Prob_base>> problems;

    std::wstring answer_to_prob(int problem_id, std::vector<long long>& params);

    int first_pid() const;
    bool problem_exists(int pID) const;
    int num_problem_params(int pID) const;
    const wchar_t* problem_param_chars(int pID, int param_ID);
    int problem_param_val(int pID, int param_ID);
    int get_problem_explanation_str_id(int pID);

};

