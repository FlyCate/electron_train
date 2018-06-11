
// TrainingSYS.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "TrainingSYS.h"
#include "TrainingSYSDlg.h"
#include <gdiplus.h>

#include "../ViKeySDK/ViKey.h"

#pragma comment (lib, "../ViKeySDK/ViKey.ia32.MT.lib")

using namespace Gdiplus;
#pragma comment( lib, "gdiplus.lib" )

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

ULONG_PTR gdiplusToken;

// CTrainingSYSApp

BEGIN_MESSAGE_MAP(CTrainingSYSApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CTrainingSYSApp ����

CTrainingSYSApp::CTrainingSYSApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CTrainingSYSApp ����

CTrainingSYSApp theApp;


// CTrainingSYSApp ��ʼ��

BOOL CTrainingSYSApp::InitInstance()
{
//TODO: call AfxInitRichEdit2() to initialize richedit2 library.
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();
	//��Ӽ��ܹ����
	if (!watch_dog())
	{
		exit(-1);
	}

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	AfxEnableControlContainer();

	/********************************************************************************/
     GdiplusStartupInput gdiplusStartupInput;
     GdiplusStartup(&gdiplusToken,&gdiplusStartupInput,NULL);
	/********************************************************************************/

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	AfxInitRichEdit2();
	CTrainingSYSDlg dlg;
	m_pMainWnd = &dlg;
//yng
	CFileFind fFind;
	if (fFind.FindFile("res/debug"))
		InitConsoleWindow();
	printf_s("ϵͳ��ʼ����!\n");

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�

	return FALSE;
}

int CTrainingSYSApp::ExitInstance()
{
     // TODO: �ڴ����ר�ô����/����û���
    GdiplusShutdown(gdiplusToken);
	CFileFind fFind;
	if (fFind.FindFile("res/debug"))
		FreeConsole();
    return CWinApp::ExitInstance();
}

void CTrainingSYSApp::InitConsoleWindow()
{
	AllocConsole();    
	SetConsoleTitle(_T("Debug Output"));
	freopen("CONOUT$","w",stdout);
}

bool watch_dog()
{
	//return true;
	DWORD dwRetCode;
	WORD Index;
	DWORD dwCount;
	DWORD dwHID;
	dwRetCode = VikeyFind(&dwCount);
	if(dwRetCode)
	{
		printf("û�з���Vikey!\n");
		AfxMessageBox("û�з��ּ��ܹ���");
		return false;
	}

	char UserPassWord[] = "32258064";
	char AdminPassWord[] = "47619047";
	Index = 0;



	dwRetCode = VikeyUserLogin(Index , UserPassWord);
	if(dwRetCode)
	{
		printf("�û�Ȩ�޵�¼ʧ��!\n");
		AfxMessageBox("������ȷ�ļ��ܹ�");
		return false;
	}

	dwRetCode = VikeyAdminLogin(Index , AdminPassWord);
	if(dwRetCode)
	{
		printf("����ԱȨ�޵�¼ʧ��!\n");
		AfxMessageBox("������ȷ�ļ��ܹ�");
		return false;
	}



	WORD wAddr = 0;
	WORD wLen = 32;
	BYTE buffer[1024];
	BYTE data[] = {0x17,0x87,0x3e,0x53,0x12,0x54,0x78,0x5a,0x7b,0x89,0x90,0x3c,0x21,0x36,0x67,0x31,0x8c,0xab,0xac,0x32,0x67,0x45,0x07,0x94,0x23,0x51,0x73,0x56,0x70,0x21,0x43,0x94};

	dwRetCode = VikeyReadData(Index, wAddr, wLen, buffer);
	if(dwRetCode)
	{
		printf("��ViKey����ʧ��!\n");
		AfxMessageBox("������ȷ�ļ��ܹ�");
		VikeyLogoff(Index);
		return false;
	}
	else
	{
		printf("��ViKey���ݳɹ�!\n");
		for(int i=0; i<wLen; i++)
		{
			if (data[i]!=buffer[i])
			{
				AfxMessageBox("������ȷ�ļ��ܹ�");
				VikeyLogoff(Index);
				return false;
			}
		}
	}
	VikeyLogoff(Index);
	return true;
}