#include "pch.h"
#include "Database.h"
#include "odbcinst.h"
#include "afxdb.h"
#include "Employee.h"
#include<vector>
#include<string>
#include <atlstr.h>
#include<iostream>
#include<sstream>
#include<stdlib.h>
using namespace std;
Database::Database()
{
}

void Database::InsertRecord(Employee record)
{
	CDatabase database;
	CString connectionString;
	CString sqlString;

	connectionString.Format(_T("Driver={Microsoft Access Driver (*.mdb, *.accdb)};Dbq=C:\\Users\\admin.teja\\Documents\\EmployeeDatabase.accdb;Uid=Admin;Pwd=;"));
	TRY{
		// Open the database
		database.Open(NULL,false,false,connectionString);
		CString out = L" ,";
		CString quo = L"'";
		sqlString.Append(_T("INSERT INTO EmployeeTable(EmpID,Hiredate,YearsOfExp,Title,Age,FirstName,LastName,Gender,MobilePhone,EMail,Address,JobTitle,Salary,BirthDate,CreatedRecord) VALUES ("));

		sqlString.Append(quo);
		sqlString.Append(record.Id);
		sqlString.Append(quo);
		sqlString.Append(out);

		sqlString.Append(quo);
		sqlString.Append(record.HireDate);
		sqlString.Append(quo);
		sqlString.Append(out);

		sqlString.Append(quo);
		sqlString.Append(record.YearsOfExperience);
		sqlString.Append(quo);
		sqlString.Append(out);

		sqlString.Append(quo);
		sqlString.Append(record.Title);
		sqlString.Append(quo);
		sqlString.Append(out);

		sqlString.Append(quo);
		sqlString.Append(record.Age);
		sqlString.Append(quo);
		sqlString.Append(out);

		sqlString.Append(quo);
		sqlString.Append(record.FirstName);
		sqlString.Append(quo);
		sqlString.Append(out);

		sqlString.Append(quo);
		sqlString.Append(record.LastName);
		sqlString.Append(quo);
		sqlString.Append(out);

		sqlString.Append(quo);
		sqlString.Append(record.Gender);
		sqlString.Append(quo);
		sqlString.Append(out);

		sqlString.Append(quo);
		sqlString.Append(record.MobileNumber);
		sqlString.Append(quo);
		sqlString.Append(out);

		sqlString.Append(quo);
		sqlString.Append(record.Email);
		sqlString.Append(quo);
		sqlString.Append(out);


		sqlString.Append(quo);
		sqlString.Append(record.Address);
		sqlString.Append(quo);
		sqlString.Append(out);

		sqlString.Append(quo);
		sqlString.Append(record.JobTitle);
		sqlString.Append(quo);
		sqlString.Append(out);

		sqlString.Append(quo);
		sqlString.Append(record.Salary);
		sqlString.Append(quo);
		sqlString.Append(out);

		sqlString.Append(quo);
		sqlString.Append(record.DateOfBirth);
		sqlString.Append(quo);
		sqlString.Append(out);

		COleDateTime Dt(COleDateTime::GetCurrentTime());
		sqlString.Append(quo);
		sqlString.Append(Dt.Format(_T("%d-%m-%Y::%H:%M:%S")));
		sqlString.Append(quo);

		sqlString.Append(_T(" )"));

		database.ExecuteSQL(sqlString);
		database.Close();
	}CATCH(CDBException, e) {
		AfxMessageBox(L"Database error: " + e->m_strError);
	}
	END_CATCH;
}

void Database::UpdateRecord(Employee record)
{
	CDatabase database;
	CString connectionString;
	CString sqlString;
	CString out = L" ,";
	CString quo = L"'";

	connectionString.Format(_T("Driver={Microsoft Access Driver (*.mdb, *.accdb)};Dbq=C:\\Users\\admin.teja\\Documents\\EmployeeDatabase.accdb;Uid=Admin;Pwd=;"));
	TRY{
		// Open the database
		database.Open(NULL,false,false,connectionString);
		sqlString.Append(_T("UPDATE EmployeeTable SET "));

		sqlString.Append(L"Title = ");
		sqlString.Append(quo);
		sqlString.Append(record.Title);
		sqlString.Append(quo);
		sqlString.Append(out);

		sqlString.Append(L"Age = ");
		sqlString.Append(quo);
		sqlString.Append(record.Age);
		sqlString.Append(quo);
		sqlString.Append(out);

		sqlString.Append(L"FirstName = ");
		sqlString.Append(quo);
		sqlString.Append(record.FirstName);
		sqlString.Append(quo);
		sqlString.Append(out);

		sqlString.Append(L"LastName = ");
		sqlString.Append(quo);
		sqlString.Append(record.LastName);
		sqlString.Append(quo);
		sqlString.Append(out);


		sqlString.Append(L"Gender = ");
		sqlString.Append(quo);
		sqlString.Append(record.Gender);
		sqlString.Append(quo);
		sqlString.Append(out);


		sqlString.Append(L"MobilePhone = ");
		sqlString.Append(quo);
		sqlString.Append(record.MobileNumber);
		sqlString.Append(quo);
		sqlString.Append(out);

		sqlString.Append(L"EMail = ");
		sqlString.Append(quo);
		sqlString.Append(record.Email);
		sqlString.Append(quo);
		sqlString.Append(out);


		sqlString.Append(L"BirthDate = ");
		sqlString.Append(quo);
		sqlString.Append(record.DateOfBirth);
		sqlString.Append(quo);
		sqlString.Append(out);

		sqlString.Append(L"Address = ");
		sqlString.Append(quo);
		sqlString.Append(record.Address);
		sqlString.Append(quo);
		sqlString.Append(out);

		sqlString.Append(L"JobTitle = ");
		sqlString.Append(quo);
		sqlString.Append(record.JobTitle);
		sqlString.Append(quo);
		sqlString.Append(out);

		sqlString.Append(L"Salary = ");
		sqlString.Append(quo);
		sqlString.Append(record.Salary);
		sqlString.Append(quo);
		sqlString.Append(out);


		sqlString.Append(L"Hiredate = ");
		sqlString.Append(quo);
		sqlString.Append(record.HireDate);
		sqlString.Append(quo);
		sqlString.Append(out);

		sqlString.Append(L"YearsOfExp = ");
		sqlString.Append(quo);
		sqlString.Append(record.YearsOfExperience);
		sqlString.Append(quo);

		sqlString.Append(_T(" WHERE EmpID = " + record.Id));

		database.ExecuteSQL(sqlString);
		database.Close();
	}CATCH(CDBException, e) {
		AfxMessageBox(L"Database error: " + e->m_strError);
	}
	END_CATCH;
}

CString Database::GetNextAutoNumber()
{
	CDatabase database;
	CString connectionString;
	CString sqlString;
	CString maxId = L"0";
	CString autoNumber;

	connectionString.Format(_T("Driver={Microsoft Access Driver (*.mdb, *.accdb)};Dbq=C:\\Users\\admin.teja\\Documents\\EmployeeDatabase.accdb;Uid=Admin;Pwd=;"));
	TRY{
		// Open the database
		CRecordset recset(&database);
		database.Open(NULL,false,false,connectionString);
		sqlString = L"SELECT TOP 1 * FROM EmployeeTable ORDER BY EmpID DESC";
		recset.Open(CRecordset::forwardOnly, sqlString, CRecordset::readOnly);
		while (!recset.IsEOF()) {
			recset.GetFieldValue(L"EmpID", maxId);
			recset.MoveNext();
		}
		database.Close();
	}CATCH(CDBException, e) {
		AfxMessageBox(L"Database error: " + e->m_strError);
	}
	END_CATCH;

	autoNumber.Format(L"%d", (_wtoi(maxId) + 1));
	return autoNumber;
}

void Database::DeleteRecord(CString id)
{
	CDatabase database;
	CString connectionString;
	CString sqlString;

	connectionString.Format(_T("Driver={Microsoft Access Driver (*.mdb, *.accdb)};Dbq=C:\\Users\\admin.teja\\Documents\\EmployeeDatabase.accdb;Uid=Admin;Pwd=;"));
	TRY{
		// Open the database
		database.Open(NULL,false,false,connectionString);
		sqlString = L"DELETE FROM EmployeeTable WHERE EmpID = ";
		sqlString.Append(id);
		database.ExecuteSQL(sqlString);
		database.Close();
	}CATCH(CDBException, e) {

		AfxMessageBox(L"Database error: " + e->m_strError);
	}
	END_CATCH;
}
vector<Employee> Database::FetchAllRecords() {
	vector<Employee> employeeRecords;
	CDatabase database;
	CString connectionString;
	CString sqlString;
	int iRecord = 0;

	connectionString.Format(_T("Driver={Microsoft Access Driver (*.mdb, *.accdb)};Dbq=C:\\Users\\admin.teja\\Documents\\EmployeeDatabase.accdb;Uid=Admin;Pwd=;"));
	TRY{
		// Open the database
		CRecordset recset(&database);
		database.Open(NULL,false,false,connectionString);
		sqlString = L"SELECT * FROM EmployeeTable ORDER BY EmpID ASC";
		recset.Open(CRecordset::forwardOnly, sqlString, CRecordset::readOnly);
		while (!recset.IsEOF()) {
			Employee record;
			recset.GetFieldValue(L"EmpID", record.Id);
			recset.GetFieldValue(L"Title",record.Title);
			recset.GetFieldValue(L"Age", record.Age);
			recset.GetFieldValue(L"FirstName", record.FirstName);
			recset.GetFieldValue(L"LastName", record.LastName);
			recset.GetFieldValue(L"Gender", record.Gender);
			recset.GetFieldValue(L"MobilePhone", record.MobileNumber);
			recset.GetFieldValue(L"EMail", record.Email);
			recset.GetFieldValue(L"BirthDate", record.DateOfBirth);
			recset.GetFieldValue(L"Address", record.Address);
			recset.GetFieldValue(L"JobTitle", record.JobTitle);
			recset.GetFieldValue(L"Salary", record.Salary);
			recset.GetFieldValue(L"Hiredate", record.HireDate);
			recset.GetFieldValue(L"YearsOfExp", record.YearsOfExperience);
			employeeRecords.push_back(record);
			recset.MoveNext();
		}
		database.Close();
	}CATCH(CDBException, e) {
		AfxMessageBox(L"Database error: " + e->m_strError);
	}
	END_CATCH;

	return employeeRecords;
}

list<Employee> Database::FetchAllEmployeeRecords()
{
	list<Employee> employeeRecords;
	CDatabase database;
	CString connectionString;
	CString sqlString;
	int iRecord = 0;

	connectionString.Format(_T("Driver={Microsoft Access Driver (*.mdb, *.accdb)};Dbq=C:\\Users\\admin.teja\\Documents\\EmployeeDatabase.accdb;Uid=Admin;Pwd=;"));
	TRY{
		// Open the database
		CRecordset recset(&database);
		database.Open(NULL,false,false,connectionString);
		sqlString = L"SELECT * FROM EmployeeTable ORDER BY EmpID ASC";
		recset.Open(CRecordset::forwardOnly, sqlString, CRecordset::readOnly);
		while (!recset.IsEOF()) {
			Employee record;
			recset.GetFieldValue(L"EmpID", record.Id);
			recset.GetFieldValue(L"Title",record.Title);
			recset.GetFieldValue(L"Age", record.Age);
			recset.GetFieldValue(L"FirstName", record.FirstName);
			recset.GetFieldValue(L"LastName", record.LastName);
			recset.GetFieldValue(L"Gender", record.Gender);
			recset.GetFieldValue(L"MobilePhone", record.MobileNumber);
			recset.GetFieldValue(L"EMail", record.Email);
			recset.GetFieldValue(L"BirthDate", record.DateOfBirth);
			recset.GetFieldValue(L"Address", record.Address);
			recset.GetFieldValue(L"JobTitle", record.JobTitle);
			recset.GetFieldValue(L"Salary", record.Salary);
			recset.GetFieldValue(L"Hiredate", record.HireDate);
			recset.GetFieldValue(L"YearsOfExp", record.YearsOfExperience);
			employeeRecords.push_back(record);
			recset.MoveNext();
		}
		database.Close();
	}CATCH(CDBException, e) {
		AfxMessageBox(L"Database error: " + e->m_strError);
	}
	END_CATCH;

	return employeeRecords;
}

EmployeeEntity::EmployeeEntity()
{
	Id = -1;
	FirstName = _T("");
	LastName = _T("");
	MobileNumber = _T("");
	HireDate = _T("");
	YearsOfExperience = 0;
	DateOfBirth = _T("");
	Title = _T("");
	Age = 0;
	Gender = _T("");
	Email = _T("");
	Address = _T("");
	JobTitle = _T("");
	Salary = 0.0;
}
extern "C" __declspec(dllexport) EmployeeEntity * GetEmp()
{
	Database db;
	list<Employee> records = db.FetchAllEmployeeRecords();
	int n = records.size();

	EmployeeEntity* empArr = new EmployeeEntity[n];

	list<Employee>::iterator employeeIterator;
	__int64 recordIndex = 0;
	for (employeeIterator = records.begin(); employeeIterator != records.end(); ++employeeIterator) {
		Employee record = *employeeIterator;
		EmployeeEntity temp = EmployeeEntity();
		temp.Address = (LPCTSTR)(record.Address);
		temp.Age = _wtoi(record.Age);
		temp.DateOfBirth = (LPCTSTR)(record.DateOfBirth);
		temp.Email = (LPCTSTR)(record.Email);
		temp.FirstName = (LPCTSTR)(record.FirstName);
		temp.Gender = (LPCTSTR)(record.Gender);
		temp.HireDate = (LPCTSTR)(record.HireDate);
		temp.Id = _wtoi(record.Id);
		temp.JobTitle = (LPCTSTR)(record.JobTitle);
		temp.LastName = (LPCTSTR)(record.LastName);
		temp.MobileNumber = (LPCTSTR)(record.MobileNumber);
		temp.Salary = _wtof(record.Salary);
		temp.Title = (LPCTSTR)(record.Title);
		temp.YearsOfExperience = _wtoi(record.YearsOfExperience);
		empArr[recordIndex] = temp;
		recordIndex++;
	}
	return empArr;
	
}

