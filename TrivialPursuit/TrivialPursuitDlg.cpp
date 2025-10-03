#include "pch.h"
#include "framework.h"
#include "TrivialPursuit.h"
#include "TrivialPursuitDlg.h"
#include "afxdialogex.h"
#include "CPlaySetupDlg.h"   // include PlaySetup dialog
#include "resource.h"       // Make sure resource.h is included for IDs

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

    // Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Implementation
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTrivialPursuitDlg dialog

CTrivialPursuitDlg::CTrivialPursuitDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_TRIVIALPURSUIT_DIALOG, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDI_MAINFRAME);
}

void CTrivialPursuitDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTrivialPursuitDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_TIMER()      // for splash auto-close
    ON_WM_ERASEBKGND() // Add message map entry
    ON_WM_CTLCOLOR()   // Add message map entry
    ON_WM_DRAWITEM()   // Add the message map entry for Owner Draw
    ON_STN_CLICKED(IDC_LOGO_SPLASH, &CTrivialPursuitDlg::OnStnClickedLogoSplash)
END_MESSAGE_MAP()


// CTrivialPursuitDlg message handlers

BOOL CTrivialPursuitDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // Initialize the background manager
    m_backgroundManager.Initialize(IDB_BACKGROUND);

    // --- CORRECTED PNG RESOURCE LOADING ---
    // We are reverting to your reliable stream-based loading. My apologies for the error.
    IStream* pStream = nullptr;
    HGLOBAL hMem = NULL;
    HRSRC hRes = ::FindResource(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_LOGO_PNG), L"PNG");
    if (hRes)
    {
        HGLOBAL hResLoad = ::LoadResource(AfxGetInstanceHandle(), hRes);
        if (hResLoad)
        {
            void* pResLock = ::LockResource(hResLoad);
            DWORD dwSize = ::SizeofResource(AfxGetInstanceHandle(), hRes);
            hMem = ::GlobalAlloc(GMEM_MOVEABLE, dwSize);
            if (hMem)
            {
                void* pMem = ::GlobalLock(hMem);
                if (pMem && pResLock && dwSize > 0)
                {
                    memcpy(pMem, pResLock, dwSize);
                }

                ::GlobalUnlock(hMem);
                if (SUCCEEDED(::CreateStreamOnHGlobal(hMem, TRUE, &pStream)))
                {
                    m_logoImage.Load(pStream);
                    pStream->Release();
                }
            }
        }
    }

    if (m_logoImage.IsNull())
    {
        AfxMessageBox(L"Failed to load logo image.");
    }
    // --- The drawing is now handled by OnDrawItem. No SetBitmap call is needed. ---

    SetIcon(m_hIcon, TRUE);
    SetIcon(m_hIcon, FALSE);
    SetTimer(1, 3000, nullptr);

    return TRUE;
}

void CTrivialPursuitDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialogEx::OnSysCommand(nID, lParam);
    }
}

void CTrivialPursuitDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this);
        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        // We no longer draw the logo manually here. The picture control handles it.
        CDialogEx::OnPaint();
    }
}

HCURSOR CTrivialPursuitDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CTrivialPursuitDlg::OnTimer(UINT_PTR nIDEvent)
{
    if (nIDEvent == 1)
    {
        KillTimer(1);
        EndDialog(IDOK);
        CPlaySetupDlg dlg;
        dlg.DoModal();
        AfxGetMainWnd()->PostMessage(WM_CLOSE);
    }
    CDialogEx::OnTimer(nIDEvent);
}

void CTrivialPursuitDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    // Check if it is the correct control that needs drawing
    if (nIDCtl == IDC_LOGO_SPLASH)
    {
        // Ensure our logo image is loaded
        if (!m_logoImage.IsNull())
        {
            // Get the Device Context (DC) to draw on
            CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
            // Get the rectangle where we need to draw
            CRect rect(lpDrawItemStruct->rcItem);

            // CImage::Draw will handle the transparency (alpha blending) correctly.
            m_logoImage.Draw(pDC->GetSafeHdc(), rect);
        }
    }
    else
    {
        // If it's another control, let the base class handle it.
        CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
    }
}


BOOL CTrivialPursuitDlg::OnEraseBkgnd(CDC* pDC)
{
    if (m_backgroundManager.EraseBkgnd(pDC))
    {
        return TRUE;
    }
    return CDialogEx::OnEraseBkgnd(pDC);
}


HBRUSH CTrivialPursuitDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = m_backgroundManager.CtlColor(pDC, pWnd, nCtlColor);
    if (hbr != (HBRUSH)GetStockObject(NULL_BRUSH))
    {
        return hbr;
    }
    return CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
}
void CTrivialPursuitDlg::OnStnClickedLogoSplash()
{
    // TODO: Add your control notification handler code here
}
