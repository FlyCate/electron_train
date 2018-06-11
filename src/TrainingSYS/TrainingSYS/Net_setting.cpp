// Net_setting.cpp : 实现文件
//

#include "stdafx.h"
#include "TrainingSYS.h"
#include "Net_setting.h"
#include "afxdialogex.h"
#include <winsock2.h>  
#include "MyMessagebox.h"
#include "ts_emf_wnd.h"
#define PICTURE_NET_LEVEL  "\\res\\picture_com\\" 
// Net_setting 对话框
#define NETBUFLEN 1024
#define NET_PKT_MSG WM_USER+21
#define PORTNUMBER 8088
IMPLEMENT_DYNAMIC(Net_setting, CDialogEx)

Net_setting::Net_setting(CWnd* pParent /*=NULL*/)
	: CDialogEx(Net_setting::IDD, pParent)
	,m_ip("")
	,m_port(PORTNUMBER)
	,m_r_port(PORTNUMBER+1)
	,m_islink(false)
	,m_sock(INVALID_SOCKET)
	,m_pThread(NULL)
{
	parent =  (CTrainingSYSDlg *)pParent;
	path =    parent->m_path+PICTURE_NET_LEVEL ; 
}

Net_setting::~Net_setting()
{
		WSACleanup(); 
}

void Net_setting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_IPADDR_IN, m_ip_input);
	DDX_Control(pDX, IDC_CH_NET_LINK, m_link_net);
	DDX_Control(pDX, IDC_BTN_NET_CLOSE1, m_close_wind);
	DDX_Control(pDX, IDC_NET_PORT1, m_port_input);
	DDX_Control(pDX, IDC_NET_PORT2, m_r_port_input);
}


BEGIN_MESSAGE_MAP(Net_setting, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_NET_CLOSE1, &Net_setting::OnBnClickedBtnNetClose)
	ON_BN_CLICKED(IDC_CH_NET_LINK, &Net_setting::OnBnClickedBtnNetLink)
	ON_MESSAGE(NET_PKT_MSG,  &Net_setting::serial_hander_data)  //消息映射
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	//	ON_WM_MBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// Net_setting 消息处理程序

//网络对话框显示关闭
void Net_setting::OnBnClickedBtnNetClose()
{
	// TODO: 在此添加控件通知处理程序代码
		this->ShowWindow(FALSE);
}

//网络连接按键
void Net_setting::OnBnClickedBtnNetLink()
{
	// TODO: 在此添加控件通知处理程序代码
	CString ipstr;
	m_islink= !m_islink;
	if (m_islink)
	{
		m_ip = get_ip_address();
		if (m_ip.IsEmpty())
		{
			m_islink = false;
			m_link_net.SetCheck(false);
			return;
		}
		m_port = get_port_address(&m_port_input);
		if (m_port < 0)
		{
			m_islink = false;
			m_link_net.SetCheck(false);
			return;
		}
		m_r_port = get_port_address(&m_r_port_input);
		if (m_r_port < 0)
		{
			m_islink = false;
			m_link_net.SetCheck(false);
			return;
		}
		if (net_link_init())
		{
			m_islink = false;
			m_link_net.SetCheck(false);
			return;
		}
		start_net_thread();
		m_ip_input.EnableWindow(false);
		m_port_input.EnableWindow(false);
		m_r_port_input.EnableWindow(false);
		m_link_net.SetCheck(true);
	}else
	{
		if (m_sock>0)
		{
			closesocket(m_sock);
			m_sock =INVALID_SOCKET;
		}
		stop_net_thread();
		m_ip_input.EnableWindow(true);
		m_port_input.EnableWindow(true);
		m_r_port_input.EnableWindow(true);
		m_link_net.SetCheck(false);
	}
}


BOOL Net_setting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect   temprect(0,0,280,250);

	CWnd::SetWindowPos(NULL,0,0,temprect.Width(),temprect.Height(),SWP_NOZORDER|SWP_NOMOVE);

    m_close_wind.SetSkin(path+"play_normal.bmp",path+"play_down.bmp",path+"play_normal.bmp",path+"play_normal.bmp",path+"play_normal.bmp",path+"play_mask.bmp",0,0,0);
	m_link_net.SetSkin(path+"com_normal.bmp",path+"com_down.bmp",path+"com_normal.bmp",path+"com_normal.bmp",path+"com_normal.bmp",path+"com_mask.bmp",0,0,0);
	removechildwnd();
	m_ip_input.SetAddress(192,168,1,213);
	CString str;
	str.Format("%d",m_port);
	m_port_input.SetWindowText(str);

	str.Format("%d",m_r_port);
	m_r_port_input.SetWindowText(str);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
int Net_setting::removechildwnd(void)
{
	CRect rt,newrt,parent_rt;
	this->GetClientRect(parent_rt);

	//主标题
	GetDlgItem(IDC_ST_NET_TLE)->GetWindowRect(rt);
	newrt.top   =  parent_rt.top+5;
	newrt.bottom = rt.Height()+5;
	newrt.left   = parent_rt.Width()/2 -rt.Width()/2;
	newrt.right  = newrt.left+ rt.Width();
	GetDlgItem(IDC_ST_NET_TLE)->MoveWindow(newrt);

	//IPADDR
    m_ip_input.GetWindowRect(rt);
	newrt.top   =  parent_rt.top+50;
	newrt.bottom = newrt.top + rt.Height() ;
	newrt.left   = 100;
	newrt.right  = newrt.left  + rt.Width() ;
	m_ip_input.MoveWindow(newrt);
	//port
	m_port_input.GetWindowRect(rt);
	newrt.top   =  parent_rt.top+100;
	newrt.bottom = newrt.top + rt.Height() ;
	newrt.left   = 100;
	newrt.right  = newrt.left  + rt.Width() ;
	m_port_input.MoveWindow(newrt);
	//本地端口输入
	m_r_port_input.GetWindowRect(rt);
	newrt.top   =  parent_rt.top+150;
	newrt.bottom = newrt.top + rt.Height() ;
	newrt.left   = 100;
	newrt.right  = newrt.left  + rt.Width() ;
	m_r_port_input.MoveWindow(newrt);


	//文本IP
	GetDlgItem(IDC_ST_IP)->GetWindowRect(rt);
	newrt.top   =  parent_rt.top+50;
	newrt.bottom = newrt.top + rt.Height() ;
	newrt.left   = 20;
	newrt.right  = newrt.left  + rt.Width() ;
	GetDlgItem(IDC_ST_IP)->MoveWindow(newrt);
	//文本远程端口
	GetDlgItem(IDC_ST_PORT)->GetWindowRect(rt);
	newrt.top   =  parent_rt.top+100;
	newrt.bottom = newrt.top + rt.Height() ;
	newrt.left   = 20;
	newrt.right  = 20 + rt.Width() ;
	GetDlgItem(IDC_ST_PORT)->MoveWindow(newrt);

	//文本本地端口
	GetDlgItem(IDC_ST_PORT2)->GetWindowRect(rt);
	newrt.top   =  parent_rt.top+150;
	newrt.bottom = newrt.top + rt.Height() ;
	newrt.left   = 20;
	newrt.right  = 20 + rt.Width() ;
	GetDlgItem(IDC_ST_PORT2)->MoveWindow(newrt);

	//btn open
	m_link_net.GetWindowRect(rt);
	newrt.top   =   parent_rt.bottom -rt.Height() -20;
	newrt.bottom =  parent_rt.bottom -20 ;
	newrt.left   = parent_rt.Width()/2 - rt.Width()-10;
	newrt.right  = newrt.left  + rt.Width() ;
	m_link_net.MoveWindow(newrt);

	m_close_wind.GetWindowRect(rt);
	newrt.top   =  parent_rt.bottom -rt.Height() -20;
	newrt.bottom = parent_rt.bottom -20 ;
	newrt.left   = parent_rt.Width()/2 +10;
	newrt.right  = newrt.left  + rt.Width() ;
	m_close_wind.MoveWindow(newrt);


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
HBRUSH Net_setting::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO:  在此更改 DC 的任何特性
	if(nCtlColor == CTLCOLOR_STATIC  )
	{
		if (pWnd->GetDlgCtrlID() == IDC_ST_NET_TLE )
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


void Net_setting::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
}
CString Net_setting::get_ip_address()
{
		byte ip_arr[4];
		int ret;
		CString ipstr;
		ret = m_ip_input.GetAddress(ip_arr[0],ip_arr[1],ip_arr[2],ip_arr[3]);
		if (ret != 4)
		{
			MsgBox("提示","目标IP填写不完整",path+"messzgebox.bmp",path);
			m_ip_input.SetFocus();
			return "";
		}
		ipstr.Format(_T("%d.%d.%d.%d"),ip_arr[0],ip_arr[1],ip_arr[2],ip_arr[3]);
		return ipstr;
}
//获取对话框中的数值
bool Net_setting::get_int(CEdit * edit_ctrl, unsigned int min,unsigned int max, unsigned int &val,const CString & mess)
{
	CString tmp_str;
	edit_ctrl->GetWindowText(tmp_str);
	if (tmp_str.GetLength()>0)
	{
		unsigned int tmp_int = atoi(_T(tmp_str));
		if (tmp_int>=min && tmp_int<=max)
		{
			val = tmp_int;
			return true;
		}
		else
		{
			CString message;
			message.Format(_T("%s范围%d～%d."),mess,min,max);
		    MsgBox("错误",message,path+"messzgebox.bmp",path);
			//超出范围，将最大值写入
			message.Format(_T("%d"),max);
			edit_ctrl->SetWindowText(message);
			edit_ctrl->SetFocus();
			//设置编辑框中的内容为选中状态
			edit_ctrl->SetSel(tmp_str.GetLength());
		}
	}else
	{
		CString message;
		message.Format(_T("%s范围%d～%d."),mess,min,max);
	    MsgBox("错误",message,path+"messzgebox.bmp",path);
		message.Format(_T("%d"),max);
		edit_ctrl->SetWindowText(message);
		edit_ctrl->SetFocus();
	}
	return false;
}
int Net_setting::get_port_address()
{    
	unsigned int val;
	if (!get_int(&m_port_input,1,0xffff,val,_T("目标端口")))
	{
		return -1;
	}	
	return val;
}
int Net_setting::get_port_address(CEdit  *pedit)
{    
	unsigned int val;
	if (!get_int(pedit,1,0xffff,val,_T("目标端口")))
	{
		return -1;
	}	
	return val;
}
int Net_setting::net_link_init()
{

	//初始化网络环境  
	WSADATA wsa;  
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)  
	{  
		TRACE("WSAStartup failed\n");  
		return -1;  
	}  
	//建立一个UDP的socket  
	 m_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);  
	if (m_sock == INVALID_SOCKET)  
	{  
		TRACE("create socket failed\n");  
		return -1;  
	}  
	//绑定地址信息  
	sockaddr_in serverAddr;  
	serverAddr.sin_family = AF_INET;  
	serverAddr.sin_port = htons(m_r_port);  
	serverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);  

	bind(m_sock, (sockaddr*)&serverAddr, sizeof(sockaddr));  
	//关闭SOCKET连接  
	//closesocket(m_sock);  
	return 0;

}
//udp发送数据
int Net_setting::udp_send_data(byte *data,WORD len)
{
	int  ret;
	byte i=0;
	if ( (len == 0) ||(data == NULL))
	{
		return -1;
	}
	sockaddr_in dev_addrto;
	if ( (m_sock   == INVALID_SOCKET )|| (m_ip == "" ) || (m_port   == 0) )
	{
		MsgBox("错误","请先选择连接设备",path+"messzgebox.bmp",path);
		return -1;
	}
	dev_addrto.sin_family      =AF_INET;
	dev_addrto.sin_addr.s_addr =inet_addr(m_ip); 
	dev_addrto.sin_port        =htons(m_port);

	int nlen=sizeof(dev_addrto);
	int sendlen= 0;
	while (sendlen != len) 
	{
		ret=sendto(m_sock,(char *)data+sendlen,len-sendlen,0,(sockaddr*)&dev_addrto,nlen);
		if (ret > 0)
		{
		   sendlen += ret;
		}else if (ret <= 0 )
		{
			break;
		}
	}
	if (ret <= 0)
	{
	    MsgBox("错误","UDP发送失败",path+"messzgebox.bmp",path);
		return -1;
	}
	return 0;
}

VOID Net_setting::MakeCMDPKT(PKT *pkt,byte cmd,byte  *payload,byte paylen)
{
	if (pkt == NULL)
		return;
	pkt->header = FRAME_HEADER;
	pkt->length = 1 + paylen;
	pkt->cmd    = cmd;
	memcpy(pkt->payload,payload,paylen);
	pkt->payload[paylen] = FRAME_END;
}
bool Net_setting::send_cmd_whole_start_run(void)
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
	return (udp_send_data((byte*)&pkt,pkt.length +3)==0) ? true : false;

}
//整个专家停止
bool Net_setting::send_cmd_whole_stop_run(void)
{
	PKT pkt;
	byte payload[20] ={0};
	payload[0] = 0;
	MakeCMDPKT(&pkt, CMD_START_STOP, payload, 1); 
	return (udp_send_data((byte*)&pkt,pkt.length +3)==0) ? true : false;
}
//开始扫描
bool Net_setting::send_cmd_start_scan(void)
{
	PKT pkt;
	byte payload[20] ={0};
	payload[0] = 1;
	MakeCMDPKT(&pkt, CMD_DEG_SCAN, payload, 1); 
    return (udp_send_data((byte*)&pkt,pkt.length +3)==0) ? true : false;
}
//结束扫描
bool  Net_setting::send_cmd_stop_scan(void)
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
bool Net_setting::send_cmd_all_bsp_chk(void)
{
	PKT pkt;
	byte payload[20] ={0};
	MakeCMDPKT(&pkt, CMD_POWER_CHK, payload, 0); 
	return (udp_send_data((byte*)&pkt,pkt.length +3)==0) ? true : false;
}
//发送连接错误
bool  Net_setting::send_link_error(void)
{
	PKT pkt;
	byte payload[20] ={0};
	MakeCMDPKT(&pkt, CMD_POWER_LINK_ERROR_FD, payload, 0); 
	return (udp_send_data((byte*)&pkt,pkt.length +3)==0) ? true : false;

}
void Net_setting::handerdatapkt(PKT * pkt)
{

	CString str ="";
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
void Net_setting::ParselinkLine(PKT * pkt)
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
void Net_setting::OnTimer(UINT_PTR nIDEvent)
{
	static  byte m_stop_num =0;
	if (nIDEvent == 148 )
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
			udp_send_data((byte*)&pkt,pkt.length +3);
		}
	}
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnTimer(nIDEvent);
}


BOOL Net_setting::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	DrawBmp(path + "comsetting.bmp");
	return true;
	//return CDialogEx::OnEraseBkgnd(pDC);
}
void Net_setting::DrawBmp(CString strname)
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

void Net_setting::OnLButtonDown(UINT nFlags, CPoint point)
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
	Net_setting *dlg=(Net_setting*)pParam;
	int len =0,lenaddr =0;
	unsigned char ch =0;
	static int num =0;
	SOCKADDR_IN  from; 
	lenaddr =sizeof(from);
	byte Buf[NETBUFLEN];
	while(dlg->m_runing)
	{
		len = recvfrom(dlg->m_sock,(char*)Buf, NETBUFLEN, 0,(struct sockaddr*)&from, &lenaddr);

		// 接收数据  
		if (len <= 0)
		{	
			//char str[100]={0};
			//itoa(WSAGetLastError(),str,10);
			//TRACE(str);
			break;
		}
		if( len > sizeof(PKT))
		{
			len= sizeof(PKT);
		}
		if ( dlg->check_pkt_header( (PKT*)Buf,len) == true)
		{
			//解析正常数据
			PKT *pkt =new PKT;
			memcpy(pkt,Buf,len);
			::PostMessage(dlg->GetSafeHwnd(),NET_PKT_MSG,(WPARAM)pkt,0);
		}
	}//end while
	return 0;
}
bool Net_setting::check_pkt_header(PKT  *pkt,unsigned int pkt_len)
{
	unsigned char   *p  =(unsigned char*) pkt;
	if (FRAME_HEADER != pkt->header)  
		return false;
    if (pkt_len   != (pkt->length+3)) 
		return false;
    if( p[pkt_len-1] != FRAME_END)
		return false;
	return true;
}
void Net_setting::start_net_thread()
{
	if (m_pThread==NULL)
	{
		m_runing = true;
		m_pThread = AfxBeginThread(Serial_hander_thread, this); //启动线程
	}
}
void Net_setting::stop_net_thread()
{
	m_runing = false;
	m_pThread = NULL ;
}	
LONG Net_setting::serial_hander_data(WPARAM ch,LPARAM port)
{
	PKT *pkt =(PKT*)ch;
	handerdatapkt(pkt);
	delete pkt;
	return 0;
}