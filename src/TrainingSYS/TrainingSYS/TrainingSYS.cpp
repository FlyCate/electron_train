
// TrainingSYS.cpp : 定义应用程序的类行为。
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


// CTrainingSYSApp 构造

CTrainingSYSApp::CTrainingSYSApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CTrainingSYSApp 对象

CTrainingSYSApp theApp;


// CTrainingSYSApp 初始化

BOOL CTrainingSYSApp::InitInstance()
{
//TODO: call AfxInitRichEdit2() to initialize richedit2 library.
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();
	//添加加密狗监测
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

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	AfxInitRichEdit2();
	CTrainingSYSDlg dlg;
	m_pMainWnd = &dlg;
//yng
	CFileFind fFind;
	if (fFind.FindFile("res/debug"))
		InitConsoleWindow();
	printf_s("系统开始启动!\n");

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。

	return FALSE;
}

int CTrainingSYSApp::ExitInstance()
{
     // TODO: 在此添加专用代码和/或调用基类
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
		printf("没有发现Vikey!\n");
		AfxMessageBox("没有发现加密狗。");
		return false;
	}

	char UserPassWord[] = "32258064";
	char AdminPassWord[] = "47619047";
	Index = 0;



	dwRetCode = VikeyUserLogin(Index , UserPassWord);
	if(dwRetCode)
	{
		printf("用户权限登录失败!\n");
		AfxMessageBox("不是正确的加密狗");
		return false;
	}

	dwRetCode = VikeyAdminLogin(Index , AdminPassWord);
	if(dwRetCode)
	{
		printf("管理员权限登录失败!\n");
		AfxMessageBox("不是正确的加密狗");
		return false;
	}



	WORD wAddr = 0;
	WORD wLen = 32;
	BYTE buffer[1024];
	BYTE data[] = {0x17,0x87,0x3e,0x53,0x12,0x54,0x78,0x5a,0x7b,0x89,0x90,0x3c,0x21,0x36,0x67,0x31,0x8c,0xab,0xac,0x32,0x67,0x45,0x07,0x94,0x23,0x51,0x73,0x56,0x70,0x21,0x43,0x94};

	dwRetCode = VikeyReadData(Index, wAddr, wLen, buffer);
	if(dwRetCode)
	{
		printf("读ViKey数据失败!\n");
		AfxMessageBox("不是正确的加密狗");
		VikeyLogoff(Index);
		return false;
	}
	else
	{
		printf("读ViKey数据成功!\n");
		for(int i=0; i<wLen; i++)
		{
			if (data[i]!=buffer[i])
			{
				AfxMessageBox("不是正确的加密狗");
				VikeyLogoff(Index);
				return false;
			}
		}
	}
	VikeyLogoff(Index);
	return true;
}