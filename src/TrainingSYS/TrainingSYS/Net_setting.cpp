// Net_setting.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TrainingSYS.h"
#include "Net_setting.h"
#include "afxdialogex.h"
#include <winsock2.h>  
#include "MyMessagebox.h"
#include "ts_emf_wnd.h"
#define PICTURE_NET_LEVEL  "\\res\\picture_com\\" 
// Net_setting �Ի���
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
	ON_MESSAGE(NET_PKT_MSG,  &Net_setting::serial_hander_data)  //��Ϣӳ��
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	//	ON_WM_MBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// Net_setting ��Ϣ�������

//����Ի�����ʾ�ر�
void Net_setting::OnBnClickedBtnNetClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		this->ShowWindow(FALSE);
}

//�������Ӱ���
void Net_setting::OnBnClickedBtnNetLink()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
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
	// �쳣: OCX ����ҳӦ���� FALSE
}
int Net_setting::removechildwnd(void)
{
	CRect rt,newrt,parent_rt;
	this->GetClientRect(parent_rt);

	//������
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
	//���ض˿�����
	m_r_port_input.GetWindowRect(rt);
	newrt.top   =  parent_rt.top+150;
	newrt.bottom = newrt.top + rt.Height() ;
	newrt.left   = 100;
	newrt.right  = newrt.left  + rt.Width() ;
	m_r_port_input.MoveWindow(newrt);


	//�ı�IP
	GetDlgItem(IDC_ST_IP)->GetWindowRect(rt);
	newrt.top   =  parent_rt.top+50;
	newrt.bottom = newrt.top + rt.Height() ;
	newrt.left   = 20;
	newrt.right  = newrt.left  + rt.Width() ;
	GetDlgItem(IDC_ST_IP)->MoveWindow(newrt);
	//�ı�Զ�̶˿�
	GetDlgItem(IDC_ST_PORT)->GetWindowRect(rt);
	newrt.top   =  parent_rt.top+100;
	newrt.bottom = newrt.top + rt.Height() ;
	newrt.left   = 20;
	newrt.right  = 20 + rt.Width() ;
	GetDlgItem(IDC_ST_PORT)->MoveWindow(newrt);

	//�ı����ض˿�
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
	// TODO:  �ڴ˸��� DC ���κ�����
	if(nCtlColor == CTLCOLOR_STATIC  )
	{
		if (pWnd->GetDlgCtrlID() == IDC_ST_NET_TLE )
		{
			pDC->SetTextColor(RGB(255,255,255));
		}else
		{
			pDC->SetTextColor(RGB(0,0,0));
		}
		pDC->SetBkMode(TRANSPARENT);//���ñ���͸��
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	} 
	return hbr;
}


void Net_setting::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}
CString Net_setting::get_ip_address()
{
		byte ip_arr[4];
		int ret;
		CString ipstr;
		ret = m_ip_input.GetAddress(ip_arr[0],ip_arr[1],ip_arr[2],ip_arr[3]);
		if (ret != 4)
		{
			MsgBox("��ʾ","Ŀ��IP��д������",path+"messzgebox.bmp",path);
			m_ip_input.SetFocus();
			return "";
		}
		ipstr.Format(_T("%d.%d.%d.%d"),ip_arr[0],ip_arr[1],ip_arr[2],ip_arr[3]);
		return ipstr;
}
//��ȡ�Ի����е���ֵ
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
			message.Format(_T("%s��Χ%d��%d."),mess,min,max);
		    MsgBox("����",message,path+"messzgebox.bmp",path);
			//������Χ�������ֵд��
			message.Format(_T("%d"),max);
			edit_ctrl->SetWindowText(message);
			edit_ctrl->SetFocus();
			//���ñ༭���е�����Ϊѡ��״̬
			edit_ctrl->SetSel(tmp_str.GetLength());
		}
	}else
	{
		CString message;
		message.Format(_T("%s��Χ%d��%d."),mess,min,max);
	    MsgBox("����",message,path+"messzgebox.bmp",path);
		message.Format(_T("%d"),max);
		edit_ctrl->SetWindowText(message);
		edit_ctrl->SetFocus();
	}
	return false;
}
int Net_setting::get_port_address()
{    
	unsigned int val;
	if (!get_int(&m_port_input,1,0xffff,val,_T("Ŀ��˿�")))
	{
		return -1;
	}	
	return val;
}
int Net_setting::get_port_address(CEdit  *pedit)
{    
	unsigned int val;
	if (!get_int(pedit,1,0xffff,val,_T("Ŀ��˿�")))
	{
		return -1;
	}	
	return val;
}
int Net_setting::net_link_init()
{

	//��ʼ�����绷��  
	WSADATA wsa;  
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)  
	{  
		TRACE("WSAStartup failed\n");  
		return -1;  
	}  
	//����һ��UDP��socket  
	 m_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);  
	if (m_sock == INVALID_SOCKET)  
	{  
		TRACE("create socket failed\n");  
		return -1;  
	}  
	//�󶨵�ַ��Ϣ  
	sockaddr_in serverAddr;  
	serverAddr.sin_family = AF_INET;  
	serverAddr.sin_port = htons(m_r_port);  
	serverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);  

	bind(m_sock, (sockaddr*)&serverAddr, sizeof(sockaddr));  
	//�ر�SOCKET����  
	//closesocket(m_sock);  
	return 0;

}
//udp��������
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
		MsgBox("����","����ѡ�������豸",path+"messzgebox.bmp",path);
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
	    MsgBox("����","UDP����ʧ��",path+"messzgebox.bmp",path);
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
//����ר��ֹͣ
bool Net_setting::send_cmd_whole_stop_run(void)
{
	PKT pkt;
	byte payload[20] ={0};
	payload[0] = 0;
	MakeCMDPKT(&pkt, CMD_START_STOP, payload, 1); 
	return (udp_send_data((byte*)&pkt,pkt.length +3)==0) ? true : false;
}
//��ʼɨ��
bool Net_setting::send_cmd_start_scan(void)
{
	PKT pkt;
	byte payload[20] ={0};
	payload[0] = 1;
	MakeCMDPKT(&pkt, CMD_DEG_SCAN, payload, 1); 
    return (udp_send_data((byte*)&pkt,pkt.length +3)==0) ? true : false;
}
//����ɨ��
bool  Net_setting::send_cmd_stop_scan(void)
{   
	SetTimer(148,200,NULL);
	return true;
	/*
	PKT pkt;
	byte payload[20] ={0};
	payload[0] = 0;
	MakeCMDPKT(&pkt, CMD_END_SCAN, payload, 1); 
	return serialsenddata((byte*)&pkt, pkt.length +3 ,true,"���� ����ɨ�� ��ʱ",3000);
	*/
}

//���вɼ����ϵ���
bool Net_setting::send_cmd_all_bsp_chk(void)
{
	PKT pkt;
	byte payload[20] ={0};
	MakeCMDPKT(&pkt, CMD_POWER_CHK, payload, 0); 
	return (udp_send_data((byte*)&pkt,pkt.length +3)==0) ? true : false;
}
//�������Ӵ���
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
			str ="ר��ϵͳ��ʼ���гɹ�";
		}else
		{
			str ="ר��ϵͳֹͣ���гɹ�";
		}

	    MsgBox("��Ϣ��ʾ",str,path+"messzgebox.bmp",path);
		break;
	case CMD_DEG_SCAN_FD:
		if (pkt->payload[0])
		{
			str ="��ʼɨ�����гɹ�";
		}else
		{
			str ="����ɨ�����гɹ�";
		}
		break;
	case CMD_POWER_CHK_FD:
		if (pkt->length == 1)
		{
			str ="���вɼ����ϵ繤���ɹ�";
		}else
		{  
			CString inf;
			if (pkt->length >= 2)
			{
				inf.Format("�ɼ���\"%d\" ",pkt->payload[0]);
				str += inf;
			}
			if (pkt->length >= 3)
			{
				inf.Format("�ɼ���\"%d\" ",pkt->payload[1]);
				str += inf;
			}
			if (pkt->length >= 4)
			{
				inf.Format("�ɼ���\"%d\" ",pkt->payload[2]);
				str += inf;
			}
			if (pkt->length >= 4)
			{
				inf.Format("�ɼ���\"%d\" ",pkt->payload[3]);
				str += inf;
			}
			if (pkt->length >= 6)
			{
				inf.Format("�ɼ���\"%d\" ",pkt->payload[4]);
				str += inf;
			}
			str += "û���ϵ�����쳣";
		}
		 MsgBox("��Ϣ��ʾ",str,path+"messzgebox.bmp",path);
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
	mode =p->m_pemf_wnd->getmode();//1�ֶ�ģʽ 0 �Զ�ģʽ
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnTimer(nIDEvent);
}


BOOL Net_setting::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	bitmap.Attach(hbmp); //����λͼ����
	CDC *pDC = GetDC();
	CDC memdc;//�����ڴ滭��
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnLButtonDown(nFlags, point);
	PostMessage(WM_NCLBUTTONDOWN,
		HTCAPTION,
		MAKELPARAM(point.x, point.y));
}
static UINT Serial_hander_thread(LPVOID pParam);//�̺߳�������

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

		// ��������  
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
			//������������
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
		m_pThread = AfxBeginThread(Serial_hander_thread, this); //�����߳�
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