#include "stdafx.h"
#include "ProblemWindow.h"
#include "Prob15.h"
#include <commctrl.h>
#include <winuser.h>
#include <cassert>
#include <algorithm>

#define IDC_SOLVE_BN 1000
#define PARAM_EDIT_RANGE_START 3000
#define PARAM_EDIT_RANGE_END 3100
#define PARAM_TEXT_RANGE_START 4000
#define PARAM_TEXT_RANGE_END 4100
#define BUTTON_MAXWIDTH 150
#define BUTTON_HEIGHT 20
#define BUTTON_WIDTH_BUFFER 5
#define ANSWER_MIN_WIDTH 100
#define GAP 10
#define IDC_LISTBOX 1001

LRESULT ProblemWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HWND hwnd_List;
    switch (uMsg)
    {
    case WM_CREATE:
        hwnd_List = init_window();
        return 0;
    case WM_SIZE:
        resize_elements();
        return 0;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_SOLVE_BN:
            solve();
            return 0;
        case IDC_LISTBOX:
            switch (HIWORD(wParam))
            {
            case LBN_SELCHANGE:
                {
                    // Get selected index.
                    int lbItem = (int)SendMessage(hwnd_List, LB_GETCURSEL, 0, 0);

                    // Get item data.
                    int i = (int)SendMessage(hwnd_List, LB_GETITEMDATA, lbItem, 0);

                    display_problem(i);
                    resize_elements();
                    return 0;
                }
			default:
                break;
            }
        default:
            break;
        }
        break;
    default:
        return WindowBase::HandleMessage(uMsg, wParam, lParam);
    }
    return WindowBase::HandleMessage(uMsg, wParam, lParam);
}

void ProblemWindow::PaintContent(PAINTSTRUCT* pps)
{
    RECT t_rect;
    static std::wstring DisplayText;
    DisplayText = (prob_expl + TEXT("\n\n") + prob_ans);
    GetClientRect(h_answerbox, &t_rect);
    InflateRect(&t_rect, -GAP, -GAP);
    DrawText(GetDC(h_answerbox), DisplayText.c_str(), DisplayText.length(), &t_rect, DT_WORDBREAK);
}

ProblemWindow* ProblemWindow::Create(HINSTANCE hInst,
                                     HWND parent_hwnd,
                                     HMENU id,
                                     int x_0,
                                     int y_0,
                                     int width,
                                     int height)
{
    auto self = new ProblemWindow();
    if (self && self->WinCreateWindow(hInst, WS_EX_CLIENTEDGE, TEXT("ProgramWin"), WS_CHILD | WS_VISIBLE, x_0, y_0,
                                      width, height, parent_hwnd, id))
    {
        return self;
    }
    delete self;
    return nullptr;
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

int ProblemWindow::calc_width_of_text(const wchar_t* text) const
{
    HDC hDC = GetDC(NULL);
    RECT r  = {0, 0, 0, 0};
    DrawText(hDC, text, wcslen(text), &r, DT_CALCRECT | DT_NOPREFIX | DT_SINGLELINE);
    return abs(r.right - r.left);
}


/**
 * \brief filters for problem parameter edit and static controls
 */
BOOL ProblemWindow::DestroyParamControls(HWND child_hwnd, LPARAM lParam)
{
    const int child_ID = (int)GetMenu(child_hwnd);

    if (child_ID >= PARAM_EDIT_RANGE_START && child_ID <= PARAM_EDIT_RANGE_END || child_ID >= PARAM_TEXT_RANGE_START &&
        child_ID <= PARAM_TEXT_RANGE_END)
    {
        DestroyWindow(child_hwnd);
    }
    return TRUE;
}



/**
 * \brief clears old problem controls then creates controls for new problem. new problem controls require resizing
 * \param newId new problem ID
 */
void ProblemWindow::display_problem(int newId)
{
    EnumChildWindows(m_hwnd, DestroyParamControls, NULL);

    h_prob_param_control.clear();
    h_prob_param_text.clear();
    prob_ans.clear();
    prob_expl.clear();

    current_problem_id = newId;
    for (int i = 0; i < manager->num_problem_params(newId); ++i)
    {
        HWND temp_handle = CreateWindowEx(NULL, WC_STATIC, NULL, WS_VISIBLE | WS_CHILD | SS_RIGHT, 10, i * 21, 100, 20,
                                          m_hwnd, (HMENU)(PARAM_TEXT_RANGE_START + i),
                                          (HINSTANCE)GetWindowLong(m_hwnd, GWL_HINSTANCE), NULL);
        if (manager->problem_param_chars(newId, i))
        {
            SetWindowText(temp_handle, manager->problem_param_chars(newId, i));
        }
        h_prob_param_text.push_back(temp_handle);

        temp_handle = CreateWindowEx(WS_EX_CLIENTEDGE, WC_EDIT, NULL, WS_VISIBLE | WS_CHILD | ES_NUMBER | ES_LEFT, 10,
                                     i * 21, 100, 20, m_hwnd, (HMENU)(PARAM_EDIT_RANGE_START + i),
                                     (HINSTANCE)GetWindowLong(m_hwnd, GWL_HINSTANCE), NULL);
        Edit_SetText(temp_handle, std::to_wstring(manager->problem_param_val(newId, i)).c_str());
        h_prob_param_control.push_back(temp_handle);
    }

    wchar_t buffer[4097]; //4097 largest str load string can hold
    LoadString(NULL, manager->get_problem_explanation_str_id(newId), buffer, sizeof(buffer) / sizeof(WCHAR));
    prob_expl = buffer;
}

HWND ProblemWindow::init_window()
{
    manager = std::make_shared<ProblemManager>();
    assert(manager);

    current_problem_id = manager->first_pid();

    int maxPIDTextWidth = 0;
    std::wstring pIDAsString;
    for (auto it = manager->problems.begin(); it != manager->problems.end(); ++it)
    {
        pIDAsString            = (std::to_wstring(it->first));
        const int pIDTextWidth = calc_width_of_text(pIDAsString.c_str());
        if (pIDTextWidth > maxPIDTextWidth)
        {
            maxPIDTextWidth = pIDTextWidth;
        }
    }
    min_width_prob_bn = maxPIDTextWidth + BUTTON_WIDTH_BUFFER;

    HWND list_hwnd_result = create_problem_list();

    display_problem(current_problem_id);

    CreateWindow(WC_BUTTON,TEXT("Solve"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 120, 10, 100, 20,
                     m_hwnd, (HMENU)IDC_SOLVE_BN, (HINSTANCE)GetWindowLong(m_hwnd, GWL_HINSTANCE), NULL);

    h_answerbox = CreateWindowEx(NULL, WC_STATIC, TEXT("AnswerBox"), WS_CHILD | WS_VISIBLE | SS_LEFT | SS_GRAYFRAME,
                                 100, 0, 100, 100, m_hwnd, NULL, (HINSTANCE)GetWindowLong(m_hwnd, GWL_HINSTANCE), NULL);

    return list_hwnd_result;
}

HWND ProblemWindow::create_problem_list() const
{
    HWND listBox =        CreateWindow(WC_LISTBOX, TEXT("ProblemSelectList"), LBS_STANDARD | WS_VISIBLE | WS_CHILD,
		                                0, 0, 10, 10, m_hwnd, (HMENU)IDC_LISTBOX, (HINSTANCE)GetWindowLong(m_hwnd, GWL_HINSTANCE), NULL);

    for (auto it = manager->problems.begin(); it != manager->problems.end(); ++it)
    {
        int pos = (int)SendMessage(listBox, LB_ADDSTRING, 0,
                                   (LPARAM)(std::to_wstring(it->first).c_str()));
        SendMessage(listBox, LB_SETITEMDATA, pos, (LPARAM)(it->first));
    }
    // Set input focus to the list box.
    SetFocus(listBox);

    return listBox;
}



void ProblemWindow::resize_elements()
{
    RECT window_rect;
    GetClientRect(m_hwnd, &window_rect);
    InflateRect(&window_rect, -GAP, -GAP);

    const int height = window_rect.bottom - window_rect.top;

    const int width = min(BUTTON_MAXWIDTH, (window_rect.right - window_rect.left) / 3);

    MoveWindow(FindWindowEx(m_hwnd, NULL, WC_LISTBOX, TEXT("ProblemSelectList")), window_rect.left, window_rect.top,
               max(width, min_width_prob_bn), height, false);

    window_rect.left += max(width, min_width_prob_bn) + GAP;

    int current_y = window_rect.top;
    assert(h_prob_param_control.size() == h_prob_param_text.size());
    for (int i = 0; i < h_prob_param_control.size(); ++i)
    {
        MoveWindow(h_prob_param_text[i], window_rect.left, current_y, width * 0.9f, BUTTON_HEIGHT, false);
        MoveWindow(h_prob_param_control[i], window_rect.left + (width * 1.2f), current_y, width * 0.9f,
                   BUTTON_HEIGHT, false);
        current_y += BUTTON_HEIGHT + GAP;
    }

    MoveWindow(FindWindowEx(m_hwnd, NULL, WC_BUTTON,TEXT("Solve")), window_rect.left + width, current_y, width,
               BUTTON_HEIGHT, false);

    window_rect.left += (width * 2) + GAP + GAP;

    MoveWindow(h_answerbox, window_rect.left, window_rect.top,
               max(window_rect.right - window_rect.left, ANSWER_MIN_WIDTH), height, false);

    MarkForRefresh();
}

void ProblemWindow::MarkForRefresh() const
{
    InvalidateRect(m_hwnd, NULL, true);
}


/**
 * \brief stores answer to current problem
 */
void ProblemWindow::solve()
{
    const int numParams = manager->num_problem_params(current_problem_id);
    std::vector<long long> params(numParams);

    std::wstring title;
    for (int i = 0; i < numParams; ++i)
    {
        title.reserve(GetWindowTextLength(h_prob_param_control[i]) + 1);
        if (!GetWindowText(h_prob_param_control[i], const_cast<WCHAR *>(title.c_str()), title.capacity()))
        {
            throw GetLastError();
        }
        params[i] = std::wcstol(title.c_str(), nullptr, 0);
        title.clear();
    }
    prob_ans = manager->answer_to_prob(current_problem_id, params);

    MarkForRefresh();
}

