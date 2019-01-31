#pragma once
#include "stdafx.h"
#include <ole2.h>
#include <shlobj.h>


/*
 * from: https://blogs.msdn.microsoft.com/oldnewthing/20050422-08/?p=35813
 */
class WindowBase
{
public:
	HWND GetHWND() {return m_hwnd;}

protected:
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    virtual void PaintContent(PAINTSTRUCT *pps){}
    virtual LPCTSTR ClassName() = 0;
    virtual BOOL WinRegisterClass(WNDCLASS *pwc){return RegisterClass(pwc);}
    virtual ~WindowBase() = default;

    HWND WinCreateWindow(HINSTANCE hInst, DWORD dwExStyle, LPCTSTR pszName, DWORD dwStyle, int x, int y, int cx, int cy, HWND hwndParent, HMENU hmenu)
    {
        Register(hInst);
        return CreateWindowEx(dwExStyle, ClassName(), pszName, dwStyle, x, y, cx, cy, hwndParent, hmenu, hInst, this);

    }

private:
    void Register(HINSTANCE hInst);
    void OnPaint();
    void OnPrintClient(HDC hdc);
    static LRESULT CALLBACK s_WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
protected:
    HWND m_hwnd;

};



