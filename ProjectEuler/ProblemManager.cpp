#include "stdafx.h"
#include "ProblemManager.h"
#include "Prob_base.h"
#include "Prob15.h"
#include <cassert>
#include "Prob2.h"
#include "Prob233.h"


ProblemManager::ProblemManager()
{
    problems[15]  = std::make_unique<Prob15>();
    problems[2]   = std::make_unique<Prob2>();
    problems[233] = std::make_unique<Prob233>();
}

std::wstring ProblemManager::answer_to_prob(int problem_id, std::vector<long long>& params)
{
    if (problem_exists(problem_id))
    {
        return problems[problem_id]->solve(params);
    }
    return TEXT("Problem not found.");
}

/**
 * \brief 
 * \param pID Problem number from ProjectEuler Website - never less than 0
 * \return True if there is a problem with that id
 */
bool ProblemManager::problem_exists(int pID) const
{
    return pID > 0 && problems.count(pID) > 0;
}

/**
 * \brief 
 * \param pID The problem number from projecteuler website  - never less than 0
 * \return 0 if no problem found
 */
int ProblemManager::num_problem_params(int pID) const
{
    if (!problem_exists(pID))
    {
        return 0;
    }
    return problems.at(pID)->number_of_parameters();
}


/**
 * \return description of problem parameter
 */
const wchar_t* ProblemManager::problem_param_chars(int pID, int param_ID)
{
    if (!problem_exists(pID) || param_ID >= num_problem_params(pID))
    {
        return nullptr;
    }
    return problems.at(pID)->prob_params[param_ID].name.c_str();
}

/**
 * \return value current set for problem parameter
 */
int ProblemManager::problem_param_val(int pID, int param_ID)
{
    if (!problem_exists(pID)  || param_ID >= num_problem_params(pID))
    {
        return 0;
    }
    return problems.at(pID)->prob_params[param_ID].value;
}

/**
 * \brief Note: asserts that there is at least one problem
 * \return The first (from iterator - not necessarily lowest) pID in the problem set
 */
int ProblemManager::first_pid() const
{
    const bool problemsNotEmpty = !(problems.empty());
    assert(problemsNotEmpty);
    return problems.begin()->first;
}

/**
 * \return the resource str id
 */
int ProblemManager::get_problem_explanation_str_id(int pID)
{
    if (!problem_exists(pID))
    {
        return -1;
    }
    return problems[pID]->explanation_id;
}


