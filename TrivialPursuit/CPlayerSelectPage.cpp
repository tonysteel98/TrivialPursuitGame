#include "pch.h"
#include "TrivialPursuit.h"
#include "CPlayerSelectPage.h"
#include "CPlaySetupDlg.h"

IMPLEMENT_DYNAMIC(CPlayerSelectPage, CMFCPropertyPage)

CPlayerSelectPage::CPlayerSelectPage()
	: CMFCPropertyPage(IDD_PLAYER_SELECT)
{
	m_hollowBrush.CreateStockObject(HOLLOW_BRUSH);
}

CPlayerSelectPage::~CPlayerSelectPage()
{
}

void CPlayerSelectPage::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPlayerSelectPage, CMFCPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_NEWPLAYER, &CPlayerSelectPage::OnBnClickedNewPlayer)
	ON_BN_CLICKED(IDC_BUTTON_CONTINUE, &CPlayerSelectPage::OnBnClickedContinue)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

BOOL CPlayerSelectPage::OnInitDialog()
{
	CMFCPropertyPage::OnInitDialog();
	return TRUE;
}

// In CPlayerSelectPage.cpp
BOOL CPlayerSelectPage::OnSetActive()
{
	CMFCPropertyPage::OnSetActive();
	CPlaySetupDlg* pHost = (CPlaySetupDlg*)GetParent();
	if (pHost) {
		CString last = pHost->GetLastPlayerName();

		// Correctly formatted label
		CString label;
		label.Format(L"Current player: %s", last.IsEmpty() ? L"none" : last);
		SetDlgItemText(IDC_STATIC_CURRENTPLAYER, label);
	}
	return TRUE;
}
void CPlayerSelectPage::OnBnClickedNewPlayer()
{
	CPlaySetupDlg* pHost = (CPlaySetupDlg*)GetParent();
	if (pHost) {
		pHost->ShowPage(pHost->GetNewPlayerPage());
	}
}

void CPlayerSelectPage::OnBnClickedContinue()
{
	CPlaySetupDlg* pHost = (CPlaySetupDlg*)GetParent();
	if (!pHost) return;

	CString last = pHost->GetLastPlayerName();
	if (last.IsEmpty()) {
		AfxMessageBox(L"No previous player found. Please create a new player first.");
		return;
	}

	pHost->ShowPage(pHost->GetGameplayPage());
}

HBRUSH CPlayerSelectPage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	// Make the property page itself and static controls transparent
	if (nCtlColor == CTLCOLOR_DLG || nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return m_hollowBrush;
	}

	return CMFCPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);
}