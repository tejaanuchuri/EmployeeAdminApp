
#pragma once

#include "ChartCtrl.h"
#include "ChartLineSerie.h"
#include "ChartLabel.h"
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <tchar.h>
#include <vector>
#include <string>
#include <stack>
#include "GraphCtrl.h"
#include "../DatabaseLibrary/Employee.h"
using namespace std;


#define RANDOMCOLOUR RGB(rand() % 256, rand() % 256, rand() % 256)

// CAdminAppDlg dialog
class CAdminAppDlg : public CDialogEx
{
	// Construction
public:
	CAdminAppDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
	CGraphCtrl BarGraph;
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADMINAPP_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
public:
	//Bar Graph
	void DisplayAllRecordsOnBarGraph();
	void DeleteAllRecordsOnBarGraph();
	void BarGraphUpdate(int barid, int yearsofexperience);
	void SetBarGraph();
	void AddBarToBarGraph(Employee record);
	void DeleteBarFromBarGraph(int row);

	//Line Graph
	void DisplayAllRecordsOnLineGraph();
	void DeleteAllRecordsOnLineGraph();
	void AddLineToLineGraph(CString id, CString hiredate, CString yearsofexperience);
	void SetLineGraph();
	void CreateLine(int id, int hireyear, int yearsofexperience);
	void UpdateLineGraph(int row, int id, int hireyear, int yearsofexperience);
	void DeleteLineFromLineGraph(int id);

	//ListControl
	void DisplayRecordsOnlistControl();
	void DisplayAllRecords();
	void EmployeeResetListControl();
	void RemoveAllRecords();
	void InsertRecordIntoListControl(Employee record);
	void InsertRecordAtCertainRow(Employee record, int row);
	void SetListControl();
	void DeleteRecordFromDatabase(CString id);

	// Import selected records
	bool AddSelectedRecords(vector<int> selectedrecordindexs, vector<Employee> importedrecords);
	void SelectRecordsResetListControl();
	Employee GetRecordFromEmployeeRecords(CString id);
	bool HasSameEmployeeRecord(Employee record, Employee selectedrecord);
	Employee ValidateAndSetEmployeeId(Employee selectedrecord);

	//Export Selected Records
	Employee GetRecord(int row);
	COleDateTime StringToDate(CString string);

	//Search Records
	void DisplaySearchedRecords(vector<int> recordindexs);
	void SetColumnIndexs();
	int GetColumnIndex(CString columnname);
	bool CompareTwoStrings(CString p, CString q);

	// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl EmployeeList;
	int row;
	int BarGraphYScale;
	map<CString, int> ColumnIndex;
	Employee SelectedRecord;
	map<unsigned int, unsigned int> LineId;
	afx_msg void OnBnClickedButtonInsert();
	afx_msg void OnBnClickedButtonUpdate();
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnFileClose();
	afx_msg void OnAboutAdminapp();

	afx_msg void OnBnClickedButtonDeleteAllBars();
	afx_msg void OnBnClickedButtonSelectgraph();
	afx_msg void OnBnClickedButtonLoadbragraph();
	CChartCtrl LineChartCtrl;
	CChartStandardAxis* LineChartBottomAxis;
	CChartStandardAxis* LineChartLeftAxis;
	CChartLineSerie* Line;


	afx_msg void OnBnClickedRadioBargraph();
	afx_msg void OnBnClickedRadioLineGraphRepresentation();
	CButton BarGraphControl;
	CButton LineGraphControl;
	CString ChooseFiledName;
	CString ChooseFiledValue;
	CComboBox CChooseType;
	CEdit CChoosetypevalue;
	//vector< vector<pair<CString, CString>>> employee_records;
	vector<Employee> EmployeeRecords;
	afx_msg void OnOperationsExport();
	afx_msg void OnOperationsImport();
	afx_msg void OnOperationsEmployeerecords();
};