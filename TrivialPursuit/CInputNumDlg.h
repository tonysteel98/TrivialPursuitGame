#pragma once
#include "afxdialogex.h"
#include "BackgroundUtils.h" // Include our new helper

class CInputNumDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInputNumDlg)

public:
	CInputNumDlg(CWnd* pParent = nullptr);
	virtual ~CInputNumDlg();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INPUT_NUMBER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog() override;
	DECLARE_MESSAGE_MAP()

private:
	CBackgroundManager m_backgroundManager;

public:
	int m_nRowID; // This will hold the number entered by the user
	virtual void OnOK();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);      // Add this handler
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor); // And this one
};
