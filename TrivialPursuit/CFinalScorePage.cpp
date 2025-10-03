#include "pch.h"
#include "TrivialPursuit.h"
#include "CFinalScorePage.h"
#include "CPlaySetupDlg.h"

IMPLEMENT_DYNAMIC(CFinalScorePage, CMFCPropertyPage)

CFinalScorePage::CFinalScorePage() : CMFCPropertyPage(IDD_FINALSCORE)
{
    m_hollowBrush.CreateStockObject(HOLLOW_BRUSH);
}

CFinalScorePage::~CFinalScorePage()
{
}

void CFinalScorePage::DoDataExchange(CDataExchange* pDX)
{
    CMFCPropertyPage::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFinalScorePage, CMFCPropertyPage)
    ON_BN_CLICKED(IDC_BUTTON_CONTINUE, &CFinalScorePage::OnBnClickedContinue)
    ON_BN_CLICKED(IDC_BUTTON_MAINMENU, &CFinalScorePage::OnBnClickedMainMenu)
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


BOOL CFinalScorePage::OnSetActive()
{
    CMFCPropertyPage::OnSetActive();
    CPlaySetupDlg* pHost = (CPlaySetupDlg*)GetParent();
    if (!pHost) return TRUE;

    // Set player name and score in separate controls
    CString playerName = pHost->GetLastPlayerName();
    SetDlgItemText(IDC_STATIC_PLAYER_NAME, playerName.IsEmpty() ? L"Player" : playerName);

    CString score;
    score.Format(L"Final Score: %d", pHost->GetLastGameScore());
    SetDlgItemText(IDC_STATIC_SCORE_VALUE, score);

    return TRUE;
}

void CFinalScorePage::OnBnClickedContinue()
{
    // Continue means play again with the same player
    CPlaySetupDlg* pHost = (CPlaySetupDlg*)GetParent();
    if (pHost) {
        pHost->ShowPage(pHost->GetGameplayPage());
    }
}

void CFinalScorePage::OnBnClickedMainMenu()
{
    CPlaySetupDlg* pHost = (CPlaySetupDlg*)GetParent();
    if (pHost) {
        pHost->ShowMainMenu();
    }
}

HBRUSH CFinalScorePage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    // Make the property page itself and static controls transparent
    if (nCtlColor == CTLCOLOR_DLG || nCtlColor == CTLCOLOR_STATIC)
    {
        pDC->SetBkMode(TRANSPARENT);
        return m_hollowBrush;
    }

    return CMFCPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);
}
