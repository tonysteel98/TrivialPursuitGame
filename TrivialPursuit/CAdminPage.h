#pragma once
#include "afxpropertypage.h"
#include "CInputNumDlg.h" // Include the new dialog header

class CAdminPage : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CAdminPage)

public:
	CAdminPage();
	virtual ~CAdminPage();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADMIN_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog() override;
	virtual BOOL OnSetActive() override;
	DECLARE_MESSAGE_MAP()

private:
	void RefreshList();
	CBrush m_hollowBrush; // Brush for transparency

public:
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedDeleteRow();
	afx_msg void OnBnClickedDeleteAll();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
