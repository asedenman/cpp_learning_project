#pragma once
#include "WindowBase.h"
#include <string>
#include "ProblemManager.h"

class ProblemWindow :
    public WindowBase
{
public:

    static ProblemWindow* Create(HINSTANCE hInst, HWND parent_hwnd, HMENU id, int x_0, int y_0, int width, int height);

protected:
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
    void PaintContent(PAINTSTRUCT* pps) override;
    LPCTSTR ClassName() override;
    BOOL WinRegisterClass(WNDCLASS* pwc) override;
    
    void MarkForRefresh() const;
    static BOOL CALLBACK DestroyParamControls(HWND child_hwnd, LPARAM lParam);

private:
    
    std::vector<HWND> h_prob_param_control;
    std::vector<HWND> h_prob_param_text;
    HWND h_answerbox = nullptr;

    std::shared_ptr<ProblemManager> manager;
    int current_problem_id = 0;

    std::wstring prob_expl;
    std::wstring prob_ans;

    int min_width_prob_bn;

    int calc_width_of_text(const wchar_t* text) const;

    HWND init_window();
    HWND create_problem_list() const;
    void resize_elements();

    void display_problem(int newID);

    void solve();

};

