
#include "pch.h"
#include "CXml.h"
#include <afxwin.h>
#include "XmlElement.h"
#include <stack>
#include<vector>

using namespace std;

IMPLEMENT_DYNAMIC(CXml, CStdioFile)
CXml::CXml()
{
}

CXml::~CXml()
{
}
void CXml::Export(vector<Employee> employeerecords)
{
	CXml file;
	file.Open(L"EmployeeRecords.xml", CXml::modeCreate | CXml::modeWrite);

	file.WriteString(StringToStartTag(L"AdminApp"));
	for (unsigned int empIndex = 0; empIndex < employeerecords.size(); empIndex++) {
		Employee record = employeerecords[empIndex];
		file.WriteString(StringToStartTag(L"Employee"));
		file.WriteString(ConvertXmlFormat(L"Id", record.Id));
		file.WriteString(ConvertXmlFormat(L"HireDate", record.HireDate));
		file.WriteString(ConvertXmlFormat(L"YearsofExperience", record.YearsOfExperience));
		file.WriteString(ConvertXmlFormat(L"Title", record.Title));
		file.WriteString(ConvertXmlFormat(L"Age", record.Age));
		file.WriteString(ConvertXmlFormat(L"FirstName", record.FirstName));
		file.WriteString(ConvertXmlFormat(L"LastName", record.LastName));
		file.WriteString(ConvertXmlFormat(L"Gender", record.Gender));
		file.WriteString(ConvertXmlFormat(L"PhoneNumber", record.MobileNumber));
		file.WriteString(ConvertXmlFormat(L"Email", record.Email));
		file.WriteString(ConvertXmlFormat(L"DateofBirth", record.DateOfBirth));
		file.WriteString(ConvertXmlFormat(L"Address", record.Address));
		file.WriteString(ConvertXmlFormat(L"JobTitle", record.JobTitle));
		file.WriteString(ConvertXmlFormat(L"Salary", record.Salary));
		file.WriteString(StringToEndTag(L"Employee"));
	}
	file.WriteString(StringToEndTag(L"AdminApp"));
	return;
}

vector<Employee> CXml::Import(CString filepath)
{
	vector<Employee> employeeRecords;
	Employee record;
	XmlElement rootElement;
	rootElement.Name = L"AdminApp";
	XmlElement element;
	vector<XmlElement> employeeChilds;

	CXml file;
	file.Open(filepath, CXml::modeRead | CXml::typeText);

	CString singleLine;
	while (file.ReadString(singleLine))
	{
		element = GetXmlElement(singleLine);			// Get xml element from the single line

		if (IsEndTag(singleLine) && element.Name == L"Employee") {
			employeeRecords.push_back(record);			// Store record in employee records

			element.Child = employeeChilds;				// Update employee childs
			rootElement.Child.push_back(element);		// Update AdminApp child
			employeeChilds.clear();						// Remove all child elements from the employeeChild Vector
		}
		else if (!IsStartTag(singleLine) && !IsEmptyTag(singleLine)) {

			employeeChilds.push_back(element);

			if (element.Name == L"Id") {
				record.Id = element.Value;
			}
			else if (element.Name == L"HireDate") {
				record.HireDate = element.Value;
			}
			else if (element.Name == L"YearsofExperience") {
				record.YearsOfExperience = element.Value;
			}
			else if (element.Name == L"Title") {
				record.Title = element.Value;
			}
			else if (element.Name == L"Age") {
				record.Age = element.Value;
			}
			else if (element.Name == L"FirstName") {
				record.FirstName = element.Value;
			}
			else if (element.Name == L"LastName") {
				record.LastName = element.Value;
			}
			else if (element.Name == L"Gender") {
				record.Gender = element.Value;
			}
			else if (element.Name == L"PhoneNumber") {
				record.MobileNumber = element.Value;
			}
			else if (element.Name == L"Email") {
				record.Email = element.Value;
			}
			else if (element.Name == L"DateofBirth") {
				record.DateOfBirth = element.Value;
			}
			else if (element.Name == L"Address") {
				record.Address = element.Value;
			}
			else if (element.Name == L"JobTitle") {
				record.JobTitle = element.Value;
			}
			else if (element.Name == L"Salary") {
				record.Salary = element.Value;
			}
		}
	}
	XmlElement root = rootElement;
	file.Close();
	return employeeRecords;
}
CString CXml::GetTagName(CString xmlelement)
{
	CString tagName;
	if (IsStartTag(xmlelement)) {
		for (int xmlElementIndex = 1; xmlElementIndex < xmlelement.GetLength() - 1; xmlElementIndex++) {
			tagName.AppendChar(xmlelement[xmlElementIndex]);
		}
	}
	else if (IsEndTag(xmlelement)) {
		for (int xmlElementIndex = 2; xmlElementIndex < xmlelement.GetLength() - 1; xmlElementIndex++) {
			tagName.AppendChar(xmlelement[xmlElementIndex]);
		}
	}
	else if (IsEmptyTag(xmlelement)) {
		for (int xmlElementIndex = 1; xmlElementIndex < xmlelement.GetLength() - 2; xmlElementIndex++) {
			tagName.AppendChar(xmlelement[xmlElementIndex]);
		}
	}
	else {
		return '\0';
	}
	return tagName;
}

XmlElement CXml::GetXmlElement(CString text) {
	XmlElement element;

	if (IsStartTag(text)) {
		element = XmlElement(GetTagName(text), '\0');
	}
	else if (IsEndTag(text)) {
		element = XmlElement(GetTagName(text), '\0');
	}
	else if (IsEmptyTag(text)) {
		element = XmlElement(GetTagName(text), '\0');
	}
	else {
		vector<CString> XmlElements = StringSplitIntoXmlElements(text);
		element = XmlElement(GetTagName(XmlElements[0]), XmlElements[1]);
	}
	return element;
}

vector<CString> CXml::StringSplitIntoXmlElements(CString text)
{
	CString xmlElement;
	vector<CString> xmlElements;

	for (int textIndex = 0; textIndex < text.GetLength(); textIndex++) {
		if (text[textIndex] == '<' && !xmlElement.IsEmpty()) {				//value
			xmlElements.push_back(xmlElement);
			xmlElement.Empty();
		}
		else if ((xmlElement[0] == '<') && (text[textIndex] == '>')) {		//tag
			xmlElement.AppendChar(text[textIndex]);
			xmlElements.push_back(xmlElement);
			xmlElement.Empty();
			continue;
		}
		xmlElement.AppendChar(text[textIndex]);
	}

	return xmlElements;
}

bool CXml::IsStartTag(CString xmltag)
{
	if (StringSplitIntoXmlElements(xmltag).size() > 1)
		return false;

	int length = xmltag.GetLength();

	if (xmltag[0] != '<' || xmltag[1] == '/' || xmltag[length - 2] == '/' || xmltag[length - 1] != '>')
		return false;

	return true;

}
bool CXml::IsEndTag(CString xmltag)
{
	if (StringSplitIntoXmlElements(xmltag).size() > 1)
		return false;

	int length = xmltag.GetLength();

	if (xmltag[0] != '<' || xmltag[1] != '/' || xmltag[length - 2] == '/' || xmltag[length - 1] != '>')
		return false;

	return true;
}
bool CXml::IsEmptyTag(CString xmltag)
{
	if (StringSplitIntoXmlElements(xmltag).size() > 1)
		return false;

	int length = xmltag.GetLength();

	if (xmltag[0] != '<' || xmltag[1] == '/' || xmltag[length - 2] != '/' || xmltag[length - 1] != '>')
		return false;

	return true;
}
CString CXml::StringToStartTag(CString tagname)
{
	return OPENSTARTTAG + tagname + CLOSETAGNEWLINE;
}

CString CXml::StringToEndTag(CString tagname)
{
	return OPENENDTAG + tagname + CLOSETAGNEWLINE;
}

CString CXml::ConvertXmlFormat(CString tagname, CString tagvalue)
{
	return StartTag(tagname) + tagvalue + EndTag(tagname);
}

CString CXml::StartTag(CString tagname)
{
	return OPENSTARTTAG + tagname + CLOSETAGSYMBOL;
}

CString CXml::EndTag(CString tagname)
{
	return OPENENDTAG + tagname + CLOSETAGNEWLINE;
}

