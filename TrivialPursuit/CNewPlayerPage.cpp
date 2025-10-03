#include "pch.h"
#include "TrivialPursuit.h"
#include "CNewPlayerPage.h"
#include "CPlaySetupDlg.h"

IMPLEMENT_DYNAMIC(CNewPlayerPage, CMFCPropertyPage)

CNewPlayerPage::CNewPlayerPage() : CMFCPropertyPage(IDD_NEWPLAYER)
{
    m_hollowBrush.CreateStockObject(HOLLOW_BRUSH);
}

CNewPlayerPage::~CNewPlayerPage()
{
}

void CNewPlayerPage::DoDataExchange(CDataExchange* pDX)
{
    CMFCPropertyPage::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNewPlayerPage, CMFCPropertyPage)
    ON_BN_CLICKED(IDOK, &CNewPlayerPage::OnBnClickedOk)
    ON_BN_CLICKED(IDCANCEL, &CNewPlayerPage::OnBnClickedCancel)
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

BOOL CNewPlayerPage::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
    {
        // If Enter is pressed while the edit box has focus, treat it as clicking OK
        if (GetFocus() == GetDlgItem(IDC_EDIT_NEWNAME))
        {
            OnBnClickedOk();
            return TRUE; // Message handled
        }
    }
    return CMFCPropertyPage::PreTranslateMessage(pMsg);
}

BOOL CNewPlayerPage::OnSetActive()
{
    CMFCPropertyPage::OnSetActive();
    SetDlgItemText(IDC_EDIT_NEWNAME, L"");
    GetDlgItem(IDC_EDIT_NEWNAME)->SetFocus();
    return TRUE;
}

void CNewPlayerPage::OnBnClickedOk()
{
    CString name;
    GetDlgItemText(IDC_EDIT_NEWNAME, name);
    name.Trim();
    if (name.IsEmpty()) {
        AfxMessageBox(L"Please enter a player name.");
        return;
    }

    CPlaySetupDlg* pHost = (CPlaySetupDlg*)GetParent();
    if (pHost) {
        pHost->SetLastPlayerName(name);
        // **FIXED**: Use the new getter function
        pHost->ShowPage(pHost->GetGameplayPage());
    }
}

void CNewPlayerPage::OnBnClickedCancel()
{
    // back to player select
    CPlaySetupDlg* pHost = (CPlaySetupDlg*)GetParent();
    if (pHost) {
        // **FIXED**: Use the new getter function
        pHost->ShowPage(pHost->GetPlayerSelectPage());
    }
}
HBRUSH CNewPlayerPage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    // Make the property page itself and static controls transparent
    if (nCtlColor == CTLCOLOR_DLG || nCtlColor == CTLCOLOR_STATIC)
    {
        pDC->SetBkMode(TRANSPARENT);
        return m_hollowBrush;
    }

    return CMFCPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);
}