// CSelectedFiles.cpp : implementation file
//

#include "pch.h"
#include "AdminApp.h"
#include "CSelectedFiles.h"
#include "afxdialogex.h"
#include "AdminAppDlg.h"


// CSelectedFiles dialog

IMPLEMENT_DYNAMIC(CSelectedFiles, CDialogEx)

CSelectedFiles::CSelectedFiles(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SELECT_FILES, pParent)
{

}

CSelectedFiles::~CSelectedFiles()
{
}

void CSelectedFiles::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SELECT_FILES, ImportRecordsList);
}


BEGIN_MESSAGE_MAP(CSelectedFiles, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_FILE, &CSelectedFiles::OnBnClickedButtonImportFile)
END_MESSAGE_MAP()


BOOL CSelectedFiles::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	UpdateData(FALSE); // flow direction database -> ui

	int iRecord = 0, columnIndex = 0;
	ListView_SetExtendedListViewStyle(ImportRecordsList, LVS_EX_FULLROWSELECT);

	ImportRecordsList.InsertColumn(columnIndex++, L"FirstName", LVCFMT_CENTER, 260);
	ImportRecordsList.InsertColumn(columnIndex++, L"LastName", LVCFMT_CENTER, 260);

	for (unsigned int empIndex = 0; empIndex < EmployeeRecords.size(); empIndex++) {
		Employee record = EmployeeRecords[empIndex];
		int row = ImportRecordsList.GetItemCount();
		iRecord = ImportRecordsList.InsertItem(row, record.FirstName, 0);
		ImportRecordsList.SetItemText(row, 1, record.LastName);
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSelectedFiles::OnBnClickedButtonImportFile()
{
	POSITION pos = ImportRecordsList.GetFirstSelectedItemPosition();
	if (pos == NULL) {
		AfxMessageBox(L"No row Selected");
	}
	else {

		POSITION pos = ImportRecordsList.GetFirstSelectedItemPosition();
		SelectedEmployeesIndex.clear();
		if (pos != NULL) {
			while (pos)
			{
				int row = ImportRecordsList.GetNextSelectedItem(pos);
				SelectedEmployeesIndex.push_back(row);
			}
		}
		UpdateData(FALSE);
	}
	CSelectedFiles::OnOK();
}
