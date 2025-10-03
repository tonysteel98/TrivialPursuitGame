#include "pch.h"
#include "TrivialPursuit.h"
#include "CHighScoresPage.h"
#include "afxdialogex.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

IMPLEMENT_DYNAMIC(CHighScoresPage, CMFCPropertyPage)

CHighScoresPage::CHighScoresPage() : CMFCPropertyPage(IDD_HIGHSCORES)
{
	m_hollowBrush.CreateStockObject(HOLLOW_BRUSH);
}

CHighScoresPage::~CHighScoresPage()
{
}

void CHighScoresPage::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHighScoresPage, CMFCPropertyPage)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

BOOL CHighScoresPage::OnInitDialog()
{
	CMFCPropertyPage::OnInitDialog();
	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST_SCORES);
	if (pList) {
		pList->InsertColumn(0, L"Player", LVCFMT_LEFT, 200);
		pList->InsertColumn(1, L"Score", LVCFMT_LEFT, 100);
		pList->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	}
	return TRUE;
}

BOOL CHighScoresPage::OnSetActive()
{
	CMFCPropertyPage::OnSetActive();
	RefreshScores();
	return TRUE;
}

void CHighScoresPage::RefreshScores()
{
	std::vector<std::pair<std::string, int>> scores;
	std::ifstream ifs("HighScores.csv");
	if (!ifs.is_open()) return;

	std::string line;
	std::getline(ifs, line); // skip header

	while (std::getline(ifs, line)) {
		std::stringstream ss(line);
		std::string id, player, scorestr;
		if (std::getline(ss, id, ',') && std::getline(ss, player, ',') && std::getline(ss, scorestr)) {
			try {
				scores.push_back({ player, std::stoi(scorestr) });
			}
			catch (...) { /* ignore conversion errors */ }
		}
	}
	ifs.close();

	// sort scores descending
	std::sort(scores.begin(), scores.end(), [](const auto& a, const auto& b) {
		return a.second > b.second;
	});

	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST_SCORES);
	if (!pList) return;

	pList->DeleteAllItems();
	int i = 0;
	for (const auto& pr : scores) {
		pList->InsertItem(i, CString(pr.first.c_str()));
		CString sc;
		sc.Format(L"%d", pr.second);
		pList->SetItemText(i, 1, sc);
		i++;
	}
}

HBRUSH CHighScoresPage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	// Make the property page itself and static controls transparent
	if (nCtlColor == CTLCOLOR_DLG || nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return m_hollowBrush;
	}

	return CMFCPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);
}