#pragma once
#include <afx.h>
#include<vector>
#include<stack>
#include "../DatabaseLibrary/Employee.h"
#include "XmlElement.h"
using namespace std;

#define OPENSTARTTAG _T("<")
#define CLOSETAGSYMBOL _T(">")
#define CLOSETAGNEWLINE _T(">\n")
#define OPENENDTAG _T("</")

class CXml :public CStdioFile
{
	DECLARE_DYNAMIC(CXml)
public:
	CXml();
	virtual ~CXml();
public:
	void Export(vector<Employee> employeerecords);
	vector<Employee> Import(CString filepath);
private:
	CString StringToStartTag(CString tagname);
	CString StringToEndTag(CString tagname);
	CString ConvertXmlFormat(CString tagname, CString tagvalue);
	CString StartTag(CString tagname);
	CString EndTag(CString tagname);
	bool IsStartTag(CString xmltag);
	bool IsEndTag(CString xmltag);
	bool IsEmptyTag(CString xmltag);
	XmlElement GetXmlElement(CString text);
	vector<CString> StringSplitIntoXmlElements(CString text);
	CString GetTagName(CString xmlelement);
};

