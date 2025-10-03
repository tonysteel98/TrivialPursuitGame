#include "pch.h"
#include "TrivialPursuit.h"
#include "CGameplayPage.h"
#include "CPlaySetupDlg.h"
#include <atlconv.h>

IMPLEMENT_DYNAMIC(CGameplayPage, CMFCPropertyPage)

CGameplayPage::CGameplayPage() : CMFCPropertyPage(IDD_GAMEPLAY_DIALOG),
m_bMustRoll(true),
m_feedbackColor(RGB(0, 0, 0))
{
    m_hollowBrush.CreateStockObject(HOLLOW_BRUSH);
}

CGameplayPage::~CGameplayPage()
{
}

void CGameplayPage::DoDataExchange(CDataExchange* pDX)
{
    CMFCPropertyPage::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGameplayPage, CMFCPropertyPage)
    ON_BN_CLICKED(IDC_BUTTON_ROLL, &CGameplayPage::OnBnClickedRoll)
    ON_BN_CLICKED(IDC_BUTTON_SUBMIT, &CGameplayPage::OnBnClickedSubmit)
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


BOOL CGameplayPage::OnInitDialog()
{
    CMFCPropertyPage::OnInitDialog();
    return TRUE;
}

BOOL CGameplayPage::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
    {
        if (GetFocus() == GetDlgItem(IDC_EDIT_ANSWER))
        {
            OnBnClickedSubmit();
            return TRUE; // Message handled
        }
    }
    return CMFCPropertyPage::PreTranslateMessage(pMsg);
}

BOOL CGameplayPage::OnSetActive()
{
    CMFCPropertyPage::OnSetActive();
    CPlaySetupDlg* pHost = (CPlaySetupDlg*)GetParent();
    if (!pHost) return TRUE;

    m_playerName = pHost->GetLastPlayerName();
    if (m_playerName.IsEmpty()) {
        AfxMessageBox(L"No player selected. Returning to player selection.");
        pHost->ShowPage(pHost->GetPlayerSelectPage());
        return TRUE;
    }

    // Initialize game with settings from host
    std::string pname = std::string(CT2A(m_playerName, CP_UTF8));
    m_game.reset(new GameSetup(pname, pHost->GetGameLives(), pHost->GetMaxScore()));
    m_game->initializeGUI();

    // Reset UI for a new game using the new helper function
    UpdateStaticText(IDC_STATIC_QUESTION, L"Roll the dice to start your game!");
    SetDlgItemText(IDC_EDIT_ANSWER, L""); // EDIT controls are fine with SetDlgItemText
    UpdateStaticText(IDC_STATIC_FEEDBACK, L"");
    UpdateStaticText(IDC_STATIC_CORRECT_ANSWER, L"");
    UpdateStatusDisplay();

    // Enforce game flow
    m_bMustRoll = true;
    GetDlgItem(IDC_BUTTON_ROLL)->EnableWindow(TRUE);
    GetDlgItem(IDC_BUTTON_SUBMIT)->EnableWindow(FALSE);

    return TRUE;
}

// *** REVISED: Implementation for the helper function ***
// This function now correctly invalidates the area on the PARENT PROPERTY SHEET,
// which is responsible for drawing the background behind the transparent property page.
void CGameplayPage::UpdateStaticText(UINT nID, const CString& strText)
{
    CWnd* pStatic = GetDlgItem(nID);
    // Get the parent property sheet, which is responsible for drawing the background
    CWnd* pParentSheet = GetParent();

    if (pStatic && pStatic->GetSafeHwnd() && pParentSheet && pParentSheet->GetSafeHwnd())
    {
        CRect rect;
        pStatic->GetWindowRect(&rect); // Get the control's position in screen coordinates

        // Convert the screen coordinates to the coordinates of the PARENT property sheet
        pParentSheet->ScreenToClient(&rect);

        // Invalidate the rectangle on the property sheet to force it to redraw its background
        // behind our static control. The TRUE parameter ensures the background is erased.
        pParentSheet->InvalidateRect(&rect, TRUE);

        // Now that the background is scheduled to be redrawn, update the text on the control itself.
        pStatic->SetWindowText(strText);
    }
}


void CGameplayPage::UpdateStatusDisplay()
{
    if (!m_game) return;
    CString lives; lives.Format(L"Lives: %d", m_game->getLives());
    CString score; score.Format(L"Score: %d", m_game->getScore());

    // Use the new helper function for updating status text
    UpdateStaticText(IDC_STATIC_LIVES, lives);
    UpdateStaticText(IDC_STATIC_SCORE, score);
}

void CGameplayPage::OnBnClickedRoll()
{
    if (!m_game) return;
    if (!m_bMustRoll) {
        AfxMessageBox(L"You must submit an answer for the current question first.");
        return;
    }

    auto qa = m_game->pickQuestionFromCategory(m_game->rollCategory());
    CString q(qa.first.c_str());
    m_currentAnswer = CString(qa.second.c_str());

    // Use the new helper function to prevent text overlap
    UpdateStaticText(IDC_STATIC_QUESTION, q);
    SetDlgItemText(IDC_EDIT_ANSWER, L"");
    UpdateStaticText(IDC_STATIC_FEEDBACK, L"");
    UpdateStaticText(IDC_STATIC_CORRECT_ANSWER, L"");

    // Update game flow: now user must submit
    m_bMustRoll = false;
    GetDlgItem(IDC_BUTTON_ROLL)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_SUBMIT)->EnableWindow(TRUE);
    GetDlgItem(IDC_EDIT_ANSWER)->SetFocus();
}

void CGameplayPage::OnBnClickedSubmit()
{
    if (!m_game) return;
    if (m_bMustRoll) {
        AfxMessageBox(L"You need to roll the dice for a new question.");
        return;
    }

    CString ans;
    GetDlgItemText(IDC_EDIT_ANSWER, ans);
    ans.Trim();

    if (ans.IsEmpty()) {
        AfxMessageBox(L"Please enter an answer before submitting.", MB_OK | MB_ICONWARNING);
        return; // Don't penalize for empty answer
    }

    std::string userAns = std::string(CT2A(ans, CP_UTF8));
    bool correct = m_game->submitAnswerForGUI(userAns);

    if (correct) {
        m_feedbackColor = RGB(0, 180, 0); // Green
        UpdateStaticText(IDC_STATIC_FEEDBACK, L"Correct!");
    }
    else {
        m_feedbackColor = RGB(220, 0, 0); // Red
        UpdateStaticText(IDC_STATIC_FEEDBACK, L"Incorrect!");

        CString correctAnswerMsg;
        correctAnswerMsg.Format(L"The correct answer was: %s", (LPCTSTR)m_currentAnswer);
        UpdateStaticText(IDC_STATIC_CORRECT_ANSWER, correctAnswerMsg);
    }

    UpdateStatusDisplay();

    if (m_game->isGameOver()) {
        EndGame();
    }
    else {
        // Update game flow: now user must roll
        m_bMustRoll = true;
        GetDlgItem(IDC_BUTTON_ROLL)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_SUBMIT)->EnableWindow(FALSE);
    }
}

void CGameplayPage::EndGame()
{
    m_game->saveHighScore();
    CPlaySetupDlg* pHost = (CPlaySetupDlg*)GetParent();
    if (pHost) {
        pHost->SetLastGameScore(m_game->getScore());
        pHost->ShowPage(pHost->GetFinalScorePage());
    }
}

HBRUSH CGameplayPage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    // Handle feedback text color first
    if (pWnd->GetDlgCtrlID() == IDC_STATIC_FEEDBACK) {
        pDC->SetTextColor(m_feedbackColor);
    }

    // Make the property page and static controls transparent
    if (nCtlColor == CTLCOLOR_DLG || nCtlColor == CTLCOLOR_STATIC)
    {
        pDC->SetBkMode(TRANSPARENT);
        return m_hollowBrush;
    }

    return CMFCPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);
}

