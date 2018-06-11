
// TrainingSYSDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TrainingSYS.h"
#include "TrainingSYSDlg.h"
#include "afxdialogex.h"
#include "PageDlg1.h"
#include "PageDlg2.h"
#include "PageDlg3.h"
#include "ts_emf_wnd.h"
#include <gdiplus.h>
#include <io.h>    
#include <fcntl.h>  
using namespace Gdiplus;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define DEBUG_TEXT 0

int UI_X_SIZE = 1600;
int UI_Y_SIZE = 900;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CTrainingSYSDlg �Ի���




CTrainingSYSDlg::CTrainingSYSDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTrainingSYSDlg::IDD, pParent)
	,m_page1(NULL)
	,m_page2(NULL)
	,m_page3(NULL)
	,m_pemf_wnd(NULL)
	,m_net(NULL)
	//,m_selectnetdlg(NULL)
	//,m_cmd("1_1_1")
	,pictitlename("")
	,videotitlename("")
	,old_linktittlename("")
	,m_pictype(1)//δ����ͼƬ����
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bacakinf.clear();
	
}
CTrainingSYSDlg::~CTrainingSYSDlg()
{
	if (m_pemf_wnd)
		delete m_pemf_wnd;
	if (m_page1)
		delete m_page1;
	
	if (m_page2)
		delete m_page2;
	
	if (m_page3)
		delete m_page3;

	if (m_btnDlg)
		delete m_btnDlg;

	if (m_net)
		delete m_net;

	//if (m_selectnetdlg)
	//	delete m_selectnetdlg;
}
void CTrainingSYSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_MAIN, m_tab_main);
}

BEGIN_MESSAGE_MAP(CTrainingSYSDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_GETMINMAXINFO()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CTrainingSYSDlg::OnTcnSelchangeTabMain)
	ON_WM_SIZING()
	ON_WM_SIZE()
	ON_MESSAGE(WM_USER_BUTTON_MSG, &CTrainingSYSDlg::OnButtnMsg) 
	ON_BN_CLICKED(IDC_EXIT, &CTrainingSYSDlg::OnBnClickedExit)
	ON_BN_CLICKED(IDC_MIN, &CTrainingSYSDlg::OnBnClickedMin)
	
//	ON_WM_CLOSE()
//	ON_WM_HOTKEY()
//ON_WM_KEYDOWN()
ON_WM_TIMER()
END_MESSAGE_MAP()


// CTrainingSYSDlg ��Ϣ�������

BOOL CTrainingSYSDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
//	ShowWindow(SW_SHOWMAXIMIZED);
	m_path = GetFilePath() ;
	//SetMainWindowFullScreen();
	//::SendMessage(this->GetSafeHwnd(), WM_USER_BUTTON_MSG, (WPARAM)"1_1_1", NULL);
	//InitMainTabControl();
	//RepainTabchidWnd();
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	   
	//yng 2016-3-22
   //m_pemf_wnd = new ts_emf_wnd();
	//m_pemf_wnd->Create(this);

	//dzw 2016-3-24
	//��� ��ť�Ի���
	m_btnDlg = new ButtonDlg(this);
	m_btnDlg->Create(IDD_DLG_BUTTON, this);
	m_btnDlg->ShowWindow(true);
	
	m_pemf_wnd = new ts_emf_wnd(this);
	m_pemf_wnd->Create( &m_tab_main);
	m_pemf_wnd->ShowWindow(false);

	RepainMainWnd();
	RepainTabchidWnd();
	m_net = new Net_setting(this);
	m_net->Create(IDD_DLG_NET, this);
	m_net->ShowWindow(false);
	SetTimer(1,3000,NULL);
	/*m_selectnetdlg = new Selectnet(this);
	m_selectnetdlg->Create(IDD_DIG_TYPE, this);
	m_selectnetdlg->ShowWindow(false);*/
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTrainingSYSDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTrainingSYSDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������
 		CDialogEx::OnPaint();
// 		CRect   rect;  
// 
// 		GetClientRect(rect);  
// 		dc.FillSolidRect(rect,RGB(7,92,168));   //����Ϊ��ɫ����

		CRect   rect;   
		GetClientRect(&rect);   
		CDC   dcMem;   
		dcMem.CreateCompatibleDC(&dc);   
		CBitmap   bmpBackground;   
		bmpBackground.LoadBitmap(IDB_MAINBACK);

		BITMAP   bitmap;   
		bmpBackground.GetBitmap(&bitmap);   
		CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground);

		dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,
			rect.Width(),rect.Height(),SRCCOPY);
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTrainingSYSDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



// BOOL CTrainingSYSDlg::PreTranslateMessage(MSG* pMsg)
// {
// 	if(pMsg->message == WM_NCLBUTTONDBLCLK)
// 	{
// 		return TRUE;
// 	}
// 	// TODO: �ڴ����ר�ô����/����û���
// 
// 	return CDialogEx::PreTranslateMessage(pMsg);
// }
//����������ȫ��
void CTrainingSYSDlg::SetMainWindowFullScreen()
{
	int cx = GetSystemMetrics(SM_CXFULLSCREEN);
	int cy = GetSystemMetrics(SM_CYFULLSCREEN);
	CRect rt;
	SystemParametersInfo(SPI_GETWORKAREA,0,&rt,0);
	cy = rt.bottom;
	MoveWindow(0, 0, cx, cy); 
}
//����Ĭ�������С�Ĵ�С
void CTrainingSYSDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//������С�߶�����,�����Ҫ�Ļ�
	lpMMI->ptMinTrackSize.x = 800;
	lpMMI->ptMinTrackSize.y = 600;
	//�������߶�����,�����Ҫ�Ļ�
	//lpMMI->ptMaxTrackSize.x = 1366;
	//lpMMI->ptMaxTrackSize.y = 768;
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}
// ��ʼ��tabѡ�
void CTrainingSYSDlg::InitMainTabControl(void)
{
	 m_tab_main.DeleteAllItems();
	if (m_page1!=NULL)
	{
		m_page1->DestroyWindow();
		delete m_page1;
		m_page1 =NULL;
	}
	if (m_page2!=NULL)
	{
		m_page2->DestroyWindow();
		delete m_page2;
		m_page2 =NULL;
	}

	m_tab_main.InsertItem(0, pictitlename);
	m_page1 = new PageDlg1(this);
	m_page1->Create(IDD_DLG_PAGE1, &m_tab_main);
	m_page1->ShowWindow(true);	
	
	if (!videotitlename.IsEmpty())
	{
		m_tab_main.InsertItem(1, videotitlename);
		m_page2 = new PageDlg2(this);
		m_page2->Create(IDD_DLG_PAGE2, &m_tab_main);
		m_page2->ShowWindow(false);
	}

	if (!linktittlename.IsEmpty())
	{
		m_tab_main.InsertItem(2, linktittlename);
		//m_pemf_wnd->ShowWindow(true);
		CRect clientRect;
	    m_tab_main.GetClientRect(clientRect);
		m_pemf_wnd->ShowWindow(FALSE);
		m_pemf_wnd->MoveWindow(0,0,clientRect.Width(),clientRect.Height());
	}else
	{
		m_pemf_wnd->ShowWindow(FALSE);
	}


	m_tab_main.SetCurSel(0);
	RepainTabchidWnd();
}
// ���»���tab�Ĵ�С���ӶԻ���Ĵ�С
void CTrainingSYSDlg::RepainTabchidWnd(void)
{
	CRect rect,rect1;
	
	//��ȡ�ؼ����������
	m_tab_main.GetWindowRect(&rect1);//��ȡ�ؼ�����Ļ����
	ScreenToClient(&rect1);          //ת��Ϊ�Ի����ϵĿͻ�����

	//��ȡbutton�Ի�������
	CRect rc,buttonRC;
	m_btnDlg->GetClientRect(&buttonRC);
	GetClientRect(&rect);
	//rect.left  = rect1.left;
	rect.left = buttonRC.right;
	rect.top += 30;
	rect.bottom -= 20;
	rect.right -= 20;

	m_tab_main.MoveWindow(&rect);
	m_tab_main.GetClientRect(&rc);
	rc.left += 1;                  
	rc.right -= 1;   
	rc.top += 22;   
	rc.bottom -= 1;	
	if (m_page1 != NULL)
	{
		m_page1->MoveWindow(&rc);
	}
	if (!videotitlename.IsEmpty())
		m_page2->MoveWindow(&rc);
	
	if (m_pemf_wnd != NULL)
		m_pemf_wnd->MoveWindow(&rc);

}

void CTrainingSYSDlg::OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	int CurSel = m_tab_main.GetCurSel();
	switch(CurSel)
	{
		case 0:
			m_page1->ShowWindow(true);
			if (m_page2)
			{
				m_page2->ShowWindow(false);
			}else
			{
				if (linktittlename !="")
				{
					m_pemf_wnd->ShowWindow(false);
				}
			}
			if (linktittlename !="")
			{
				m_pemf_wnd->ShowWindow(false);
			}
			break;
		case 1:
			m_page1->ShowWindow(false);
			if (m_page2)
			{
				m_page2->ShowWindow(true);
				if (linktittlename !="")
				{
					m_pemf_wnd->ShowWindow(false);
				}
			}else
			{
				if (linktittlename !="")
				{
					m_pemf_wnd->ShowWindow(true);
				}
			}
	
			break;
		case 2:
			m_page1->ShowWindow(false);
			if (m_page2)
			{
				m_page2->ShowWindow(false);
			}
			if (linktittlename !="")
			{
				m_pemf_wnd->ShowWindow(true);
			}
			break;
		default:break;
	}   
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CTrainingSYSDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialogEx::OnSizing(fwSide, pRect);

	// TODO: �ڴ˴������Ϣ����������

}
void CTrainingSYSDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	//����button���ڸ߶�
	if(GetDlgItem(IDD_DLG_BUTTON))
	{
		CRect rect,rect1;
		GetClientRect(&rect);
		m_btnDlg->GetClientRect(&rect1);
		rect1.bottom = rect1.top + rect.Height();
		m_btnDlg->MoveWindow(rect1);
	}
	

	if (m_page1==NULL||m_page2==NULL||m_page3==NULL)
	{
		return;
	}
	// TODO: �ڴ˴������Ϣ����������
	CWnd *pwnd = GetDlgItem(IDC_TAB_MAIN);
	if (pwnd)
	{
		RepainTabchidWnd();
	}
}

//void CTrainingSYSDlg::OnBnClickedButton19()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	m_tab_main.DeselectAll(true);
//	m_tab_main.DeleteItem(0);
//	m_tab_main.DeleteItem(0);
//	m_tab_main.DeleteItem(0);
//	m_page1->DestroyWindow();
//	m_page2->DestroyWindow();
//	m_page3->DestroyWindow();
//}

//void CTrainingSYSDlg::OnBnClickedButton20()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//
//}

//��ȡ��������·��
CString CTrainingSYSDlg::GetFilePath() 
{ 
	char  exepath[1024];
	CString  strdir,tmpdir; 
	memset(exepath,0,sizeof(exepath)); 
	GetModuleFileName(NULL,exepath,sizeof(exepath)); 
	tmpdir=exepath; 
	strdir=tmpdir.Left(tmpdir.ReverseFind('\\'));
	return strdir; 
}

LRESULT CTrainingSYSDlg::OnButtnMsg(WPARAM wParam, LPARAM lParam) 
{
	TRACE((char *)wParam);
	TRACE("\n");
	CString cmd= (char *)wParam;	
	if (cmd == "")
		return 0;
	m_cmd =cmd;
	CString oldpictitlename = pictitlename;
	CString oldlinktittlename = linktittlename;
	 pictitlename = "";
	 videotitlename= "";
	  
	/*���������ȡtabpage1������*/
	 ReadXMlTitleName(m_cmd);
	 if (pictitlename == "")
	 {
		 pictitlename   = oldpictitlename;
		 linktittlename = oldlinktittlename;
		 return 0;
	 }else if ((linktittlename == oldlinktittlename)&& (pictitlename !=oldpictitlename))
	 {//��ǩ�Ѿ�����������û�ж�ȡ���µ���Ϣ��ͼ��ǩ��Ϣ��˵�����±�ǩ�����ڻ�ͼ������Ϊ��
		 linktittlename = "";
	 }
	 ReadVideoXMlTitleName(m_cmd);
	 InitMainTabControl();

	return 0;
}
//��ȡtabpage1��ѡ�����
int CTrainingSYSDlg::ReadXMlTitleName(CString cmd)
{	
	//����Picture XML
	TiXmlDocument doc;
	if (!doc.LoadFile(XML_PICTUREINF))
		return 1;
	//���Ҹ��ڵ�ʧ��
	TiXmlElement* root = doc.FirstChildElement();
	if(root == NULL)
	{	
		doc.Clear();
		return 1;
	}
	for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		CString elemName = elem->Value();
		// const char* attr;
		CString attr;
		attr = elem->Attribute("priority");
		//cmd ����ƥ����ȷ��
		if (cmd == attr)
		{	
			//cmd ����ƥ����ȷ��   
			for(TiXmlElement* e1 = elem->FirstChildElement(); e1 != NULL; e1 = e1->NextSiblingElement())
			{  
				string elemName = e1->Value();
				CString name;
				if (elemName =="title")
				{
					name =e1->Attribute("name");
					if (!name.IsEmpty())
					{
						pictitlename = name;
					}
				}
				if (elemName =="linktitle")
				{
					name =e1->Attribute("name");
					if (!name.IsEmpty())
					{
						linktittlename = name;
					}
				}
			}//end for
			doc.Clear();
			return 0;
		} 
	}
	doc.Clear();
	return 1;
}

int CTrainingSYSDlg::ReadVideoXMlTitleName(CString cmd)
{
	//����Video XML
	TiXmlDocument doc;
	if (!doc.LoadFile(XML_VIDEOINF))
		return 1;
	//���Ҹ��ڵ�ʧ��
	TiXmlElement* root = doc.FirstChildElement();
	if(root == NULL)
	{	
		doc.Clear();
		return 1;
	}
	for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		CString elemName = elem->Value();
		// const char* attr;
		CString attr;
		attr = elem->Attribute("priority");
		//cmd ����ƥ����ȷ��
		if (cmd == attr)
		{	
			//cmd ����ƥ����ȷ��   
			for(TiXmlElement* e1 = elem->FirstChildElement(); e1 != NULL; e1 = e1->NextSiblingElement())
			{  
				string elemName = e1->Value();
				CString name;
				if (elemName =="title")
				{
					name =e1->Attribute("name");
					if (!name.IsEmpty())
					{
						videotitlename = name;
						doc.Clear();
						return 0;
					}
					doc.Clear();
					return 1;
				}
			}
			doc.Clear();
			return 1;
		} 
	}
	doc.Clear();

	return 1;
}

// ���»������Ի���
void CTrainingSYSDlg::RepainMainWnd(void)
{
	//��ȡ�����С
	int nScreenWidth, nScreenHeight;  
	nScreenWidth = GetSystemMetrics(SM_CXSCREEN);  
	nScreenHeight = GetSystemMetrics(SM_CYSCREEN);
#if DEBUG_TEXT
	UI_X_SIZE = 1600;
	UI_Y_SIZE = 900;
#else
	UI_X_SIZE = nScreenWidth;
	UI_Y_SIZE = nScreenHeight;
#endif
	CRect rc;

	rc.left= (nScreenWidth- UI_X_SIZE)/2;
	rc.top = (nScreenHeight- UI_Y_SIZE)/2;
	rc.right=  rc.left + UI_X_SIZE;
	rc.bottom = rc.top + UI_Y_SIZE;

	this->MoveWindow(rc);

	CRect rect;
	m_btnDlg->GetClientRect(&rect);
	rect.bottom = rect.top + UI_Y_SIZE;
	m_btnDlg->MoveWindow(rect);

	GetDlgItem(IDC_EXIT)->GetClientRect(&rect);
	int width = 40;//rect.right - rect.left;
	int height = 30;//rect.bottom - rect.top;
	rect.top = 0;
	rect.bottom = height;
	rect.right = UI_X_SIZE - 10;
	rect.left = UI_X_SIZE - width - 10;
	GetDlgItem(IDC_EXIT)->MoveWindow(rect);

	GetDlgItem(IDC_MIN)->GetClientRect(&rect);
	//width = rect.right - rect.left;
	//height = rect.bottom - rect.top;
	rect.top = 0;
	rect.bottom = height;
	rect.right = UI_X_SIZE - width - 15;
	rect.left = UI_X_SIZE - width * 2 - 15;
	GetDlgItem(IDC_MIN)->MoveWindow(rect);

	setBtmBmp(IDC_EXIT, IDB_EXIT_UP);
	setBtmBmp(IDC_MIN, IDB_MIN_UP);
}

bool CTrainingSYSDlg::FindDataWitchcmd(CString cmd)
{
	vector<BACK_INF>::iterator it ;
	for (it = m_bacakinf.begin();it!=m_bacakinf.end();)
	{
		if ( cmd == it->cmd)
		{
			return true;
		}
	}
	return false;
}

//�˳�
void CTrainingSYSDlg::OnBnClickedExit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}

//��С��
void CTrainingSYSDlg::OnBnClickedMin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShowWindow(SW_SHOWMINIMIZED);
}


void CTrainingSYSDlg::OnOK()
{
	close_window();
}


void CTrainingSYSDlg::OnCancel()
{
	close_window();
}

void CTrainingSYSDlg::close_window()
{
	if (AfxMessageBox(_T("ϵͳ�رպ�,���е����Ͻ���ʧ,ȷ��Ҫ�ر�ϵͳ��?"),MB_OKCANCEL)==IDOK)
	{
		CDialogEx::OnCancel();
	}
}

BOOL CTrainingSYSDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_LBUTTONDOWN)
	{
		// ��ť����
		if (pMsg->hwnd == GetDlgItem(IDC_EXIT)->GetSafeHwnd())
		{
			setBtmBmp(IDC_EXIT, IDB_EXIT_DOWN);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_MIN)->GetSafeHwnd())
		{
			setBtmBmp(IDC_MIN, IDB_MIN_DOWN);
		}
	}
	else if(pMsg->message == WM_LBUTTONUP)
	{
		// ��ť����
		if (pMsg->hwnd == GetDlgItem(IDC_EXIT)->GetSafeHwnd())
		{
			setBtmBmp(IDC_EXIT, IDB_EXIT_UP);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_MIN)->GetSafeHwnd())
		{
			setBtmBmp(IDC_MIN, IDB_MIN_UP);
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CTrainingSYSDlg::setBtmBmp(int btnID, int bmpID)
{
	HINSTANCE hInstance;
	HBITMAP hBitmap;
	hInstance   =   ::AfxGetInstanceHandle();
	hBitmap =  ::LoadBitmap(hInstance, MAKEINTRESOURCE(bmpID) );
	((CButton *)GetDlgItem(btnID))->SetBitmap(hBitmap);
}

extern bool watch_dog();
void CTrainingSYSDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(nIDEvent==1)
	{
		KillTimer(1);
		while(!watch_dog())
		{

		}
		SetTimer(1,3000,NULL);
	}

	CDialogEx::OnTimer(nIDEvent);
}
