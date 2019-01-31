#pragma once
#include <string>
#include <utility>
#include <vector>

class Prob_base
{
public:
    explicit Prob_base(int explanationResID) : explanation_id(explanationResID){}

    virtual ~Prob_base() = default;

    int number_of_parameters() const {return prob_params.size();}

    const int explanation_id;

    bool set_params(const std::vector<long long>& new_params){
        if (new_params.size() == number_of_parameters())
        {
            for (int i = 0; i < prob_params.size(); ++i)
            {
                prob_params[i].value = new_params[i];
            }
            return true;
        }
        return false;
    }

    virtual std::wstring solve(const std::vector<long long>& new_params){return nullptr;};

    struct ProblemParam final
    {
        std::wstring name;
        long long value;
        ProblemParam(std::wstring name, long long val) : name(std::move(name)), value(val){}
    };

    std::vector<ProblemParam> prob_params;

};



