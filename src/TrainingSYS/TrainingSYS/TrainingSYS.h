
// TrainingSYS.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTrainingSYSApp:
// �йش����ʵ�֣������ TrainingSYS.cpp
//
bool watch_dog();
class CTrainingSYSApp : public CWinApp
{
public:
	CTrainingSYSApp();

private:
	void InitConsoleWindow();
	
// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTrainingSYSApp theApp;