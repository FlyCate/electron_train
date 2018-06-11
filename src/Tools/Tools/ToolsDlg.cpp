
// ToolsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Tools.h"
#include "ToolsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define  XML_VIDEOINF		"res/video.xml"
#define  XML_PICTUREINF		"res/picture.xml"
#define  XML_OPTIONTUREINF	"res/option.xml"

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CToolsDlg 对话框




CToolsDlg::CToolsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CToolsDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CToolsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tabCtrl);
}

BEGIN_MESSAGE_MAP(CToolsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CToolsDlg::OnTcnSelchangeTab1)
	ON_WM_MOVE()
END_MESSAGE_MAP()


// CToolsDlg 消息处理程序

BOOL CToolsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_path = GetFilePath();

	m_tabCtrl.InsertItem(0,"图片xml");
	//m_tabCtrl.InsertItem(1,"视频xml");
	m_tabCtrl.SetCurSel(0);

	m_picDlg = new PICDLG(this);
	m_picDlg->Create(IDD_DIALOG_ADD_PIC, &m_tabCtrl);
	m_picDlg->ShowWindow(SW_HIDE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CToolsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

int first = 0;

void CToolsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

	switch (m_tabCtrl.GetCurSel())
	{
	case 0:
		{
			CRect rect;
			m_tabCtrl.GetWindowRect(&rect);
			rect.top += 20;
			m_picDlg->MoveWindow(rect);
			m_picDlg->ShowWindow(SW_SHOW);
			first = 1;
		}
		break;
	case 1:
		{

		}
		break;
	default:
		break;
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CToolsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString CToolsDlg::GetFilePath()
{ 
	char  exepath[1024];
	CString  strdir,tmpdir; 
	memset(exepath,0,sizeof(exepath)); 
	GetModuleFileName(NULL,exepath,sizeof(exepath)); 
	tmpdir=exepath; 
	strdir=tmpdir.Left(tmpdir.ReverseFind('\\'));
	return strdir; 
}

void CToolsDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	int CurSel = m_tabCtrl.GetCurSel();

	switch(CurSel)
	{
	case 0:
		m_picDlg->ShowWindow(SW_SHOW);
		break;
	case 1:
		m_picDlg->ShowWindow(SW_HIDE);
		break;
	}
	*pResult = 0;
}


void CToolsDlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	// TODO: 在此处添加消息处理程序代码
	if (first == 0) return;

	CRect rect;
	m_tabCtrl.GetWindowRect(&rect);
	rect.top += 20;
	m_picDlg->MoveWindow(rect);
}
