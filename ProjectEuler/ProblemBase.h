#pragma once
#include <string>
#include <utility>
#include <vector>

class Prob_base
{
public:
    explicit Prob_base(int explanationResID) : explanationID(explanationResID){}

    virtual ~Prob_base() = default;

    int numberOfParameters() const {return Params.size();}

    const int explanationID;

    bool SetParams(const std::vector<long long>& params){
        if (params.size() == numberOfParameters())
        {
            for (int i = 0; i < params.size(); ++i)
            {
                Params[i].Value = params[i];
            }
            return true;
        }
        return false;
    }

    virtual std::wstring Solve(const std::vector<long long>& params){return nullptr;};

    struct ProblemParam final
    {
        std::wstring Name;
        long long Value;
        ProblemParam(std::wstring name, long long val) : Name(std::move(name)), Value(val){}
    };

    std::vector<ProblemParam> Params;

};



