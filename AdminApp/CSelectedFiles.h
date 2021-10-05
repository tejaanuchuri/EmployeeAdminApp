#pragma once


// CSelectedFiles dialog

#include <fstream>
#include <vector>
#include <stdlib.h>
#include <tchar.h>
#include <vector>
#include <string>
#include <stack>
using namespace std;
#include "../DatabaseLibrary/Employee.h"
class CSelectedFiles : public CDialogEx
{
	DECLARE_DYNAMIC(CSelectedFiles)

public:
	CSelectedFiles(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CSelectedFiles();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SELECT_FILES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl ImportRecordsList;
	vector<Employee> EmployeeRecords;

	vector<int> SelectedEmployeesIndex;
	afx_msg void OnBnClickedButtonImportFile();
};
