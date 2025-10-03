#include "pch.h"
#include "TrivialPursuit.h"
#include "CPlaySetupDlg.h"
#include "resource.h"

IMPLEMENT_DYNAMIC(CPlaySetupDlg, CDialogEx)

CPlaySetupDlg::CPlaySetupDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_PLAY_SETUP, pParent),
    m_pCurrentPage(nullptr),
    m_lastGameScore(0),
    m_nGameLives(3),
    m_nMaxScore(10)
{
}

CPlaySetupDlg::~CPlaySetupDlg()
{
}

void CPlaySetupDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPlaySetupDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_PLAY, &CPlaySetupDlg::OnBnClickedButtonPlay)
    ON_BN_CLICKED(IDC_BUTTON_ADMIN, &CPlaySetupDlg::OnBnClickedButtonAdmin)
    ON_BN_CLICKED(IDC_BUTTON_HIGH_SCORES, &CPlaySetupDlg::OnBnClickedButtonHighScores)
    ON_BN_CLICKED(IDC_BUTTON_SETTINGS, &CPlaySetupDlg::OnBnClickedButtonSettings)
    ON_BN_CLICKED(IDC_BUTTON_BACK, &CPlaySetupDlg::OnBnClickedButtonBack)
    ON_WM_SIZE()
    ON_WM_ERASEBKGND()
    ON_WM_CTLCOLOR()
    ON_WM_DRAWITEM()
END_MESSAGE_MAP()


BOOL CPlaySetupDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    m_backgroundManager.Initialize(IDB_BACKGROUND);

    // --- CORRECTED PNG RESOURCE LOADING ---
    // Reverting to your reliable stream-based loading.
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
        AfxMessageBox(L"Failed to load main logo image.");
    }
    // --- The drawing is now handled by OnDrawItem. No SetBitmap call is needed. ---

    GetDlgItem(IDC_CHILDHOST)->GetWindowRect(&m_rcPageHost);
    ScreenToClient(&m_rcPageHost);

    m_pagePlayerSelect.Create(IDD_PLAYER_SELECT, this);
    m_pageNewPlayer.Create(IDD_NEWPLAYER, this);
    m_pageGameplay.Create(IDD_GAMEPLAY_DIALOG, this);
    m_pageFinal.Create(IDD_FINALSCORE, this);
    m_pageAdmin.Create(IDD_ADMIN_DIALOG, this);
    m_pageScores.Create(IDD_HIGHSCORES, this);
    m_pageSettings.Create(IDD_SETTINGS, this);

    ShowMainMenu();

    return TRUE;
}
void CPlaySetupDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    if (nIDCtl == IDC_LOGO_MAIN)
    {
        if (!m_logoImage.IsNull())
        {
            CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
            CRect rect(lpDrawItemStruct->rcItem);
            m_logoImage.Draw(pDC->GetSafeHdc(), rect);
        }
    }
    else
    {
        CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
    }
}

void CPlaySetupDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialogEx::OnSize(nType, cx, cy);
    if (GetDlgItem(IDC_CHILDHOST) && GetDlgItem(IDC_CHILDHOST)->GetSafeHwnd())
    {
        GetDlgItem(IDC_CHILDHOST)->GetWindowRect(&m_rcPageHost);
        ScreenToClient(&m_rcPageHost);
        if (m_pCurrentPage && m_pCurrentPage->GetSafeHwnd())
        {
            m_pCurrentPage->MoveWindow(&m_rcPageHost);
        }
    }
}

void CPlaySetupDlg::HideAllPages()
{
    m_pagePlayerSelect.ShowWindow(SW_HIDE);
    m_pageNewPlayer.ShowWindow(SW_HIDE);
    m_pageGameplay.ShowWindow(SW_HIDE);
    m_pageFinal.ShowWindow(SW_HIDE);
    m_pageAdmin.ShowWindow(SW_HIDE);
    m_pageScores.ShowWindow(SW_HIDE);
    m_pageSettings.ShowWindow(SW_HIDE);
    m_pCurrentPage = nullptr;
}

void CPlaySetupDlg::ShowPage(CMFCPropertyPage* pPage)
{
    if (!pPage || !pPage->GetSafeHwnd()) return;

    // Hide main menu buttons AND THE LOGO
    GetDlgItem(IDC_BUTTON_PLAY)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_BUTTON_ADMIN)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_BUTTON_HIGH_SCORES)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_BUTTON_SETTINGS)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_LOGO_MAIN)->ShowWindow(SW_HIDE); // <-- HIDE LOGO

    HideAllPages();

    m_pCurrentPage = pPage;
    m_pCurrentPage->MoveWindow(&m_rcPageHost);
    m_pCurrentPage->ShowWindow(SW_SHOW);
    m_pCurrentPage->SetFocus();
    m_pCurrentPage->OnSetActive();

    CWnd* pBack = GetDlgItem(IDC_BUTTON_BACK);
    pBack->ShowWindow(SW_SHOW);
    pBack->EnableWindow(TRUE);
    pBack->Invalidate();
    pBack->UpdateWindow();
}

void CPlaySetupDlg::ShowMainMenu()
{
    HideAllPages();

    // Show main menu buttons AND THE LOGO
    GetDlgItem(IDC_BUTTON_PLAY)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_BUTTON_ADMIN)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_BUTTON_HIGH_SCORES)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_BUTTON_SETTINGS)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_LOGO_MAIN)->ShowWindow(SW_SHOW); // <-- SHOW LOGO

    CWnd* pBack = GetDlgItem(IDC_BUTTON_BACK);
    pBack->ShowWindow(SW_HIDE);
    pBack->EnableWindow(FALSE);
}

void CPlaySetupDlg::OnBnClickedButtonPlay() { ShowPage(&m_pagePlayerSelect); }
void CPlaySetupDlg::OnBnClickedButtonAdmin() { ShowPage(&m_pageAdmin); }
void CPlaySetupDlg::OnBnClickedButtonHighScores() { ShowPage(&m_pageScores); }
void CPlaySetupDlg::OnBnClickedButtonSettings() { ShowPage(&m_pageSettings); }
void CPlaySetupDlg::OnBnClickedButtonBack() { ShowMainMenu(); }

BOOL CPlaySetupDlg::OnEraseBkgnd(CDC* pDC)
{
    if (m_backgroundManager.EraseBkgnd(pDC))
    {
        return TRUE;
    }
    return CDialogEx::OnEraseBkgnd(pDC);
}

HBRUSH CPlaySetupDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = m_backgroundManager.CtlColor(pDC, pWnd, nCtlColor);
    if (hbr != (HBRUSH)GetStockObject(NULL_BRUSH))
    {
        return hbr;
    }
    return CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
}
