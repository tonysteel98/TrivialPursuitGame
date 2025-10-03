#pragma once
#include "afxpropertypage.h"

class CSettingsPage : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CSettingsPage)

public:
	CSettingsPage();
	virtual ~CSettingsPage();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETTINGS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnSetActive() override;
	DECLARE_MESSAGE_MAP()

private:
	CBrush m_hollowBrush; // Brush for transparency

public:
	afx_msg void OnBnClickedUpdate();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
