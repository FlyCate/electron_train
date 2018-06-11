// SettingCom.cpp : ʵ���ļ�
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
// SettingCom �Ի���

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
	//ON_MESSAGE(WM_COMM_RXCHAR,  &SettingCom::OnComm)  //��Ϣӳ��
	ON_MESSAGE(COMM_PKT_MSG,  &SettingCom::serial_hander_data)  //��Ϣӳ��
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// SettingCom ��Ϣ�������


BOOL SettingCom::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
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
	// �쳣: OCX ����ҳӦ���� FALSE
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


void SettingCom::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	DrawBmp(path + "comsetting.bmp");
	removechildwnd();
}

//ok����
void SettingCom::OnBnClickedBtnOkCom()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->ShowWindow(FALSE);
	if (parent->m_pemf_wnd != NULL)
	{
		//parent->m_pictype =1;
		//parent->m_pemf_wnd->setEmfType(parent->m_pictype);
		//send_cmd_all_bsp_chk();
	}

}

//com��ѡ��ı�
void SettingCom::OnCbnSelchangeCbCom()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_cb_comsel.GetLBText(m_cb_comsel.GetCurSel(),str);
	if (str.GetLength()>3)
	{
		str = str.Mid(3);
		m_com_index = atoi(str.GetString())	;
	}

}

//������ѡ��ı�
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
	// TODO:  �ڴ˸��� DC ���κ�����
	if(nCtlColor == CTLCOLOR_STATIC  )
	{
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_MAINITEM )
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


int SettingCom::removechildwnd(void)
{

	CRect rt,newrt,parent_rt;
	this->GetClientRect(parent_rt);
	GetDlgItem(IDC_STATIC_MAINITEM)->GetWindowRect(rt);

	//������
	newrt.top   =  parent_rt.top+5;
	newrt.bottom = rt.Height()+5;
	newrt.left   = parent_rt.Width()/2 -rt.Width()/2;
	newrt.right  = newrt.left+ rt.Width();
	GetDlgItem(IDC_STATIC_MAINITEM)->MoveWindow(newrt);

	//�ı�com
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

//�򿪴��ڰ���
void SettingCom::OnBnClickedCheckOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_isopen = !m_isopen;
	if(m_isopen)
	{
		if(m_com.OpenCOM(m_com_index,m_bund,0))
		//if(m_com.InitPort(this,m_com_index,m_bund))
		{
			//m_com.StartMonitoring();
			//���������߳�
			start_serial_thread();
			m_btn_open.SetCheck(true);
			m_cb_bundsel.EnableWindow(FALSE);
			m_cb_comsel.EnableWindow(FALSE);
			/*this->ShowWindow(false);*/
		}else
		{
			m_cb_bundsel.EnableWindow(TRUE);
			m_cb_comsel.EnableWindow(TRUE);
			
			 MsgBox("����","û�з��ִ˴��ڻ��߱�ռ��",path+"messzgebox.bmp",path);
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
//���ڽ��մ�����
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
		{//У����ͷ
			if (Bufcom[0]  != FRAME_HEADER)
			{
				num =0;
			}
		}else if (num > 2)
		{   //������α��
			if ((Bufcom[1]+3)  == num)
			{
				if (Bufcom[num-1] != FRAME_END)
				{
					num =0;
				}else
				{
					//������������
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
//���ڷ���
bool  SettingCom::serialsenddata(byte * p,int len)
{
	if (p == NULL || len <=  0)
	{
		return false;
	}
	if (!m_isopen)
	{ 
		MsgBox("����","���ȴ򿪴���",path+"messzgebox.bmp",path);
		return false;
	}
//	m_com.WriteToPort(p,  len);
	m_com.Write((char*)p, len);
	return true;
}
//���ڷ���
bool  SettingCom::serialsenddata(byte * p,int len,bool ischk,CString inf,DWORD ms)
{
	if (p == NULL || len <=  0 )
	{
		return false;
	}
	if (!m_isopen)
	{ 
		MsgBox("����","���ȴ򿪴���",path+"messzgebox.bmp",path);
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
//����ר������
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
	return serialsenddata((byte*)&pkt, pkt.length +3 ,true,"���� ����ר��ϵͳ���� ��ʱ",3000);

}
//����ר������
bool SettingCom::send_cmd_whole_stop_run(void)
{
	PKT pkt;
	byte payload[20] ={0};
	payload[0] = 0;
	MakeCMDPKT(&pkt, CMD_START_STOP, payload, 1); 

    return serialsenddata((byte*)&pkt, pkt.length +3 ,true,"���� ����ר��ϵͳֹͣ ��ʱ",3000);

}
//��ʼɨ��
bool SettingCom::send_cmd_start_scan(void)
{
	PKT pkt;
	byte payload[20] ={0};
	payload[0] = 1;
	MakeCMDPKT(&pkt, CMD_DEG_SCAN, payload, 1); 
   return serialsenddata((byte*)&pkt, pkt.length +3 ,true,"���� ��ʼɨ�� ��ʱ",3000);

}
//����ɨ��
bool  SettingCom::send_cmd_stop_scan(void)
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
bool SettingCom::send_cmd_all_bsp_chk(void)
{
	PKT pkt;
	byte payload[20] ={0};
	MakeCMDPKT(&pkt, CMD_POWER_CHK, payload, 0); 
	return serialsenddata((byte*)&pkt, pkt.length +3 ,true,"���� ���вɼ����ϵ��� ��ʱ",3000);
}
//�������Ӵ���
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
	m_send_flag = false;  //��շ��ͱ��
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

void SettingCom::OnTimer(UINT_PTR nIDEvent)
{
	static  byte m_stop_num =0;
	if (nIDEvent == m_tm_id)
	{
		if (m_send_flag == true)
		{    
		     KillTimer(nIDEvent);

			 MsgBox("��ʾ",m_tmoutinf,path+"messzgebox.bmp",path);
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnTimer(nIDEvent);
}


BOOL SettingCom::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	DrawBmp(path + "comsetting.bmp");
	return true;
	//return CDialogEx::OnEraseBkgnd(pDC);
}


void SettingCom::OnLButtonDown(UINT nFlags, CPoint point)
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
				{//У����ͷ
					if (Bufcom[0]  != FRAME_HEADER)
					{
						num =0;
					}
				}else if (num > 2)
				{   //������α��
					if ((Bufcom[1]+3)  == num)
					{
						if (Bufcom[num-1] != FRAME_END)
						{
							num =0;
						}else
						{
							//������������
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
		m_pThread = AfxBeginThread(Serial_hander_thread, this); //�����߳�
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