#include "stdafx.h"
#include "ProblemWindow.h"
#include "Problem15.h"


ProblemWindow::ProblemWindow()
{
}


ProblemWindow::~ProblemWindow()
{
}


LRESULT ProblemWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
	    case WM_LBUTTONDBLCLK:
            Solve();
            InvalidateRect(m_hwnd, NULL, true);

    }
    return WindowBase::HandleMessage(uMsg, wParam, lParam);
}

void ProblemWindow::PaintContent(PAINTSTRUCT* pps)
{

    RECT rc; 
    POINT aptStar[6] = {50,2, 2,98, 98,33, 2,33, 98,98, 50,2}; 
    HDC hdc = GetDC(m_hwnd); /*
    SetMapMode(hdc, MM_ANISOTROPIC); 
    SetWindowExtEx(hdc, 100, 100, NULL); 
    SetViewportExtEx(hdc, rc.right, rc.bottom, NULL); */
    //Polyline(hdc, aptStar, 6); 
    TextOut(hdc, 0, 0, Answer.c_str(), Answer.length() );
}

ProblemWindow* ProblemWindow::Create(HINSTANCE hInst, HWND parent_hwnd)
{
    ProblemWindow* self = new ProblemWindow();
    if(self && self->WinCreateWindow(hInst, WS_EX_CLIENTEDGE, TEXT("ProgramWin"), WS_CHILD | WS_VISIBLE, 200, 200, 100, 100, parent_hwnd, NULL))
    {
        return self;
    }
    delete self;
    return NULL;
}

LPCTSTR ProblemWindow::ClassName()
{
    return TEXT("ProblemWindow");
}

BOOL ProblemWindow::WinRegisterClass(WNDCLASS* pwc)
{
    pwc->style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    return WindowBase::WinRegisterClass(pwc);

}

void ProblemWindow::Solve()
{

    long long answer = Problem15::num_paths(20, 20);

    Answer = TEXT("Answer: ");
    Answer += std::to_wstring(answer);
}
