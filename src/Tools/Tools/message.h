#pragma once
#include <list>
using namespace std;

typedef struct tagCMD
{
	CString cmd;
	CString title;
	CString backpic;
	list<CString> listpic;
	CString linkTitle;
}CMD, *pCMD;