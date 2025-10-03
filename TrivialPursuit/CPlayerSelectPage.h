#pragma once
#include "afxpropertypage.h" 

// Forward declaration
class CPlaySetupDlg;

class CPlayerSelectPage : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CPlayerSelectPage)

public:
	CPlayerSelectPage();
	virtual ~CPlayerSelectPage();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PLAYER_SELECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX) override;
	virtual BOOL OnInitDialog() override;
	virtual BOOL OnSetActive() override;
	DECLARE_MESSAGE_MAP()

private:
	CBrush m_hollowBrush; // Brush for transparency

public:
	afx_msg void OnBnClickedNewPlayer();
	afx_msg void OnBnClickedContinue();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
