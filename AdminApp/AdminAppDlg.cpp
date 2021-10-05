
#include "pch.h"
#include "framework.h"
#include "AdminApp.h"
#include "AdminAppDlg.h"
#include "afxdialogex.h"
#include "odbcinst.h"
#include "afxdb.h"
#include "Insert.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "CAbout.h"

#include "ChartAxis.h"
#include "afxdialogex.h"
#include "ChartLineSerie.h"
#include "ChartPointsSerie.h"
#include "ChartSurfaceSerie.h"
#include "ChartGrid.h"
#include "ChartBarSerie.h"
#include "ChartLabel.h"

#include "ChartAxisLabel.h"
#include "ChartStandardAxis.h"
#include "ChartDateTimeAxis.h"

#include "ChartCrossHairCursor.h"
#include "ChartDragLineCursor.h"
#include "CSelectedFiles.h"
#include <set>
#include "CXml.h"
#include "../DatabaseLibrary/Database.h"
#include "GraphCtrl.h"
#include <algorithm>
#include "Insert.h"
#include "../DatabaseLibrary/Employee.h"
#include "WpfContentHostOnMfc.h"
using namespace std;

CAdminAppDlg::CAdminAppDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADMINAPP_DIALOG, pParent)
	, row(-1)
	, BarGraphYScale(0)
	, ChooseFiledName(_T(""))
	, ChooseFiledValue(_T(""))
	, LineChartBottomAxis()
	, LineChartLeftAxis()
	, Line()
{
	BarGraphYScale = 1;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAdminAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_EMP, EmployeeList);
	DDX_Control(pDX, IDC_STATIC_GRAPH_CHART, BarGraph);
	DDX_Control(pDX, IDC_CUSTOM_LINE_GRAPH, LineChartCtrl);
	DDX_Control(pDX, IDC_RADIO_BARGRAPH, BarGraphControl);
	DDX_Control(pDX, IDC_RADIO_LINE_GRAPH_REPRESENTATION, LineGraphControl);
	DDX_CBString(pDX, IDC_COMBO_CHHOSEFIELDOPTIONS, ChooseFiledName);
	DDX_Text(pDX, IDC_EDIT_CHOOSEVALUE, ChooseFiledValue);
	DDX_Control(pDX, IDC_COMBO_CHHOSEFIELDOPTIONS, CChooseType);
	DDX_Control(pDX, IDC_EDIT_CHOOSEVALUE, CChoosetypevalue);
}

BEGIN_MESSAGE_MAP(CAdminAppDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_INSERT, &CAdminAppDlg::OnBnClickedButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, &CAdminAppDlg::OnBnClickedButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CAdminAppDlg::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CAdminAppDlg::OnBnClickedButtonDelete)
	ON_COMMAND(ID_FILE_CLOSE32771, &CAdminAppDlg::OnFileClose)
	ON_COMMAND(ID_ABOUT_ADMINAPP, &CAdminAppDlg::OnAboutAdminapp)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_ALL_BARS, &CAdminAppDlg::OnBnClickedButtonDeleteAllBars)
	ON_BN_CLICKED(IDC_BUTTON_SELECTGRAPH, &CAdminAppDlg::OnBnClickedButtonSelectgraph)
	ON_BN_CLICKED(IDC_BUTTON_LOADBRAGRAPH, &CAdminAppDlg::OnBnClickedButtonLoadbragraph)
	ON_BN_CLICKED(IDC_RADIO_BARGRAPH, &CAdminAppDlg::OnBnClickedRadioBargraph)
	ON_BN_CLICKED(IDC_RADIO_LINE_GRAPH_REPRESENTATION, &CAdminAppDlg::OnBnClickedRadioLineGraphRepresentation)
	ON_COMMAND(ID_OPERATIONS_EXPORT, &CAdminAppDlg::OnOperationsExport)
	ON_COMMAND(ID_OPERATIONS_IMPORT, &CAdminAppDlg::OnOperationsImport)
	ON_COMMAND(ID_OPERATIONS_EMPLOYEERECORDS, &CAdminAppDlg::OnOperationsEmployeerecords)
END_MESSAGE_MAP()

HWND hwndWPF_WIN;
// CAdminAppDlg message handlers

BOOL CAdminAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	CMenu m_Menu;
	m_Menu.LoadMenu(IDR_MENU1);
	SetMenu(&m_Menu);
	EmployeeRecords.clear();
	SetListControl();
	Database database;
	EmployeeRecords = database.FetchAllRecords();
	DisplayRecordsOnlistControl();
	DisplayAllRecordsOnBarGraph();
	DisplayAllRecordsOnLineGraph();

	GetDlgItem(IDC_STATIC_GRAPH_CHART)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_GRAPH_CHART)->ShowWindow(SW_HIDE);
	LineGraphControl.SetState(true);
	LineGraphControl.SetCheck(1);
	SetColumnIndexs();
	hwndWPF_WIN = GetHwnd(this->GetSafeHwnd(), 821, 44, 1250, 1290);
	return TRUE;
}
void CAdminAppDlg::DisplayRecordsOnlistControl() {
	UpdateData(FALSE); // flow direction database -> ui
	DisplayAllRecords();
}


void CAdminAppDlg::DisplayAllRecordsOnBarGraph()
{
	UpdateData(FALSE);
	SetBarGraph();
	for (unsigned int employeeIndex = 0; employeeIndex < EmployeeRecords.size(); employeeIndex++)
	{
		Employee record = EmployeeRecords[employeeIndex];
		AddBarToBarGraph(record);
	}
	UpdateData(FALSE);
}
void CAdminAppDlg::DeleteAllRecordsOnBarGraph()
{
	UpdateData(FALSE);
	while (BarGraph.GetNumberOfBars() != 0) {
		BarGraph.DeleteBar(0);
	}
	UpdateWindow();
	return;
}

void CAdminAppDlg::DisplayAllRecordsOnLineGraph()
{
	DeleteAllRecordsOnLineGraph();
	SetLineGraph();
	UpdateData(FALSE);
	for (unsigned int empployeeIndex = 0; empployeeIndex < EmployeeRecords.size(); empployeeIndex++)
	{
		Employee record = EmployeeRecords[empployeeIndex];
		AddLineToLineGraph(record.Id, record.HireDate, record.YearsOfExperience);
	}
	return;
}

void CAdminAppDlg::DeleteAllRecordsOnLineGraph()
{
	LineChartCtrl.RemoveAllSeries();
	LineChartCtrl.EnableRefresh(true);
}

void CAdminAppDlg::DisplayAllRecords()
{
	UpdateData(FALSE);
	ListView_SetExtendedListViewStyle(EmployeeList, LVS_EX_FULLROWSELECT);
	RemoveAllRecords();
	for (unsigned int empIndex = 0; empIndex < EmployeeRecords.size(); empIndex++) {
		Employee record = EmployeeRecords[empIndex];
		InsertRecordIntoListControl(record);
	}
	EmployeeList.UpdateWindow();
	UpdateWindow();
	UpdateData(FALSE);
}

void CAdminAppDlg::RemoveAllRecords()
{
	while (EmployeeList.GetItemCount() != 0) {
		EmployeeList.DeleteItem(0);
	}
}

void CAdminAppDlg::BarGraphUpdate(int barid, int yearsofexperience)
{
	BarGraph.SetBarValue(barid, yearsofexperience, TRUE);
	BarGraph.DrawGraph();

}

void CAdminAppDlg::EmployeeResetListControl() {
	EmployeeList.DeleteAllItems();
	int iNbrOfColumns = 0, columnIndex;
	CHeaderCtrl* pHeader = (CHeaderCtrl*)EmployeeList.GetDlgItem(0);
	if (pHeader) {
		iNbrOfColumns = pHeader->GetItemCount();
	}
	for (columnIndex = iNbrOfColumns; columnIndex >= 0; columnIndex--) {
		EmployeeList.DeleteColumn(columnIndex);
	}
}

void CAdminAppDlg::OnBnClickedButtonInsert()
{
	Insert dlg;
	Employee record;
	//SubmitBtnCtrl.SetWindowTextW(L"Insert");
	if (dlg.DoModal() == IDOK) {
		UpdateData(FALSE); // flow direction database -> ui
		record.Id = dlg.Id;
		record.HireDate = dlg.HireDate.Format(_T("%d-%m-%Y"));
		record.YearsOfExperience = dlg.YearsOfExperience;
		record.Age = dlg.Age;
		record.Title = dlg.Title;
		record.FirstName = dlg.FirstName;
		record.LastName = dlg.LastName;
		record.Gender = dlg.Gender;
		record.MobileNumber = dlg.PhoneNumber;
		record.Email = dlg.Email;
		record.DateOfBirth = dlg.DateOfBirth.Format(_T("%d-%m-%Y"));
		record.Address = dlg.Address;
		record.JobTitle = dlg.JobTitle;
		record.Salary = dlg.Salary;

		EmployeeRecords.push_back(record);
		InsertRecordIntoListControl(record);
		EmployeeList.UpdateWindow();
		AddBarToBarGraph(record);
		AddLineToLineGraph(record.Id, record.HireDate, record.YearsOfExperience);
		UpdateWindow();
	}
}


void CAdminAppDlg::OnBnClickedButtonUpdate()
{
	UpdateData(TRUE); // flow direction database <- updateDlg.

	row = EmployeeList.GetSelectionMark();
	if (row < 0) {
		AfxMessageBox(L"No row Selected");
	}
	else {

		Insert updateDlg;
		updateDlg.Id = EmployeeList.GetItemText(row, 0);
		updateDlg.YearsOfExperience = EmployeeList.GetItemText(row, 2);
		updateDlg.Title = EmployeeList.GetItemText(row, 3);
		updateDlg.Age = EmployeeList.GetItemText(row, 4);
		updateDlg.FirstName = EmployeeList.GetItemText(row, 5);
		updateDlg.LastName = EmployeeList.GetItemText(row, 6);
		updateDlg.Gender = EmployeeList.GetItemText(row, 7);
		updateDlg.PhoneNumber = EmployeeList.GetItemText(row, 8);
		updateDlg.Email = EmployeeList.GetItemText(row, 9);
		updateDlg.Address = EmployeeList.GetItemText(row, 11);
		updateDlg.JobTitle = EmployeeList.GetItemText(row, 12);
		updateDlg.Salary = EmployeeList.GetItemText(row, 13);
		COleDateTime emp_datebirth;
		emp_datebirth.ParseDateTime(EmployeeList.GetItemText(row, 10));
		COleDateTime employee_hiredate;
		employee_hiredate.ParseDateTime(EmployeeList.GetItemText(row, 1));
		updateDlg.DateOfBirth = emp_datebirth;
		updateDlg.HireDate = employee_hiredate;


		if (updateDlg.DoModal() == IDOK) {
			Employee record;
			record.Id = updateDlg.Id;
			record.HireDate = updateDlg.HireDate.Format(_T("%d-%m-%Y"));
			record.YearsOfExperience = updateDlg.GetYearsOfExperience(updateDlg.HireDate);

			record.Title = updateDlg.Title;
			record.Age = updateDlg.GetAge(updateDlg.DateOfBirth);
			record.FirstName = updateDlg.FirstName;
			record.LastName = updateDlg.LastName;
			record.Gender = updateDlg.Gender;
			record.MobileNumber = updateDlg.PhoneNumber;
			record.Email = updateDlg.Email;
			record.DateOfBirth = updateDlg.DateOfBirth.Format(_T("%d-%m-%Y"));
			record.Address = updateDlg.Address;
			record.JobTitle = updateDlg.JobTitle;
			record.Salary = updateDlg.Salary;

			ListView_SetExtendedListViewStyle(EmployeeList, LVS_EX_FULLROWSELECT);
			//Update record on listcontrol
			InsertRecordAtCertainRow(record, row);

			//update record on employee records
			vector<Employee>::iterator updateRecord = (EmployeeRecords.begin() + row);
			(*updateRecord) = record;

			BarGraphUpdate(row, _wtoi(record.YearsOfExperience));

			AddLineToLineGraph(record.Id, record.HireDate, record.YearsOfExperience);
			LineChartCtrl.EnableRefresh(true);
			MessageBox(L"Update record Sucessfully...!");
		}
		UpdateWindow();
	}

}


void CAdminAppDlg::OnBnClickedButtonSearch()
{
	UpdateData(TRUE);

	CString chooseField = ChooseFiledName;
	DisplayAllRecords();
	if (ChooseFiledValue.IsEmpty()) {
		CChooseType.SetWindowText(_T(""));
		CChoosetypevalue.SetWindowText(_T(""));
	}
	else {
		UpdateData(FALSE);
		vector<int> recordIndexs;
		for (unsigned int empIndex = 0; empIndex < EmployeeRecords.size(); empIndex++) {
			CString temp = EmployeeList.GetItemText(empIndex, ColumnIndex[chooseField]);
			if (ColumnIndex[chooseField] == 0 || ColumnIndex[chooseField] == 1 || ColumnIndex[chooseField] == 2 || ColumnIndex[chooseField] == 4 || ColumnIndex[chooseField] == 10 || ColumnIndex[chooseField] == 13 || ColumnIndex[chooseField] == 8) {
				if (CompareTwoStrings(temp, ChooseFiledValue)) {
					recordIndexs.push_back(empIndex);
				}
			}
			else {
				if (temp.Find(ChooseFiledValue) != -1) {
					recordIndexs.push_back(empIndex);
				}
			}
		}
		RemoveAllRecords();
		DisplaySearchedRecords(recordIndexs);
	}
	UpdateWindow();

}

void CAdminAppDlg::SelectRecordsResetListControl()
{
	CSelectedFiles dlg;
	dlg.ImportRecordsList.DeleteAllItems();
	int iNbrOfColumns = 0, columnIndex;
	CHeaderCtrl* pHeader = (CHeaderCtrl*)dlg.ImportRecordsList.GetDlgItem(0);
	if (pHeader) {
		iNbrOfColumns = pHeader->GetItemCount();
	}
	for (columnIndex = iNbrOfColumns; columnIndex >= 0; columnIndex--) {
		dlg.ImportRecordsList.DeleteColumn(columnIndex);
	}
}

void CAdminAppDlg::OnBnClickedButtonDelete()
{
	UpdateData(TRUE);

	row = EmployeeList.GetSelectionMark();
	if (row < 0) {
		AfxMessageBox(L"No row Selected");
	}
	else {
		vector<Employee>::iterator it = EmployeeRecords.begin() + row;
		EmployeeRecords.erase(it);
		CString id = EmployeeList.GetItemText(row, 0);
		EmployeeList.DeleteItem(row);
		DeleteBarFromBarGraph(row);
		UpdateWindow();
		DeleteRecordFromDatabase(id);
		DeleteLineFromLineGraph(_wtoi(id));
		MessageBox(L"Delete Record Sucessfully...!");
		UpdateWindow();
	}

}

void CAdminAppDlg::OnFileClose()
{
	if (AfxMessageBox(_T("Are you sure you want to close ?"),
		MB_YESNO) == IDNO)
	{
		return;
	}


	CDialog::OnCancel();
}


void CAdminAppDlg::OnAboutAdminapp()
{
	CAbout about;
	if (about.DoModal() == IDOK) {

	}
}
void CAdminAppDlg::OnBnClickedButtonDeleteAllBars()
{
	DeleteAllRecordsOnBarGraph();
	BarGraph.DrawGraph();
	DeleteAllRecordsOnLineGraph();
	UpdateData(FALSE);
	UpdateWindow();
}
void CAdminAppDlg::OnBnClickedButtonSelectgraph()
{
	POSITION pos = EmployeeList.GetFirstSelectedItemPosition();
	if (pos == NULL) {
		AfxMessageBox(L"No row Selected");
	}
	else {
		DeleteAllRecordsOnBarGraph();
		DeleteAllRecordsOnLineGraph();
		BarGraph.DrawGraph();
		SetLineGraph();
		POSITION pos = EmployeeList.GetFirstSelectedItemPosition();
		if (pos != NULL) {
			while (pos)
			{
				int row = EmployeeList.GetNextSelectedItem(pos);
				Employee record;
				record.Id = EmployeeList.GetItemText(row, 0);
				record.YearsOfExperience = EmployeeList.GetItemText(row, 2);
				record.HireDate = EmployeeList.GetItemText(row, 1);

				AddBarToBarGraph(record);
				AddLineToLineGraph(record.Id, record.HireDate, record.YearsOfExperience);
			}
		}
		BarGraph.SetBGColor(RGB(255, 229, 204));
		BarGraph.SetAxisColor(RGB(102, 0, 0));
		BarGraph.SetTextColor(RGB(102, 102, 255));
		UpdateData(FALSE);
	}
}


void CAdminAppDlg::OnBnClickedButtonLoadbragraph()
{
	DeleteAllRecordsOnBarGraph();
	DisplayAllRecordsOnBarGraph();
	BarGraph.DrawGraph();
	DeleteAllRecordsOnLineGraph();
	DisplayAllRecordsOnLineGraph();
	UpdateWindow();
	return;
}


void CAdminAppDlg::OnBnClickedRadioBargraph()
{
	UpdateData(FALSE);
	GetDlgItem(IDC_STATIC_GRAPH_CHART)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CUSTOM_LINE_GRAPH)->ShowWindow(SW_HIDE);
	UpdateWindow();
}


void CAdminAppDlg::OnBnClickedRadioLineGraphRepresentation()
{
	UpdateData(FALSE);
	GetDlgItem(IDC_STATIC_GRAPH_CHART)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CUSTOM_LINE_GRAPH)->ShowWindow(SW_SHOW);
	UpdateWindow();

}


void CAdminAppDlg::OnOperationsExport()
{

	POSITION pos = EmployeeList.GetFirstSelectedItemPosition();
	if (pos == NULL) {
		AfxMessageBox(L"No row Selected");
	}
	else {
		vector<Employee> employeeRecords;
		POSITION pos = EmployeeList.GetFirstSelectedItemPosition();

		if (pos != NULL) {
			while (pos)
			{
				int row = EmployeeList.GetNextSelectedItem(pos);
				employeeRecords.push_back(GetRecord(row));
			}
		}
		CXml xml;
		xml.Export(employeeRecords);
		MessageBox(L"Xml Files Generate Sucessfully...!");
	}

	return;
}


void CAdminAppDlg::OnOperationsImport()
{
	CString sFilter = _T("Xml Files (*.xml)|*.xml");

	CFileDialog dlg(TRUE, _T("*.xml"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT, sFilter, this);

	vector<Employee> employeeRecords;
	if (dlg.DoModal() == IDOK)
	{
		POSITION pos(dlg.GetStartPosition());
		while (pos)
		{
			CString filePath = dlg.GetNextPathName(pos);
			CXml xml;
			employeeRecords = xml.Import(filePath);

			CSelectedFiles dlg;
			dlg.EmployeeRecords = employeeRecords;
			if (dlg.DoModal() == IDOK) {
				UpdateData(FALSE);
				if (AddSelectedRecords(dlg.SelectedEmployeesIndex, dlg.EmployeeRecords))
				{
					MessageBox(L"Successfully Insert Xml File...!");
				}
				else {
					MessageBox(L"Same Records Already exists In Xml File...!");
				}
			}
			UpdateWindow();
		}
	}
}

bool CAdminAppDlg::CompareTwoStrings(CString p, CString q)
{
	if (p.GetLength() != q.GetLength())
		return false;
	for (int index = 0; index < p.GetLength(); index++) {
		if (p[index] != q[index]) {
			return false;
		}
	}
	return true;
}

Employee CAdminAppDlg::GetRecord(int row)
{
	Employee record;
	record.Id = EmployeeList.GetItemText(row, 0);
	record.HireDate = EmployeeList.GetItemText(row, 1);
	record.YearsOfExperience = EmployeeList.GetItemText(row, 2);
	record.Title = EmployeeList.GetItemText(row, 3);
	record.Age = EmployeeList.GetItemText(row, 4);
	record.FirstName = EmployeeList.GetItemText(row, 5);
	record.LastName = EmployeeList.GetItemText(row, 6);
	record.Gender = EmployeeList.GetItemText(row, 7);
	record.MobileNumber = EmployeeList.GetItemText(row, 8);
	record.Email = EmployeeList.GetItemText(row, 9);
	record.DateOfBirth = EmployeeList.GetItemText(row, 10);
	record.Address = EmployeeList.GetItemText(row, 11);
	record.JobTitle = EmployeeList.GetItemText(row, 12);
	record.Salary = EmployeeList.GetItemText(row, 13);
	return record;
}

COleDateTime CAdminAppDlg::StringToDate(CString string)
{
	COleDateTime date;
	date.ParseDateTime(string);
	return date;
}

void CAdminAppDlg::DisplaySearchedRecords(vector<int> recordindexs)
{
	UpdateData(FALSE);
	for (unsigned int index = 0; index < recordindexs.size(); index++) {
		Employee record = EmployeeRecords[recordindexs[index]];
		InsertRecordIntoListControl(record);
	}
	EmployeeList.UpdateWindow();
	UpdateWindow();
}

void CAdminAppDlg::SetColumnIndexs()
{

	ColumnIndex.insert(make_pair(L"EmpID", 0));
	ColumnIndex.insert(make_pair(L"Hiredate", 1));
	ColumnIndex.insert(make_pair(L"YearsOfExp", 2));
	ColumnIndex.insert(make_pair(L"Title", 3));
	ColumnIndex.insert(make_pair(L"Age", 4));
	ColumnIndex.insert(make_pair(L"FirstName", 5));
	ColumnIndex.insert(make_pair(L"LastName", 6));
	ColumnIndex.insert(make_pair(L"Gender", 7));
	ColumnIndex.insert(make_pair(L"MobilePhone", 8));
	ColumnIndex.insert(make_pair(L"EMail", 9));
	ColumnIndex.insert(make_pair(L"BirthDate", 10));
	ColumnIndex.insert(make_pair(L"Address", 11));
	ColumnIndex.insert(make_pair(L"JobTitle", 12));
	ColumnIndex.insert(make_pair(L"Salary", 13));
}

int CAdminAppDlg::GetColumnIndex(CString columnname)
{
	return ColumnIndex[columnname];
}


Employee CAdminAppDlg::GetRecordFromEmployeeRecords(CString id)
{
	Employee record;
	for (unsigned int empIndex = 0; empIndex < EmployeeRecords.size(); empIndex++) {
		record = EmployeeRecords[empIndex];
		if (record.Id == id) {
			return record;
		}
	}
	return Employee();
}

bool CAdminAppDlg::HasSameEmployeeRecord(Employee record, Employee selectedrecord)
{
	if (record.Id != selectedrecord.Id || record.Title != selectedrecord.Title || record.FirstName != selectedrecord.FirstName || record.LastName != selectedrecord.LastName || record.Age != selectedrecord.Age || record.DateOfBirth != selectedrecord.DateOfBirth || record.Address != selectedrecord.Address || record.Email != selectedrecord.Email || record.Gender != selectedrecord.Gender || record.HireDate != selectedrecord.HireDate || record.JobTitle != selectedrecord.JobTitle || record.MobileNumber != selectedrecord.MobileNumber || record.Salary != selectedrecord.Salary || record.YearsOfExperience != selectedrecord.YearsOfExperience)
		return false;
	return true;
}

Employee CAdminAppDlg::ValidateAndSetEmployeeId(Employee selectedrecord)
{
	Database database;
	Employee record = GetRecordFromEmployeeRecords(selectedrecord.Id);
	if (!HasSameEmployeeRecord(selectedrecord, record)) {
		if (selectedrecord.Id == record.Id) {
			selectedrecord.Id.Empty();
			selectedrecord.Id = database.GetNextAutoNumber();
		}
	}
	else {
		selectedrecord.Id.Empty();
	}
	return selectedrecord;
}


void CAdminAppDlg::AddLineToLineGraph(CString id, CString hiredate, CString yearsofexperience)
{
	int hireYear = StringToDate(hiredate).GetYear();
	int yearsOfExp = _wtoi(yearsofexperience);
	int empId = _wtoi(id);
	CreateLine(empId, hireYear, yearsOfExp);
}

void CAdminAppDlg::SetBarGraph()
{
	UpdateData(FALSE);
	BarGraph.SetUnit(L"Experience");
	BarGraph.SetScale(10);
	int x = 1, y = 100;
	BarGraph.GetDisplayRange(x, y);
	BarGraphYScale = 1;
	BarGraph.SetBGColor(RGB(255, 229, 204));
	BarGraph.SetAxisColor(RGB(102, 0, 0));
	BarGraph.SetTextColor(RGB(102, 102, 255));
}

void CAdminAppDlg::AddBarToBarGraph(Employee record)
{
	char recordId[20];
	sprintf_s(recordId, "%d", _wtoi(record.Id));
	BarGraph.AddBar(_wtoi(record.YearsOfExperience), RANDOMCOLOUR, recordId);
	BarGraph.DrawGraph();
	UpdateWindow();
}

void CAdminAppDlg::DeleteBarFromBarGraph(int row)
{
	BarGraph.DeleteBar(row);
	BarGraph.DrawGraph();

}

void CAdminAppDlg::SetLineGraph()
{
	LineChartBottomAxis = LineChartCtrl.CreateStandardAxis(CChartCtrl::BottomAxis);
	LineChartLeftAxis = LineChartCtrl.CreateStandardAxis(CChartCtrl::LeftAxis);


	LineChartBottomAxis->SetMinMax(2000, 2015);

	LineChartLeftAxis->SetMinMax(1, 20);
	LineChartLeftAxis->GetLabel()->SetText(L"Employee Id");

	LineChartBottomAxis->GetLabel()->SetText(L"Year of Employee hired");
	LineChartBottomAxis->SetTickIncrement(false, 1);
	LineChartLeftAxis->SetTickIncrement(false, 1);
	LineChartBottomAxis->SetDiscrete(false);
	LineChartLeftAxis->SetDiscrete(false);
	LineChartBottomAxis->EnableScrollBar(true);
	LineChartLeftAxis->EnableScrollBar(true);
	return;
}

void CAdminAppDlg::InsertRecordIntoListControl(Employee record)
{
	int row = EmployeeList.GetItemCount();
	int iRecord = EmployeeList.InsertItem(row, record.Id, 0);
	EmployeeList.SetItemText(row, 1, record.HireDate);
	EmployeeList.SetItemText(row, 2, record.YearsOfExperience);
	EmployeeList.SetItemText(row, 3, record.Title);
	EmployeeList.SetItemText(row, 4, record.Age);
	EmployeeList.SetItemText(row, 5, record.FirstName);
	EmployeeList.SetItemText(row, 6, record.LastName);
	EmployeeList.SetItemText(row, 7, record.Gender);
	EmployeeList.SetItemText(row, 8, record.MobileNumber);
	EmployeeList.SetItemText(row, 9, record.Email);
	EmployeeList.SetItemText(row, 10, record.DateOfBirth);
	EmployeeList.SetItemText(row, 11, record.Address);
	EmployeeList.SetItemText(row, 12, record.JobTitle);
	EmployeeList.SetItemText(row, 13, record.Salary);
	EmployeeList.UpdateWindow();
}

void CAdminAppDlg::InsertRecordAtCertainRow(Employee record, int row)
{
	EmployeeList.SetItemText(row, 0, record.Id);
	EmployeeList.SetItemText(row, 1, record.HireDate);
	EmployeeList.SetItemText(row, 2, record.YearsOfExperience);
	EmployeeList.SetItemText(row, 3, record.Title);
	EmployeeList.SetItemText(row, 4, record.Age);
	EmployeeList.SetItemText(row, 5, record.FirstName);
	EmployeeList.SetItemText(row, 6, record.LastName);
	EmployeeList.SetItemText(row, 7, record.Gender);
	EmployeeList.SetItemText(row, 8, record.MobileNumber);
	EmployeeList.SetItemText(row, 9, record.Email);
	EmployeeList.SetItemText(row, 10, record.DateOfBirth);
	EmployeeList.SetItemText(row, 11, record.Address);
	EmployeeList.SetItemText(row, 12, record.JobTitle);
	EmployeeList.SetItemText(row, 13, record.Salary);
	EmployeeList.UpdateWindow();
}

void CAdminAppDlg::DeleteRecordFromDatabase(CString id)
{
	Database database;
	database.DeleteRecord(id);
}

void CAdminAppDlg::SetListControl()
{
	EmployeeResetListControl();

	ListView_SetExtendedListViewStyle(EmployeeList, LVS_EX_FULLROWSELECT);

	EmployeeList.InsertColumn(0, L"EmpID", LVCFMT_LEFT, 70);
	EmployeeList.InsertColumn(1, L"HireDate", LVCFMT_LEFT, 100);
	EmployeeList.InsertColumn(2, L"YearsOfExp", LVCFMT_LEFT, 100);
	EmployeeList.InsertColumn(3, L"Title", LVCFMT_CENTER, 90);
	EmployeeList.InsertColumn(4, L"Age", LVCFMT_LEFT, 70);
	EmployeeList.InsertColumn(5, L"FirstName", LVCFMT_CENTER, 130);
	EmployeeList.InsertColumn(6, L"LastName", LVCFMT_LEFT, 130);
	EmployeeList.InsertColumn(7, L"Gender", LVCFMT_CENTER, 120);
	EmployeeList.InsertColumn(8, L"MobilePhone", LVCFMT_LEFT, 160);
	EmployeeList.InsertColumn(9, L"EMail", LVCFMT_CENTER, 230);
	EmployeeList.InsertColumn(10, L"BirthDate", LVCFMT_LEFT, 100);
	EmployeeList.InsertColumn(11, L"Address", LVCFMT_CENTER, 180);
	EmployeeList.InsertColumn(12, L"JobTitle", LVCFMT_LEFT, 100);
	EmployeeList.InsertColumn(13, L"Salary", LVCFMT_CENTER, 100);
}

bool CAdminAppDlg::AddSelectedRecords(vector<int> selectedrecordindexs, vector<Employee> importedrecords)
{
	Database database;
	Employee selectedRecord;
	int selectedRecordsCount = 0;
	for (unsigned int recordIndex = 0; recordIndex < selectedrecordindexs.size(); recordIndex++) {
		selectedRecord = importedrecords[selectedrecordindexs[recordIndex]];
		selectedRecord = ValidateAndSetEmployeeId(selectedRecord);
		if (selectedRecord.Id.IsEmpty())
			continue;
		database.InsertRecord(selectedRecord);
		EmployeeRecords.push_back(selectedRecord);
		InsertRecordIntoListControl(selectedRecord);
		AddBarToBarGraph(selectedRecord);
		AddLineToLineGraph(selectedRecord.Id, selectedRecord.HireDate, selectedRecord.YearsOfExperience);
		selectedRecordsCount++;
	}
	if (selectedRecordsCount == 0) {
		return false;
	}
	return true;
}

void CAdminAppDlg::CreateLine(int id, int hireyear, int yearsofexperience)
{
	Line = LineChartCtrl.CreateLineSerie();
	Line->SetWidth(5); //line width
	Line->SetColor(RANDOMCOLOUR); //color of line

	double XVal[2] = { 0 };
	double YVal[2] = { 0 };
	unsigned int index = 0;
	XVal[index] = hireyear;
	YVal[index] = id;
	index++;
	YVal[index] = id;
	XVal[index] = XVal[index - 1] + yearsofexperience;
	index++;
	Line->SetPoints(XVal, YVal, index);
	if (LineId.find(id) != LineId.end()) {
		map<unsigned int, unsigned int>::iterator it = LineId.find(id);
		LineChartCtrl.RemoveSerie(it->second);
		LineId.erase(it);
	}
	LineId[id] = Line->GetSerieId();
	LineChartCtrl.EnableRefresh(true);
}

void CAdminAppDlg::UpdateLineGraph(int row, int id, int hireyear, int yearsofexperience)
{
	if (LineId.find(id) != LineId.end()) {
		unsigned int seriesIndex = LineId[id];
		LineChartCtrl.RemoveSerie(seriesIndex);
		LineChartCtrl.EnableRefresh(true);
	}
	CreateLine(id, hireyear, yearsofexperience);
}

void CAdminAppDlg::DeleteLineFromLineGraph(int id)
{
	map<unsigned int, unsigned int>::iterator lineId = LineId.find(id);
	if (lineId != LineId.end()) {
		LineChartCtrl.RemoveSerie(lineId->second);
		LineChartCtrl.EnableRefresh(true);
		LineId.erase(lineId);
	}
	return;
}


void CAdminAppDlg::OnOperationsEmployeerecords()
{
	UpdateData(FALSE);
	WpfContentHostOnMfc dlg;
	if (dlg.DoModal() == IDOK) {

	}
}
