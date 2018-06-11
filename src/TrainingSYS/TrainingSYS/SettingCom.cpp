// SettingCom.cpp : 实现文件
//

#include "stdafx.h"
#include "TrainingSYS.h"
#include "SettingCom.h"
#include "afxdialogex.h"
#include "TrainingSYSDlg.h"
#include "MyMessagebox.h"
#include "ts_emf_wnd.h"
#define  PICTURE_COM_LEVEL     "\\res\\picture_com\\"  
#define  COMBUFLEN 20
byte Bufcom[COMBUFLEN]={0};
#define COMM_PKT_MSG WM_USER+20
// SettingCom 对话框

IMPLEMENT_DYNAMIC(SettingCom, CDialogEx)
bool SettingCom::m_first = false;
SettingCom::SettingCom(CWnd* pParent /*=NULL*/)
	: CDialogEx(SettingCom::IDD, pParent)
	,m_com_name("")
	,m_com_index(-1)
	,m_bund(115200)
	,m_isopen(false)
	, m_tm_id(156)
    , m_send_flag()
    , m_tmoutinf("")
	,m_pThread(NULL)
	,m_runing(false)
{
	parent =  (CTrainingSYSDlg *)pParent;
	path =    parent->m_path+PICTURE_COM_LEVEL ; 
}

SettingCom::~SettingCom()
{
}

void SettingCom::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CB_COM, m_cb_comsel);
	DDX_Control(pDX, IDC_CB_BUND, m_cb_bundsel);
	DDX_Control(pDX, IDC_BTN_OK_COM, m_btn_ok);

	DDX_Control(pDX, IDC_CHECK_OPEN, m_btn_open);
}


BEGIN_MESSAGE_MAP(SettingCom, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_OK_COM, &SettingCom::OnBnClickedBtnOkCom)
	ON_CBN_SELCHANGE(IDC_CB_COM, &SettingCom::OnCbnSelchangeCbCom)
	ON_CBN_SELCHANGE(IDC_CB_BUND, &SettingCom::OnCbnSelchangeCbBund)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CHECK_OPEN, &SettingCom::OnBnClickedCheckOpen)
	//ON_MESSAGE(WM_COMM_RXCHAR,  &SettingCom::OnComm)  //消息映射
	ON_MESSAGE(COMM_PKT_MSG,  &SettingCom::serial_hander_data)  //消息映射
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// SettingCom 消息处理程序


BOOL SettingCom::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect   temprect(0,0,280,200);

	CWnd::SetWindowPos(NULL,0,0,temprect.Width(),temprect.Height(),SWP_NOZORDER|SWP_NOMOVE);

	m_btn_ok.SetSkin(path+"play_normal.bmp",path+"play_down.bmp",path+"play_normal.bmp",path+"play_normal.bmp",path+"play_normal.bmp",path+"play_mask.bmp",0,0,0);
	m_btn_open.SetSkin(path+"com_normal.bmp",path+"com_down.bmp",path+"com_normal.bmp",path+"com_normal.bmp",path+"com_normal.bmp",path+"com_mask.bmp",0,0,0);
	m_com.Hkey2ComboBox(m_cb_comsel);
	CString str;
	if (m_cb_comsel.GetCount()>0)
	{

		m_cb_comsel.SetCurSel(0);

		m_cb_comsel.GetLBText(m_cb_comsel.GetCurSel(),str);
		if (str.GetLength()>3)
		{
			str = str.Mid(3);
			m_com_index = atoi(str.GetString())	;
		}
	}

	m_cb_bundsel.SetCurSel(7);

	m_cb_bundsel.GetLBText(m_cb_bundsel.GetCurSel(),str);
	if (str.GetLength()>0)
	{
		m_bund = atoi(str.GetString())	;
	}
	m_btn_ok.ShowWindow(true);
	removechildwnd();


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void SettingCom::DrawBmp(CString strname)
{
	CString dstname;

	if (strname== "")
		return;
	dstname =  strname; 
	HBITMAP hbmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
		dstname, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE); 
	CBitmap bitmap;
	bitmap.Attach(hbmp); //关联位图对象
	CDC *pDC = GetDC();
	CDC memdc;//创建内存画家
	memdc.CreateCompatibleDC(NULL);
	memdc.SelectObject(&bitmap);
	CRect bmpRC;
	this->GetWindowRect(&bmpRC);
	BITMAP bmp;
	bitmap.GetBitmap(&bmp);
	pDC->SetStretchBltMode(HALFTONE);
	pDC->StretchBlt(0,0,bmpRC.Width(),bmpRC.Height(),&memdc,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
	//pDC->StretchBlt(0,0,bmp.bmWidth,bmp.bmHeight,&memdc,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
	memdc.DeleteDC();
	ReleaseDC(pDC);
} 


void SettingCom::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	DrawBmp(path + "comsetting.bmp");
	removechildwnd();
}

//ok按键
void SettingCom::OnBnClickedBtnOkCom()
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(FALSE);
	if (parent->m_pemf_wnd != NULL)
	{
		//parent->m_pictype =1;
		//parent->m_pemf_wnd->setEmfType(parent->m_pictype);
		//send_cmd_all_bsp_chk();
	}

}

//com口选择改变
void SettingCom::OnCbnSelchangeCbCom()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	// TODO: 在此添加控件通知处理程序代码
	m_cb_comsel.GetLBText(m_cb_comsel.GetCurSel(),str);
	if (str.GetLength()>3)
	{
		str = str.Mid(3);
		m_com_index = atoi(str.GetString())	;
	}

}

//波特率选择改变
void SettingCom::OnCbnSelchangeCbBund()
{
	CString str;
	m_cb_bundsel.GetLBText(m_cb_bundsel.GetCurSel(),str);
	if (str.GetLength()>0)
	{
		m_bund = atoi(str.GetString())	;
	}
}


HBRUSH SettingCom::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO:  在此更改 DC 的任何特性
	if(nCtlColor == CTLCOLOR_STATIC  )
	{
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_MAINITEM )
		{
			pDC->SetTextColor(RGB(255,255,255));
		}else
		{
			pDC->SetTextColor(RGB(0,0,0));
		}
		pDC->SetBkMode(TRANSPARENT);//设置背景透明
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	} 
	return hbr;
}


int SettingCom::removechildwnd(void)
{

	CRect rt,newrt,parent_rt;
	this->GetClientRect(parent_rt);
	GetDlgItem(IDC_STATIC_MAINITEM)->GetWindowRect(rt);

	//主标题
	newrt.top   =  parent_rt.top+5;
	newrt.bottom = rt.Height()+5;
	newrt.left   = parent_rt.Width()/2 -rt.Width()/2;
	newrt.right  = newrt.left+ rt.Width();
	GetDlgItem(IDC_STATIC_MAINITEM)->MoveWindow(newrt);

	//文本com
	newrt.top   =  parent_rt.top+50;
	newrt.bottom = newrt.top + rt.Height() ;
	newrt.left   = 20;
	newrt.right  = newrt.left  + rt.Width() ;
	GetDlgItem(IDC_ST_COM)->MoveWindow(newrt);

	//cbcom
	m_cb_comsel.GetWindowRect(rt);
	newrt.top   =  parent_rt.top+50;
	newrt.bottom = newrt.top + rt.Height() ;
	newrt.left   = 100;
	newrt.right  = newrt.left  + rt.Width() ;
	m_cb_comsel.MoveWindow(newrt);
		//cbbund
	m_cb_bundsel.GetWindowRect(rt);
	newrt.top   =  parent_rt.top+100;
	newrt.bottom = newrt.top + rt.Height() ;
	newrt.left   = 100;
	newrt.right  = newrt.left  + rt.Width() ;
	m_cb_bundsel.MoveWindow(newrt);


	newrt.top   =  parent_rt.top+100;
	newrt.bottom = newrt.top + rt.Height() ;
	newrt.left   = 20;
	newrt.right  = 20 + rt.Width() ;
	GetDlgItem(IDC_ST_BUND)->MoveWindow(newrt);
	//btn open
	m_btn_open.GetWindowRect(rt);
	newrt.top   =   parent_rt.bottom -rt.Height() -20;
	newrt.bottom =  parent_rt.bottom -20 ;
	newrt.left   = parent_rt.Width()/2 - rt.Width()-10;
	newrt.right  = newrt.left  + rt.Width() ;
	
	m_btn_open.MoveWindow(newrt);

	m_btn_ok.GetWindowRect(rt);
	newrt.top   =  parent_rt.bottom -rt.Height() -20;
	newrt.bottom = parent_rt.bottom -20 ;
	newrt.left   = parent_rt.Width()/2 +10;
	newrt.right  = newrt.left  + rt.Width() ;
	m_btn_ok.MoveWindow(newrt);


	int nScreenWidth, nScreenHeight;  
	nScreenWidth = GetSystemMetrics(SM_CXSCREEN);  
	nScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	CRect mainrt,newrct;
	GetWindowRect(mainrt);
	newrct.left = nScreenWidth/2 - mainrt.Width()/2;
	newrct.right += newrct.left + mainrt.Width();
	newrct.top =  nScreenHeight/2 - mainrt.Height()/2;
	newrct.bottom =  newrct.top +  mainrt.Height();
	this->MoveWindow(newrct);
	return 0;
}

//打开串口按键
void SettingCom::OnBnClickedCheckOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	m_isopen = !m_isopen;
	if(m_isopen)
	{
		if(m_com.OpenCOM(m_com_index,m_bund,0))
		//if(m_com.InitPort(this,m_com_index,m_bund))
		{
			//m_com.StartMonitoring();
			//开启串口线程
			start_serial_thread();
			m_btn_open.SetCheck(true);
			m_cb_bundsel.EnableWindow(FALSE);
			m_cb_comsel.EnableWindow(FALSE);
			/*this->ShowWindow(false);*/
		}else
		{
			m_cb_bundsel.EnableWindow(TRUE);
			m_cb_comsel.EnableWindow(TRUE);
			
			 MsgBox("错误","没有发现此串口或者被占用",path+"messzgebox.bmp",path);
			m_isopen=FALSE;
			m_btn_open.SetCheck(false);
		}
	}else
	{
		m_cb_bundsel.EnableWindow(TRUE);
		m_cb_comsel.EnableWindow(TRUE);
		m_btn_open.SetCheck(false);
		//m_com.StopMonitoring();
	   	stop_serial_thread();
		//m_com.ClosePort();
		 m_com.CloseCOM();
		/*this->ShowWindow(false);*/
	}
}
//串口接收处理函数
LONG SettingCom::OnComm(WPARAM ch,LPARAM port)
{
	static int num =0;
	byte data = (byte)ch;

	Bufcom[num++] = data;
	if (num >= COMBUFLEN)
	{
		num  = 0;
	}else
	{
		if (num == 1)
		{//校验枕头
			if (Bufcom[0]  != FRAME_HEADER)
			{
				num =0;
			}
		}else if (num > 2)
		{   //教研真伪不
			if ((Bufcom[1]+3)  == num)
			{
				if (Bufcom[num-1] != FRAME_END)
				{
					num =0;
				}else
				{
					//解析正常数据
					PKT pkt;
					memcpy(&pkt,Bufcom,num);
					handerdatapkt(&pkt);
					num =0;
				}
			}
		}
	}

	//Bufcom
	return 0;
}
//串口发送
bool  SettingCom::serialsenddata(byte * p,int len)
{
	if (p == NULL || len <=  0)
	{
		return false;
	}
	if (!m_isopen)
	{ 
		MsgBox("错误","请先打开串口",path+"messzgebox.bmp",path);
		return false;
	}
//	m_com.WriteToPort(p,  len);
	m_com.Write((char*)p, len);
	return true;
}
//串口发送
bool  SettingCom::serialsenddata(byte * p,int len,bool ischk,CString inf,DWORD ms)
{
	if (p == NULL || len <=  0 )
	{
		return false;
	}
	if (!m_isopen)
	{ 
		MsgBox("错误","请先打开串口",path+"messzgebox.bmp",path);
		return false;
	}
	//m_com.WriteToPort(p,  len);
	m_com.Write((char*)p, len);
	if (ischk)
	{
		m_tmoutinf = inf;
		m_send_flag = true;
		SetTimer(m_tm_id,ms,NULL);
	}
	return true;
}
VOID SettingCom::MakeCMDPKT(PKT *pkt,byte cmd,byte  *payload,byte paylen)
{
	if (pkt == NULL)
		return;
	pkt->header = FRAME_HEADER;
	pkt->length = 1 + paylen;
	pkt->cmd    = cmd;
	memcpy(pkt->payload,payload,paylen);
	pkt->payload[paylen] = FRAME_END;
}
//整个专家运行
bool SettingCom::send_cmd_whole_start_run(void)
{
	PKT pkt;
	byte payload[20] ={0};
	DWORD data = parent->m_pemf_wnd->GetCableStat();
	payload[0] = 1;
	payload[1] = data >> 24;
	payload[2] = data >> 16;
	payload[3] = data >> 8 ;
	payload[4] = data >> 0 ;
	MakeCMDPKT(&pkt, CMD_START_RUN, payload, 5); 
	return serialsenddata((byte*)&pkt, pkt.length +3 ,true,"发送 整个专家系统运行 超时",3000);

}
//整个专家运行
bool SettingCom::send_cmd_whole_stop_run(void)
{
	PKT pkt;
	byte payload[20] ={0};
	payload[0] = 0;
	MakeCMDPKT(&pkt, CMD_START_STOP, payload, 1); 

    return serialsenddata((byte*)&pkt, pkt.length +3 ,true,"发送 整个专家系统停止 超时",3000);

}
//开始扫描
bool SettingCom::send_cmd_start_scan(void)
{
	PKT pkt;
	byte payload[20] ={0};
	payload[0] = 1;
	MakeCMDPKT(&pkt, CMD_DEG_SCAN, payload, 1); 
   return serialsenddata((byte*)&pkt, pkt.length +3 ,true,"发送 开始扫描 超时",3000);

}
//结束扫描
bool  SettingCom::send_cmd_stop_scan(void)
{   
	SetTimer(148,200,NULL);
	return true;
	/*
	PKT pkt;
	byte payload[20] ={0};
	payload[0] = 0;
	MakeCMDPKT(&pkt, CMD_END_SCAN, payload, 1); 
	return serialsenddata((byte*)&pkt, pkt.length +3 ,true,"发送 结束扫描 超时",3000);
	*/
}

//所有采集板上电检测
bool SettingCom::send_cmd_all_bsp_chk(void)
{
	PKT pkt;
	byte payload[20] ={0};
	MakeCMDPKT(&pkt, CMD_POWER_CHK, payload, 0); 
	return serialsenddata((byte*)&pkt, pkt.length +3 ,true,"发送 所有采集板上电检测 超时",3000);
}
//发送连接错误
bool  SettingCom::send_link_error(void)
{
	PKT pkt;
	byte payload[20] ={0};
	MakeCMDPKT(&pkt, CMD_POWER_LINK_ERROR_FD, payload, 0); 
	return serialsenddata((byte*)&pkt, pkt.length +3 ,false,"",0);

}
void SettingCom::handerdatapkt(PKT * pkt)
{

	CString str ="";
	m_send_flag = false;  //清空发送标记
	switch (pkt->cmd)
	{
	case CMD_START_RUN_FD:
		if (pkt->payload[0])
		{
			str ="专家系统开始运行成功";
		}else
		{
			str ="专家系统停止运行成功";
		}

	    MsgBox("信息提示",str,path+"messzgebox.bmp",path);
		break;
	case CMD_DEG_SCAN_FD:
		if (pkt->payload[0])
		{
			str ="开始扫描运行成功";
		}else
		{
			str ="结束扫描运行成功";
		}
		break;
	case CMD_POWER_CHK_FD:
		if (pkt->length == 1)
		{
			str ="所有采集板上电工作成功";
		}else
		{  
			CString inf;
			if (pkt->length >= 2)
			{
				inf.Format("采集板\"%d\" ",pkt->payload[0]);
				str += inf;
			}
			if (pkt->length >= 3)
			{
				inf.Format("采集板\"%d\" ",pkt->payload[1]);
				str += inf;
			}
			if (pkt->length >= 4)
			{
				inf.Format("采集板\"%d\" ",pkt->payload[2]);
				str += inf;
			}
			if (pkt->length >= 4)
			{
				inf.Format("采集板\"%d\" ",pkt->payload[3]);
				str += inf;
			}
			if (pkt->length >= 6)
			{
				inf.Format("采集板\"%d\" ",pkt->payload[4]);
				str += inf;
			}
			str += "没有上电或者异常";
		}
		 MsgBox("信息提示",str,path+"messzgebox.bmp",path);
		break;
	case CMD_POWER_LINK_FD:
		ParselinkLine(pkt);
		break;
	default:break;
	}
}
void SettingCom::ParselinkLine(PKT * pkt)
{   int mode = 0;
	bool res= false;
	CTrainingSYSDlg *p = parent;

	if (p->m_pemf_wnd == NULL)
		return;
	if( p->m_pictype == 0 || p->m_pictype>4 )
		return;
	if ( pkt->length < 3)
		return;
	mode =p->m_pemf_wnd->getmode();//1手动模式 0 自动模式
	if ( (p->m_btnDlg->m_startCheck) && (!mode ) )
	{
		res = p->m_pemf_wnd->LinkLine(pkt->payload,  pkt->length-1);
		if (res ==false)
		{
			send_link_error();
		}
	}
		
		
}

void SettingCom::OnTimer(UINT_PTR nIDEvent)
{
	static  byte m_stop_num =0;
	if (nIDEvent == m_tm_id)
	{
		if (m_send_flag == true)
		{    
		     KillTimer(nIDEvent);

			 MsgBox("提示",m_tmoutinf,path+"messzgebox.bmp",path);
			 m_tmoutinf = "";
			 m_send_flag = false;
		}
		else
		{
			 m_tmoutinf = "";
			 KillTimer(nIDEvent);
		}
	}else if (nIDEvent == 148 )
	{
		if ( (m_stop_num++) >= 3 )
		{
			m_stop_num=0;
			KillTimer(nIDEvent);
		}else
		{
			PKT pkt;
			byte payload[20] ={0};
			payload[0] = 0;
			MakeCMDPKT(&pkt, CMD_END_SCAN, payload, 1); 
			serialsenddata((byte*)&pkt, pkt.length +3 ,FALSE,"",0);
		}
	}
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnTimer(nIDEvent);
}


BOOL SettingCom::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	DrawBmp(path + "comsetting.bmp");
	return true;
	//return CDialogEx::OnEraseBkgnd(pDC);
}


void SettingCom::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnLButtonDown(nFlags, point);
	PostMessage(WM_NCLBUTTONDOWN,
		HTCAPTION,
		MAKELPARAM(point.x, point.y));
}
static UINT Serial_hander_thread(LPVOID pParam);//线程函数声明
UINT Serial_hander_thread(LPVOID pParam)
{
	SettingCom *dlg=(SettingCom*)pParam;
	unsigned int len =0;
	unsigned char ch =0;
	static int num =0;
	while(dlg->m_runing)
	{
		len = dlg->m_com.Read((char*)&ch,1);
		if (len <= 0)
		{
			Sleep(1);
			continue;
		}else
		{
			Bufcom[num++] = ch;
			if (num >= COMBUFLEN)
			{
				num  = 0;
			}else
			{
				if (num == 1)
				{//校验枕头
					if (Bufcom[0]  != FRAME_HEADER)
					{
						num =0;
					}
				}else if (num > 2)
				{   //教研真伪不
					if ((Bufcom[1]+3)  == num)
					{
						if (Bufcom[num-1] != FRAME_END)
						{
							num =0;
						}else
						{
							//解析正常数据
							PKT *pkt =new PKT;
							memcpy(pkt,Bufcom,num);
							::PostMessage(dlg->GetSafeHwnd(),COMM_PKT_MSG,(WPARAM)pkt,0);
							num =0;
						}
					}
				}
			}

		}//end else
	}//end while
	return 0;
}

void SettingCom::start_serial_thread()
{
	if (m_pThread==NULL)
	{
		m_runing = true;
		m_pThread = AfxBeginThread(Serial_hander_thread, this); //启动线程
	}
}
void SettingCom::stop_serial_thread()
{
	m_runing = false;
	m_pThread = NULL ;
}	
LONG SettingCom::serial_hander_data(WPARAM ch,LPARAM port)
{
	PKT *pkt =(PKT*)ch;
	handerdatapkt(pkt);
	delete pkt;
	return 0;
}