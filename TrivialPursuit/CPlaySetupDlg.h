#pragma once
#include "afxdialogex.h"
#include "afxpropertypage.h"
#include "resource.h"
#include "BackgroundUtils.h"
#include "CPlayerSelectPage.h"
#include "CNewPlayerPage.h"
#include "CGameplayPage.h"
#include "CFinalScorePage.h"
#include "CAdminPage.h"
#include "CHighScoresPage.h"
#include "CSettingsPage.h"

class CPlaySetupDlg : public CDialogEx
{
    DECLARE_DYNAMIC(CPlaySetupDlg)

public:
    CPlaySetupDlg(CWnd* pParent = nullptr);
    virtual ~CPlaySetupDlg();

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_PLAY_SETUP };
#endif

protected:
    virtual BOOL OnInitDialog() override;
    virtual void DoDataExchange(CDataExchange* pDX) override;
    DECLARE_MESSAGE_MAP()

private:
    // Pages
    CPlayerSelectPage m_pagePlayerSelect;
    CNewPlayerPage    m_pageNewPlayer;
    CGameplayPage     m_pageGameplay;
    CFinalScorePage   m_pageFinal;
    CAdminPage        m_pageAdmin;
    CHighScoresPage   m_pageScores;
    CSettingsPage     m_pageSettings;

    // Page management
    CMFCPropertyPage* m_pCurrentPage;
    CRect m_rcPageHost;

    // Shared Data
    CString m_lastPlayerName;
    int     m_lastGameScore;
    int     m_nGameLives;
    int     m_nMaxScore;

    // Background and Logo members
    CBackgroundManager m_backgroundManager;
    CImage m_logoImage;

    void HideAllPages();

public:
    void ShowPage(CMFCPropertyPage* pPage);
    void ShowMainMenu();

    void SetLastPlayerName(const CString& name) { m_lastPlayerName = name; }
    const CString& GetLastPlayerName() const { return m_lastPlayerName; }
    void SetLastGameScore(int s) { m_lastGameScore = s; }
    int GetLastGameScore() const { return m_lastGameScore; }
    void SetGameSettings(int lives, int maxScore) { m_nGameLives = lives; m_nMaxScore = maxScore; }
    int GetGameLives() const { return m_nGameLives; }
    int GetMaxScore() const { return m_nMaxScore; }
    CMFCPropertyPage* GetPlayerSelectPage() { return &m_pagePlayerSelect; }
    CMFCPropertyPage* GetNewPlayerPage() { return &m_pageNewPlayer; }
    CMFCPropertyPage* GetGameplayPage() { return &m_pageGameplay; }
    CMFCPropertyPage* GetFinalScorePage() { return &m_pageFinal; }

    afx_msg void OnBnClickedButtonPlay();
    afx_msg void OnBnClickedButtonAdmin();
    afx_msg void OnBnClickedButtonHighScores();
    afx_msg void OnBnClickedButtonSettings();
    afx_msg void OnBnClickedButtonBack();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
};

