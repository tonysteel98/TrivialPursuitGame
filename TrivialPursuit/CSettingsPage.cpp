#include "pch.h"
#include "TrivialPursuit.h"
#include "CSettingsPage.h"
#include "CPlaySetupDlg.h"

IMPLEMENT_DYNAMIC(CSettingsPage, CMFCPropertyPage)

CSettingsPage::CSettingsPage() : CMFCPropertyPage(IDD_SETTINGS)
{
    m_hollowBrush.CreateStockObject(HOLLOW_BRUSH);
}

CSettingsPage::~CSettingsPage()
{
}

void CSettingsPage::DoDataExchange(CDataExchange* pDX)
{
    CMFCPropertyPage::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSettingsPage, CMFCPropertyPage)
    ON_BN_CLICKED(IDC_BUTTON_UPDATE, &CSettingsPage::OnBnClickedUpdate)
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

BOOL CSettingsPage::OnSetActive()
{
    CMFCPropertyPage::OnSetActive();
    CPlaySetupDlg* pHost = (CPlaySetupDlg*)GetParent();
    if (pHost) {
        // Load current settings into edit boxes
        SetDlgItemInt(IDC_EDIT_LIVES, pHost->GetGameLives());
        SetDlgItemInt(IDC_EDIT_MAXSCORE, pHost->GetMaxScore());
    }
    return TRUE;
}

void CSettingsPage::OnBnClickedUpdate()
{
    CPlaySetupDlg* pHost = (CPlaySetupDlg*)GetParent();
    if (!pHost) return;

    BOOL bSuccess1, bSuccess2;
    int lives = GetDlgItemInt(IDC_EDIT_LIVES, &bSuccess1);
    int maxScore = GetDlgItemInt(IDC_EDIT_MAXSCORE, &bSuccess2);

    if (!bSuccess1 || !bSuccess2 || lives <= 0 || maxScore <= 0) {
        AfxMessageBox(L"Please enter valid, positive numbers for lives and max score.", MB_OK | MB_ICONERROR);
        return;
    }

    pHost->SetGameSettings(lives, maxScore);
    AfxMessageBox(L"Settings updated successfully!", MB_OK | MB_ICONINFORMATION);
}

HBRUSH CSettingsPage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    // Make the property page itself and static controls transparent
    if (nCtlColor == CTLCOLOR_DLG || nCtlColor == CTLCOLOR_STATIC)
    {
        pDC->SetBkMode(TRANSPARENT);
        return m_hollowBrush;
    }

    return CMFCPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);
}