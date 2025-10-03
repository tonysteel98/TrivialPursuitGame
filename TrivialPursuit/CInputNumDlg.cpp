#include "pch.h"
#include "TrivialPursuit.h"
#include "CInputNumDlg.h"
#include "afxdialogex.h"
#include "resource.h"

IMPLEMENT_DYNAMIC(CInputNumDlg, CDialogEx)

CInputNumDlg::CInputNumDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_INPUT_NUMBER, pParent), m_nRowID(0)
{

}

CInputNumDlg::~CInputNumDlg()
{
}

void CInputNumDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    // Link the edit control to our member variable
    DDX_Text(pDX, IDC_EDIT_ROW_ID, m_nRowID);
}


BEGIN_MESSAGE_MAP(CInputNumDlg, CDialogEx)
    ON_WM_ERASEBKGND()
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

BOOL CInputNumDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    m_backgroundManager.Initialize(IDB_BACKGROUND);
    return TRUE;
}

void CInputNumDlg::OnOK()
{
    UpdateData(TRUE); // Get data from controls into variables
    if (m_nRowID <= 0) {
        AfxMessageBox(L"Please enter a valid, positive row number.");
        return;
    }
    CDialogEx::OnOK(); // Close the dialog
}

BOOL CInputNumDlg::OnEraseBkgnd(CDC* pDC)
{
    // Use our helper to draw the background
    if (m_backgroundManager.EraseBkgnd(pDC))
    {
        return TRUE;
    }
    return CDialogEx::OnEraseBkgnd(pDC);
}

HBRUSH CInputNumDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    // Use helper to make static controls transparent
    HBRUSH hbr = m_backgroundManager.CtlColor(pDC, pWnd, nCtlColor);
    if (hbr != (HBRUSH)GetStockObject(NULL_BRUSH))
    {
        return hbr;
    }
    return CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
}
