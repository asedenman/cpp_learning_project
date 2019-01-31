#pragma once
#include <string>

class ProblemBase
{
public:
	ProblemBase();
	~ProblemBase();

    virtual std::string Solve();

    virtual void InitProblem();

    static void CALLBACK ProblemProc(UINT, UINT, DWORD, DWORD, DWORD);
};

inline void ProblemBase::ProblemProc(UINT, UINT, DWORD, DWORD, DWORD)
{
}

