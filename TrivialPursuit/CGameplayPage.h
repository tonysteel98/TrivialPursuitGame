#pragma once
#include "afxpropertypage.h"
#include "../TrivialPursuitCore/GameSetup.h"
#include <memory>

class CGameplayPage : public CMFCPropertyPage
{
    DECLARE_DYNAMIC(CGameplayPage)

public:
    CGameplayPage();
    virtual ~CGameplayPage();

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_GAMEPLAY_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX) override;
    virtual BOOL OnInitDialog() override;
    virtual BOOL OnSetActive() override;
    virtual BOOL PreTranslateMessage(MSG* pMsg) override; // For Enter key
    DECLARE_MESSAGE_MAP()

private:
    std::unique_ptr<GameSetup> m_game;
    CString m_playerName;
    CString m_currentAnswer;
    COLORREF m_feedbackColor;
    CBrush m_hollowBrush; // Brush for transparency

    // Game flow state
    bool m_bMustRoll;

    void UpdateStatusDisplay();
    void EndGame();

    // *** ADDED: Helper function to correctly update transparent static text ***
    void UpdateStaticText(UINT nID, const CString& strText);

public:
    afx_msg void OnBnClickedRoll();
    afx_msg void OnBnClickedSubmit();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
