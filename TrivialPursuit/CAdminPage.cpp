#include "pch.h"
#include "TrivialPursuit.h"
#include "CAdminPage.h"
#include "afxdialogex.h"
#include "../TrivialPursuitCore/FileReader.h"
#include "../TrivialPursuitCore/FileWriter.h"
#include "../TrivialPursuitCore/DeleteManager.h"
#include <atlconv.h>
#include <fstream>
#include <sstream>

IMPLEMENT_DYNAMIC(CAdminPage, CMFCPropertyPage)

CAdminPage::CAdminPage() : CMFCPropertyPage(IDD_ADMIN_DIALOG)
{
    m_hollowBrush.CreateStockObject(HOLLOW_BRUSH);
}

CAdminPage::~CAdminPage()
{
}

void CAdminPage::DoDataExchange(CDataExchange* pDX)
{
    CMFCPropertyPage::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAdminPage, CMFCPropertyPage)
    ON_BN_CLICKED(IDC_BUTTON_ADD, &CAdminPage::OnBnClickedAdd)
    ON_BN_CLICKED(IDC_BUTTON_DELETEROW, &CAdminPage::OnBnClickedDeleteRow)
    ON_BN_CLICKED(IDC_BUTTON_DELETEALL, &CAdminPage::OnBnClickedDeleteAll)
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


BOOL CAdminPage::OnInitDialog()
{
    CMFCPropertyPage::OnInitDialog();

    CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST_CUSTOM);
    if (pList) {
        pList->InsertColumn(0, L"ID", LVCFMT_LEFT, 50);
        pList->InsertColumn(1, L"Question", LVCFMT_LEFT, 400);
        pList->InsertColumn(2, L"Answer", LVCFMT_LEFT, 200);
        pList->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
    }
    RefreshList();

    return TRUE;
}

BOOL CAdminPage::OnSetActive()
{
    CMFCPropertyPage::OnSetActive();
    RefreshList();
    return TRUE;
}

HBRUSH CAdminPage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    // Make the property page itself transparent
    if (nCtlColor == CTLCOLOR_DLG || nCtlColor == CTLCOLOR_STATIC)
    {
        pDC->SetBkMode(TRANSPARENT);
        return m_hollowBrush;
    }

    return CMFCPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);
}

void CAdminPage::RefreshList()
{
    CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST_CUSTOM);
    if (!pList) return;
    pList->DeleteAllItems();

    // Read all lines (skip header) and store only question+answer pairs
    std::ifstream file("Custom.csv");
    if (!file.is_open()) return;

    std::string line;
    // Read header (if any) and ignore it
    if (!std::getline(file, line)) {
        file.close();
        return;
    }

    // helpers: trim and strip surrounding quotes
    auto trim = [](std::string& s) {
        while (!s.empty() && (s.front() == ' ' || s.front() == '\t' || s.front() == '\r' || s.front() == '\n')) s.erase(s.begin());
        while (!s.empty() && (s.back() == ' ' || s.back() == '\t' || s.back() == '\r' || s.back() == '\n')) s.pop_back();
        };
    auto unquote = [&](std::string& s) {
        trim(s);
        if (s.size() >= 2 && ((s.front() == '"' && s.back() == '"') || (s.front() == '\'' && s.back() == '\''))) {
            s = s.substr(1, s.size() - 2);
            trim(s);
        }
        };

    std::vector<std::pair<std::string, std::string>> rows; // (question, answer)
    while (std::getline(file, line))
    {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string id, question, answer;

        if (std::getline(ss, id, ',') && std::getline(ss, question, ',') && std::getline(ss, answer))
        {
            // Normalize fields
            trim(id);
            unquote(question);
            unquote(answer);

            // store Q/A only (we will renumber IDs)
            rows.emplace_back(question, answer);
        }
    }
    file.close();

    // Rewrite the CSV with sequential IDs starting at 1
    std::ofstream ofs("Custom.csv", std::ios::trunc);
    if (!ofs.is_open()) return;
    ofs << "Custom_ID,Custom_Q,Custom_A\n";
    for (size_t i = 0; i < rows.size(); ++i) {
        ofs << (i + 1) << "," << rows[i].first << "," << rows[i].second << "\n";
    }
    ofs.close();

    // Fill the list control with the renumbered rows
    for (int i = 0; i < (int)rows.size(); ++i)
    {
        CString idStr(std::to_string(i + 1).c_str());
        CString qStr(rows[i].first.c_str());
        CString aStr(rows[i].second.c_str());

        pList->InsertItem(i, idStr);
        pList->SetItemText(i, 1, qStr);
        pList->SetItemText(i, 2, aStr);
    }
}

void CAdminPage::OnBnClickedAdd()
{
    CString qcs, acs;
    GetDlgItemText(IDC_EDIT_QUESTION, qcs);
    GetDlgItemText(IDC_EDIT_ANSWER, acs);

    if (qcs.IsEmpty() || acs.IsEmpty()) {
        AfxMessageBox(L"Question and Answer fields cannot be empty.");
        return;
    }

    std::string q_str = std::string(CW2A(qcs, CP_UTF8));
    std::string a_str = std::string(CW2A(acs, CP_UTF8));

    FileWriter fw;
    bool success = false;

    // Check if we are adding multiple questions
    if (qcs.Find(L";;") != -1) {
        success = fw.addMultipleFromStrings("Custom.csv", q_str, a_str);
        if (!success) AfxMessageBox(L"Failed to add questions. Please check for duplicates or ensure the number of questions matches the number of answers.");
    }
    else { // Adding a single question
        success = fw.addQuestion("Custom.csv", q_str, a_str);
        if (!success) AfxMessageBox(L"Failed to add question. It may already exist.");
    }

    if (success) {
        AfxMessageBox(L"Question(s) added successfully.");
        SetDlgItemText(IDC_EDIT_QUESTION, L"");
        SetDlgItemText(IDC_EDIT_ANSWER, L"");
        RefreshList();
    }
}

void CAdminPage::OnBnClickedDeleteRow()
{
    CInputNumDlg dlg;
    if (dlg.DoModal() == IDOK) {
        int rowID = dlg.m_nRowID;
        DeleteManager dm;
        if (dm.deleteRow("Custom.csv", rowID)) {
            AfxMessageBox(L"Row deleted successfully.");
            RefreshList();
        }
        else {
            AfxMessageBox(L"Failed to delete row. Please ensure the ID is correct.");
        }
    }
}

void CAdminPage::OnBnClickedDeleteAll()
{
    if (AfxMessageBox(L"Are you sure you want to delete all custom questions?", MB_YESNO | MB_ICONWARNING) == IDYES) {
        std::ofstream ofs("Custom.csv", std::ios::trunc);
        if (ofs.is_open()) {
            ofs << "Custom_ID,Custom_Q,Custom_A" << std::endl;
            ofs.close();
            RefreshList();
        }
    }
}