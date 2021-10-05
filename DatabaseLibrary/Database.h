#pragma once
#include<vector>
#include"Employee.h"
#include <list>
#include<string>
#include<vector>
#include<string>
#include <atlstr.h>
#include<iostream>
#include<sstream>
using namespace std;
class __declspec(dllexport) Database
{
public:
	Database();
public:
	void InsertRecord(Employee record);
	void UpdateRecord(Employee record);
	void DeleteRecord(CString id);
	CString GetNextAutoNumber();
	vector<Employee> FetchAllRecords();
	list<Employee> FetchAllEmployeeRecords();
};
extern "C" class __declspec(dllexport) EmployeeEntity
{
public:
	int Id;
	LPCTSTR FirstName;
	LPCTSTR LastName;
	LPCTSTR MobileNumber;
	LPCTSTR HireDate;
	int YearsOfExperience;
	LPCTSTR DateOfBirth;
	LPCTSTR Title;
	int Age;
	LPCTSTR Gender;
	LPCTSTR Email;
	LPCTSTR Address;
	LPCTSTR JobTitle;
	double Salary;

	EmployeeEntity();
	//EmployeeEntity(int empId, std::string fullName, std::string city, double salary);
};

class __declspec(dllexport) MockDB
{
public:
	std::list<EmployeeEntity> GetEmployees();
};
