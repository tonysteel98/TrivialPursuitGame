#pragma once
#include "afxpropertypage.h" 

class CHighScoresPage : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CHighScoresPage)

public:
	CHighScoresPage();
	virtual ~CHighScoresPage();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HIGHSCORES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog() override;
	virtual BOOL OnSetActive() override;
	DECLARE_MESSAGE_MAP()

private:
	void RefreshScores();
	CBrush m_hollowBrush; // Brush for transparency

public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
