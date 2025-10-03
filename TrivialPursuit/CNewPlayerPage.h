#pragma once
#include "afxpropertypage.h"

class CNewPlayerPage : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CNewPlayerPage)

public:
	CNewPlayerPage();
	virtual ~CNewPlayerPage();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEWPLAYER };
#endif

protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg) override; // To catch Enter key
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnSetActive() override;
	DECLARE_MESSAGE_MAP()

private:
	CBrush m_hollowBrush; // Brush for transparency

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
