#pragma once
#include "WindowBase.h"
#include <string>

class ProblemWindow :
	public WindowBase
{
public:
	ProblemWindow();
	~ProblemWindow();

    static ProblemWindow* Create(HINSTANCE hInst, HWND parent_hwnd);


protected:
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
    void PaintContent(PAINTSTRUCT* pps) override;
    LPCTSTR ClassName() override;
    BOOL WinRegisterClass(WNDCLASS* pwc) override;
    virtual void Solve();

private:
    std::string Name;
    std::wstring Answer;

};

