#include "stdafx.h"
#include "WindowBase.h"
#include <winuser.h>




void WindowBase::Register(HINSTANCE hInst)
{
    WNDCLASS wc;
    SecureZeroMemory(&wc, sizeof(wc));
    wc.style         = 0;
    wc.lpfnWndProc   = WindowBase::s_WndProc;
    wc.cbClsExtra    = 0;
    wc.hInstance     = hInst;
    wc.hIcon         = NULL;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = ClassName();

    WinRegisterClass(&wc);
}



LRESULT WindowBase::s_WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    WindowBase* self;
    if (uMsg == WM_NCCREATE)
    {
        const auto lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
        self                = reinterpret_cast<WindowBase *>(lpcs->lpCreateParams);
        self->m_hwnd        = hwnd;
        SetWindowLongPtr(hwnd, GWLP_USERDATA,
                         reinterpret_cast<LPARAM>(self));
    }
    else
    {
        self = reinterpret_cast<WindowBase *>
            (GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }
    if (self)
    {
        return self->HandleMessage(uMsg, wParam, lParam);
    }
    else
    {
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}


LRESULT WindowBase::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT lres;

    switch (uMsg)
    {
    case WM_NCDESTROY:
        lres = DefWindowProc(m_hwnd, uMsg, wParam, lParam);
        SetWindowLongPtr(m_hwnd, GWLP_USERDATA, 0);
        delete this;
        return lres;
    case WM_PAINT:
        OnPaint();
        return 0;
    case WM_PRINTCLIENT:
        OnPrintClient(reinterpret_cast<HDC>(wParam));
        return 0;
    }

    return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}

void WindowBase::OnPaint()
{
    PAINTSTRUCT ps;
    BeginPaint(m_hwnd, &ps);
    PaintContent(&ps);
    EndPaint(m_hwnd, &ps);
}

void WindowBase::OnPrintClient(HDC hdc)
{
    PAINTSTRUCT ps;
    ps.hdc = hdc;
    GetClientRect(m_hwnd, &ps.rcPaint);
    PaintContent(&ps);
}
