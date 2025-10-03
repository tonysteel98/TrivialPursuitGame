// TrivialPursuitDlg.h : header file
//
#pragma once
#include "afxwin.h"
#include "BackgroundUtils.h" // Include our new helper

class CTrivialPursuitDlg : public CDialogEx
{
    // Construction
public:
    CTrivialPursuitDlg(CWnd* pParent = nullptr); // standard constructor
    // Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_TRIVIALPURSUIT_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support

    // Implementation
protected:
    HICON m_hIcon;

    // Background and Logo members
    CBackgroundManager m_backgroundManager;
    CImage m_logoImage;  // Use CImage for PNG support. CBitmap is no longer needed.

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct); // Add this handler
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnStnClickedLogoSplash();
};