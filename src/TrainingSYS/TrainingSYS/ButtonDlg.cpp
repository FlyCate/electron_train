// ButtonDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TrainingSYS.h"
#include "TrainingSYSDlg.h"
#include "ButtonDlg.h"
#include "afxdialogex.h"
#include "ts_emf_wnd.h"


int secondMenu[10] = {7, 7, 6, 7, 7, 5, 8, 7, 1, 1};
/*char * titleList[8][8] = {
	{"��Դϵͳ","ͨ��������","�����ɼ���ϵͳ","����������ϵͳ","�豸������ϵͳ","���Ӽ���������","�豸���ϱ�",""},
	{"ϵͳͼ���֪ʶ","�����ɼ���ϵͳ","����������ϵͳ","�豸������ϵͳ","��Դϵͳ","RS485ͨ����ϵͳ","ϵͳͼ���",""},
	{"ʩ��ͼ���֪ʶ","�����ɼ���ϵͳ","����������ϵͳ","�豸������ϵͳ","��Դϵͳ","RS485ͨ����ϵͳ","ʩ��ͼ���",""},
	{"�豸���֪ʶ","�����ɼ���ϵͳ","����������ϵͳ","�豸������ϵͳ","��Դϵͳ","ͨ��ģ����","��ⱨ��",""},
	{"ʩ������֪ʶ","�����ɼ���ϵͳ","����������ϵͳ","�豸������ϵͳ","��Դϵͳ","RS485ͨ����ϵͳ","ʩ������",""},
	{"�̾���ͨ�ż���","ZigBee����ͨ��","RS485����ͨ��","433MHz����ͨ��","WiFi����ͨ��","����ͨ�ż���","�ƶ�ͨ�ż���",""},
	{"������滮���","����滮�����","����ͨ�ų������","HTTP�����������","�����ɼ���ϵͳ","����������ϵͳ","�豸������ϵͳ","ϵͳ���������"},
	{"����滮�����","����滮�����","HTTP�����������","�����ɼ���ϵͳ","�ҾӰ�����ϵͳ","�豸������ϵͳ","ϵͳ���������",""}
};*/

char * titleList[10][9] = {
	{"��Դϵͳ","ͨ��������","�����ɼ���ϵͳ","����������ϵͳ","�豸������ϵͳ","���Ӽ���������","",""},
	{"ϵͳͼ���֪ʶ","�����ɼ���ϵͳ","����������ϵͳ","�豸������ϵͳ","��Դϵͳ","RS485ͨ����ϵͳ","ϵͳͼ���",""},
	{"ʩ��ͼ���֪ʶ","�����ɼ���ϵͳ","����������ϵͳ","�豸������ϵͳ","��Դϵͳ","RS485ͨ����ϵͳ","",""},
	{"�豸���֪ʶ","�����ɼ���ϵͳ","����������ϵͳ","�豸������ϵͳ","��Դϵͳ","ͨ��ģ����","",""},
	{"ʩ������֪ʶ","�����ɼ���ϵͳ","����������ϵͳ","�豸������ϵͳ","��Դϵͳ","RS485ͨ����ϵͳ","",""},
	{"�̾���ͨ�ż���","ZigBee����ͨ��","RS485����ͨ��","433MHz����ͨ��","","","",""},
	{"������滮���","����滮�����","����ͨ�ų������","HTTP�����������","�����ɼ���ϵͳ","����������ϵͳ","�豸������ϵͳ",""},
	{"����滮�����","����滮�����","HTTP�����������","�����ɼ���ϵͳ","�ҾӰ�����ϵͳ","�豸������ϵͳ","",""},
	{"ϵͳ���","ƽ̨���","ʹ�÷���","ͨ��ģ����","�����ɼ��豸���","���������豸���","�����豸���","��Դ�豸���","�����ն˼��"},
	{"��Ŀ�滮����֪ʶ","���ܼҾ���Ŀ�滮","����ũҵ��Ŀ�滮","����������Ŀ�滮","����������Ŀ�滮","","",""}
};

char * itoaa(int num);

// ButtonDlg �Ի���

IMPLEMENT_DYNAMIC(ButtonDlg, CDialogEx)

ButtonDlg::ButtonDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ButtonDlg::IDD, pParent)
{
	InitializeCriticalSection(&g_criSection);  //ʹ��ǰ�����ʼ��
	parent = (CTrainingSYSDlg *) pParent;
	m_picPath = parent->m_path;
	m_picPath += "\\res\\button\\";
	m_startrun = false;

	for (int i = 1; i <= 16; i++)
	{
		pMenuBtn pBtn = new MenuBtn;

		pBtn->m_MenuBtnNum = i;
		pBtn->m_BtnNum.Format("%d", i);
		pBtn->m_BtnUpFileName.Format("%sDown.bmp", pBtn->m_BtnNum);
		pBtn->m_BtnDownFileName.Format("%sUp.bmp", pBtn->m_BtnNum);
		pBtn->m_BtnSetFileName.Format("%sSet.bmp", pBtn->m_BtnNum);

		if (i <= 10)
		{
			for (int m = 1; m <= 9; m++)
			{
				pMenuBtn pBtnSecond = new MenuBtn;

				pBtnSecond->m_MenuBtnNum = m;
				pBtnSecond->m_BtnNum.Format("%d-%d", i, m);
				pBtnSecond->m_BtnUpFileName.Format("%sDown.bmp", pBtnSecond->m_BtnNum);
				pBtnSecond->m_BtnDownFileName.Format("%sUp.bmp", pBtnSecond->m_BtnNum);
				pBtnSecond->m_BtnSetFileName.Format("%sSet.bmp", pBtnSecond->m_BtnNum);

				for (int n = 1; n <= 9; n++)
				{
					pMenuBtn pBtnThird = new MenuBtn;

					pBtnThird->m_MenuBtnNum = m;
					pBtnThird->m_BtnNum.Format("%d-%d-%d", i, m, n);
					pBtnThird->m_BtnUpFileName.Format("%sDown.bmp", pBtnThird->m_BtnNum);
					pBtnThird->m_BtnDownFileName.Format("%sUp.bmp", pBtnThird->m_BtnNum);
					pBtnThird->m_BtnSetFileName.Format("%sSet.bmp", pBtnThird->m_BtnNum);

					pBtnSecond->m_MenuBtnList.push_back(pBtnThird);
				}

				pBtn->m_MenuBtnList.push_back(pBtnSecond);
			}
		}

		m_MenuBtnList.push_back(pBtn);
	}
}

ButtonDlg::~ButtonDlg()
{
	DeleteCriticalSection(&g_criSection);
}

void ButtonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TITLE, m_title);
	DDX_Control(pDX, IDC_BTN_SYSTEM_INTRODUCTION, m_system);
}


BEGIN_MESSAGE_MAP(ButtonDlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_INFO_CAP_RUN, &ButtonDlg::OnBnClickedBtnInfoCapRun)
	ON_BN_CLICKED(IDC_BTN_ALARM_RUN, &ButtonDlg::OnBnClickedBtnAlarmRun)
	ON_BN_CLICKED(IDC_BTN_CONSTRUCTION_COMMISSIONING, &ButtonDlg::OnBnClickedBtnConstructionCommissioning)
	ON_BN_CLICKED(IDC_BUTTON_SWITCH_PIC, &ButtonDlg::OnBnClickedButtonSwitchPic)
	ON_BN_CLICKED(IDC_BUTTON_START_CHECK, &ButtonDlg::OnBnClickedButtonStartCheck)
END_MESSAGE_MAP()

void ButtonDlg::setBtmBmp(int btnID, int bmpID)
{
	HINSTANCE hInstance;
	HBITMAP hBitmap;
	hInstance   =   ::AfxGetInstanceHandle();
	hBitmap =  ::LoadBitmap(hInstance, MAKEINTRESOURCE(bmpID) );
	((CButton *)GetDlgItem(btnID))->SetBitmap(hBitmap);
}

void ButtonDlg::setBtmBmp(int btnID, CString strFileName)
{
	HBITMAP bitmap;
	CString str = m_picPath;
	str += strFileName;

	bitmap=(HBITMAP)LoadImage(AfxGetInstanceHandle(),str,IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	((CButton *)GetDlgItem(btnID))->SetBitmap(bitmap);
}

void ButtonDlg::BtnInit()
{
	//��ʼ����Ϣ
	m_firstRangeBtnNum = 1;
	m_secondRangeBtnNum = -1;
	m_thirdRangeBtnNum = -1;

	//���ñ���ͼƬ
	CBitmap   bmpBackground;   
	bmpBackground.LoadBitmap(IDB_BACKGURAND);

	BITMAP   bitmap;   
	bmpBackground.GetBitmap(&bitmap);

	//���ð�ťλ��
	CRect rect;
	GetWindowRect(&rect);
	int width = 335;//bitmap.bmWidth;
	int height = rect.bottom - rect.top;
	SetWindowPos(NULL, rect.left, rect.top, width, 1000, SWP_NOZORDER|SWP_NOMOVE);
	int edgeSize = 30;
	int edgeSize2 = 30;
	int intervalSize = 5;
	int topSize = 131;

	int buttonwidth = 119;
	int buttonheight = 29;
	int button2width = 74;
	int button2height = 74;

	//����������
	GetDlgItem(IDC_BTN_SYSTEM_INTRODUCTION)->MoveWindow(edgeSize, topSize, buttonwidth, buttonheight);
	GetDlgItem(IDC_BTN_SYSTEM_DESIGN_REQUIREMENTS)->MoveWindow(width-edgeSize-buttonwidth, topSize, buttonwidth, buttonheight);
	topSize += 34 + intervalSize;

	//����
	GetDlgItem(IDC_STATIC)->MoveWindow(edgeSize, topSize, width-edgeSize*2, buttonheight);
	topSize += 34 + intervalSize;

	//����˸�
	GetDlgItem(IDC_BTN_DEVICE_SELECT)->MoveWindow(edgeSize, topSize, buttonwidth, buttonheight);
	GetDlgItem(IDC_BTN_SYSTEM_DESIGN)->MoveWindow(width-edgeSize-buttonwidth, topSize, buttonwidth, buttonheight);
	topSize += 34 + intervalSize;
	GetDlgItem(IDC_BTN_CONSTRUCTING_DESIGN)->MoveWindow(edgeSize, topSize, buttonwidth, buttonheight);
	GetDlgItem(IDC_BTN_EQUIPMENT_INSPECTION)->MoveWindow(width-edgeSize-buttonwidth, topSize, buttonwidth, buttonheight);
	topSize += 34 + intervalSize;
	GetDlgItem(IDC_BTN_CONSTRUCTION_COMMISSIONING)->MoveWindow(edgeSize, topSize, buttonwidth, buttonheight);
	GetDlgItem(IDC_BTN_COMMUNICATIONS_NETWORK)->MoveWindow(width-edgeSize-buttonwidth, topSize, buttonwidth, buttonheight);
	topSize += 34 + intervalSize;
	GetDlgItem(IDC_BTN_TERMINAL_SOFTWARE)->MoveWindow(edgeSize, topSize, buttonwidth, buttonheight);
	GetDlgItem(IDC_BTN_APP_DESIGN)->MoveWindow(width-edgeSize-buttonwidth, topSize, buttonwidth, buttonheight);
	topSize += 34 + intervalSize;

	//����
	GetDlgItem(IDC_STATIC_TITLE)->MoveWindow(edgeSize, topSize, width-edgeSize*2, buttonheight);
	topSize += 34 + intervalSize;

 	//�м�Ÿ�
 	GetDlgItem(IDC_BTN_ONE)->MoveWindow(edgeSize2, topSize, button2width, button2height);
 	GetDlgItem(IDC_BTN_TWO)->MoveWindow(edgeSize2+button2width+(width-2*(button2width+edgeSize2)-button2width)/2, topSize, button2width, button2height);
 	GetDlgItem(IDC_BTN_THREE)->MoveWindow(width-edgeSize2-button2width, topSize, button2width, button2height);
	topSize += button2width + (width-2*(button2width+edgeSize2)-button2width)/2;
 	GetDlgItem(IDC_BTN_FOUR)->MoveWindow(edgeSize2, topSize, button2width, button2height);
 	GetDlgItem(IDC_BTN_FIVE)->MoveWindow(edgeSize2+button2width+(width-2*(button2width+edgeSize2)-button2width)/2, topSize, button2width, button2height);
 	GetDlgItem(IDC_BTN_SIX)->MoveWindow(width-edgeSize2-button2width, topSize, button2width, button2height);
	topSize += button2width + (width-2*(button2width+edgeSize2)-button2width)/2;
 	GetDlgItem(IDC_BTN_SEVEN)->MoveWindow(edgeSize2, topSize, button2width, button2height);
 	GetDlgItem(IDC_BTN_EIGHT)->MoveWindow(edgeSize2+button2width+(width-2*(button2width+edgeSize2)-button2width)/2, topSize, button2width, button2height);
 	GetDlgItem(IDC_BTN_NINE)->MoveWindow(width-edgeSize2-button2width, topSize, button2width, button2height);
	topSize += button2width + (width-2*(button2width+edgeSize2)-button2width)/2;
 
 	//����������
 	GetDlgItem(IDC_BTN_INFO_CAP_RUN)->MoveWindow(edgeSize, topSize, buttonwidth, buttonheight);
	GetDlgItem(IDC_BUTTON_SWITCH_PIC)->MoveWindow(width-edgeSize-buttonwidth, topSize, buttonwidth, buttonheight);
	topSize += 34 + intervalSize;
 	GetDlgItem(IDC_BUTTON_START_CHECK)->MoveWindow(edgeSize, topSize, buttonwidth, buttonheight);
	GetDlgItem(IDC_BTN_ALARM_RUN)->MoveWindow(width-edgeSize-buttonwidth, topSize, buttonwidth, buttonheight);

	//��ʼ����ťͼ��
	Btn1BmpInit();
	setBtmBmp(IDC_BTN_DEVICE_SELECT,  m_MenuBtnList[0]->m_BtnSetFileName);
	Btn2BmpInit(m_firstRangeBtnNum);
	Btn3BmpInit();

	SetFirstRangeNum(m_firstRangeBtnNum);
}

BOOL ButtonDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_font.CreatePointFont(140,"����");//����15�����壬�����п�
	BtnInit();

	m_startrun = false;
	m_startCheck = false;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

int ButtonDlg::SwitchBtn(HWND btnHwnd)
{
	//һ���˵� ����
	if (btnHwnd == GetDlgItem(IDC_BTN_SYSTEM_INTRODUCTION)->GetSafeHwnd()) return 1;
	if (btnHwnd == GetDlgItem(IDC_BTN_SYSTEM_DESIGN_REQUIREMENTS)->GetSafeHwnd()) return 2;

	//һ���˵��в�
	if (btnHwnd == GetDlgItem(IDC_BTN_DEVICE_SELECT)->GetSafeHwnd()) return 3;
	if (btnHwnd == GetDlgItem(IDC_BTN_SYSTEM_DESIGN)->GetSafeHwnd()) return 4;
	if (btnHwnd == GetDlgItem(IDC_BTN_CONSTRUCTING_DESIGN)->GetSafeHwnd()) return 5;
	if (btnHwnd == GetDlgItem(IDC_BTN_EQUIPMENT_INSPECTION)->GetSafeHwnd()) return 6;
	if (btnHwnd == GetDlgItem(IDC_BTN_CONSTRUCTION_COMMISSIONING)->GetSafeHwnd()) return 7;
	if (btnHwnd == GetDlgItem(IDC_BTN_COMMUNICATIONS_NETWORK)->GetSafeHwnd()) return 8;
	if (btnHwnd == GetDlgItem(IDC_BTN_TERMINAL_SOFTWARE)->GetSafeHwnd()) return 9;
	if (btnHwnd == GetDlgItem(IDC_BTN_APP_DESIGN)->GetSafeHwnd()) return 10;

	//�����˵� �����˵�
	if (btnHwnd == GetDlgItem(IDC_BTN_ONE)->GetSafeHwnd()) return 11;
	if (btnHwnd == GetDlgItem(IDC_BTN_TWO)->GetSafeHwnd()) return 12;
	if (btnHwnd == GetDlgItem(IDC_BTN_THREE)->GetSafeHwnd()) return 13;
	if (btnHwnd == GetDlgItem(IDC_BTN_FOUR)->GetSafeHwnd()) return 14;
	if (btnHwnd == GetDlgItem(IDC_BTN_FIVE)->GetSafeHwnd()) return 15;
	if (btnHwnd == GetDlgItem(IDC_BTN_SIX)->GetSafeHwnd()) return 16;
	if (btnHwnd == GetDlgItem(IDC_BTN_SEVEN)->GetSafeHwnd()) return 17;
	if (btnHwnd == GetDlgItem(IDC_BTN_EIGHT)->GetSafeHwnd()) return 18;
	if (btnHwnd == GetDlgItem(IDC_BTN_NINE)->GetSafeHwnd()) return 19;

	//�ļ��˵�
	if (btnHwnd == GetDlgItem(IDC_BTN_INFO_CAP_RUN)->GetSafeHwnd()) return 20;
	if (btnHwnd == GetDlgItem(IDC_BTN_ALARM_RUN)->GetSafeHwnd()) return 21;
	if (btnHwnd == GetDlgItem(IDC_BUTTON_SWITCH_PIC)->GetSafeHwnd()) return 22;
	if (btnHwnd == GetDlgItem(IDC_BUTTON_START_CHECK)->GetSafeHwnd()) return 23;

	return -1;
}

void ButtonDlg::Btn1BmpInit()
{
	setBtmBmp(IDC_BTN_SYSTEM_INTRODUCTION, m_MenuBtnList[8]->m_BtnUpFileName);
	setBtmBmp(IDC_BTN_SYSTEM_DESIGN_REQUIREMENTS, m_MenuBtnList[9]->m_BtnUpFileName);

	//dzw 2017/3/25 change m_MenuBtnList[0]->m_BtnUpFileName to m_MenuBtnList[1]->m_BtnUpFileName
	setBtmBmp(IDC_BTN_DEVICE_SELECT,  m_MenuBtnList[0]->m_BtnUpFileName);
	setBtmBmp(IDC_BTN_SYSTEM_DESIGN,  m_MenuBtnList[1]->m_BtnUpFileName);
	setBtmBmp(IDC_BTN_CONSTRUCTING_DESIGN,  m_MenuBtnList[2]->m_BtnUpFileName);
	setBtmBmp(IDC_BTN_EQUIPMENT_INSPECTION,  m_MenuBtnList[3]->m_BtnUpFileName);
	setBtmBmp(IDC_BTN_CONSTRUCTION_COMMISSIONING,  m_MenuBtnList[4]->m_BtnUpFileName);
	setBtmBmp(IDC_BTN_COMMUNICATIONS_NETWORK,  m_MenuBtnList[5]->m_BtnUpFileName);
	setBtmBmp(IDC_BTN_TERMINAL_SOFTWARE,  m_MenuBtnList[6]->m_BtnUpFileName);
	setBtmBmp(IDC_BTN_APP_DESIGN,  m_MenuBtnList[7]->m_BtnUpFileName);
}

void ButtonDlg::Btn2BmpInit(int btn)
{
	for (int i = 0; i < 9; i++)
	{
		setBtmBmp(IDC_BTN_ONE + i, m_MenuBtnList[btn-1]->m_MenuBtnList[i]->m_BtnUpFileName);
	}
}

void ButtonDlg::Btn2BmpDown(int btn1, int btn2)
{
	setBtmBmp(IDC_BTN_ONE + btn2 - 1, m_MenuBtnList[btn1-1]->m_MenuBtnList[btn2 - 1]->m_BtnDownFileName);
}

void ButtonDlg::Btn2BmpSet(int btn1, int btn2)
{
	Btn2BmpInit(btn1);
	setBtmBmp(IDC_BTN_ONE + btn2 - 1, m_MenuBtnList[btn1-1]->m_MenuBtnList[btn2 - 1]->m_BtnSetFileName);
}

void ButtonDlg::Btn23BmpInit(int btn1, int btn2)
{
	for (int i = 0; i < 9; i++)
	{
		setBtmBmp(IDC_BTN_ONE + i, m_MenuBtnList[btn1-1]->m_MenuBtnList[btn2 - 1]->m_MenuBtnList[i]->m_BtnUpFileName);
	}
}

void ButtonDlg::Btn23BmpDown(int btn1, int btn2, int btn3)
{
	setBtmBmp(IDC_BTN_ONE + btn3 - 1, m_MenuBtnList[btn1-1]->m_MenuBtnList[btn2 - 1]->m_MenuBtnList[btn3 - 1]->m_BtnDownFileName);
}

void ButtonDlg::Btn23BmpSet(int btn1, int btn2, int btn3)
{
	Btn23BmpInit(btn1, btn2);
	setBtmBmp(IDC_BTN_ONE + btn3 - 1, m_MenuBtnList[btn1-1]->m_MenuBtnList[btn2 - 1]->m_MenuBtnList[btn3 - 1]->m_BtnSetFileName);
}

void ButtonDlg::Btn3BmpInit()
{
	setBtmBmp(IDC_BTN_INFO_CAP_RUN, m_MenuBtnList[10]->m_BtnUpFileName);
	setBtmBmp(IDC_BTN_ALARM_RUN, m_MenuBtnList[11]->m_BtnUpFileName);
	setBtmBmp(IDC_BUTTON_SWITCH_PIC, m_MenuBtnList[13]->m_BtnUpFileName);
	setBtmBmp(IDC_BUTTON_START_CHECK, m_MenuBtnList[14]->m_BtnUpFileName);
}

//����һ���˵���ֵ
void ButtonDlg::SetFirstRangeNum(int btn)
{
	CString str = "";
	m_firstRangeBtnNum = btn;
	m_secondRangeBtnNum = -1;
	m_thirdRangeBtnNum = -1;

	switch (btn)
	{
		case 1: str = "�豸ԭ����ѡ��"; break;
		case 2: str = "ϵͳͼ���"; break;
		case 3: str = "ʩ��ͼ���"; break;
		case 4: str = "�豸ԭ������"; break;
		case 5: str = "ʩ������"; break;
		case 6: str = "ͨ��������"; break;
		case 7: str = "�ն�������"; break;
		case 8: str = "�ֻ�APP������"; break;
		case 9: str = "ϵͳ���"; break;
		case 10: str = "�滮������"; break;
		default: break;
	}

	if (str.GetLength() > 0) SetTitle(str);
}

//������������˵���ֵ
void ButtonDlg::SetSecondRangeNum(int btn)
{
	//dzhw change m_secondRangeBtnNum == -1 to m_secondRangeBtnNum != -1 2017/3/25
	if ((m_secondRangeBtnNum != -1)&&(btn == 9))//�����˵�����
	{
		if (m_secondRangeBtnNum != -1)
		{
			m_secondRangeBtnNum = -1;
			m_thirdRangeBtnNum = -1;
		}
		SetFirstRangeNum(m_firstRangeBtnNum);
	}
	else//�����˵��������˵�������
	{
		if (m_secondRangeBtnNum == -1)
		{
			if (btn != 9) m_secondRangeBtnNum = btn;
			SendMsg(m_firstRangeBtnNum, btn);
		}
		else
		{
			m_thirdRangeBtnNum = btn;
			SendMsg(m_firstRangeBtnNum, m_secondRangeBtnNum, m_thirdRangeBtnNum);
		}
	}

	//�޸Ĳ˵�������
	if (m_firstRangeBtnNum < 9)
	{
		CString str = titleList[m_firstRangeBtnNum - 1][m_secondRangeBtnNum - 1];
		if (str.GetLength() > 0)
		{
			SetTitle(str);
		}
	}
}

void ButtonDlg::SendFirstRangeMsg(int btn)
{
	//SetTitle(itoaa(btn));
	SendMsg(btn);
}

void ButtonDlg::SendSecondRangeMsg(int btn)
{
	SendMsg(m_firstRangeBtnNum, btn);
}

void ButtonDlg::SendThirdRangeMsg(int btn)
{
	SendMsg(m_firstRangeBtnNum, m_secondRangeBtnNum, btn);
}

char * itoaa(int num)
{
	static char tmp[64] = {0};

	memset(tmp, 0, 64);
	sprintf(tmp, "%d", num);

	return tmp;
}

void ButtonDlg::SendMsg(int btn1, int btn2, int btn3)
{
	CString str;
	CWnd * hParent = GetParent();

	str.Format("%d", btn1);
	if (btn2 > 0)
	{
		str += "_";
		str += itoaa(btn2);
	}
	if (btn3 > 0)
	{
		str += "_";
		str += itoaa(btn3);
	}
	
	::SendMessage(hParent->GetSafeHwnd(), WM_USER_BUTTON_MSG, (WPARAM)str.GetBuffer(), NULL);
}

void ButtonDlg::BtnDown(HWND btnHwnd)
{
	int  btn = SwitchBtn(btnHwnd);
	switch (btn)
	{
		//һ���˵�����
	case 1: setBtmBmp(IDC_BTN_SYSTEM_INTRODUCTION, m_MenuBtnList[8]->m_BtnDownFileName); break;
	case 2: setBtmBmp(IDC_BTN_SYSTEM_DESIGN_REQUIREMENTS, m_MenuBtnList[9]->m_BtnDownFileName); break;
		//һ���˵� �˸���ť
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
		{
			setBtmBmp(IDC_BTN_DEVICE_SELECT + btn - 3, m_MenuBtnList[btn - 3]->m_BtnDownFileName);
		}
		break;
		//�����˵��Ÿ���ť
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
		{
			if (m_secondRangeBtnNum == -1)
			{
				Btn2BmpDown(m_firstRangeBtnNum, btn - 10);
			}
			else
			{
				Btn23BmpDown(m_firstRangeBtnNum, m_secondRangeBtnNum, btn - 10);
			}
		}
		break;
		//һ���˵��ײ�
	case 20: setBtmBmp(IDC_BTN_INFO_CAP_RUN, m_MenuBtnList[10]->m_BtnDownFileName); break;
	case 21:
		{
			if (m_startCheck == false)
			{
				if (m_startrun == false)
				{
					setBtmBmp(IDC_BTN_ALARM_RUN, m_MenuBtnList[11]->m_BtnDownFileName);
				}
				else
				{
					setBtmBmp(IDC_BTN_ALARM_RUN, m_MenuBtnList[12]->m_BtnDownFileName);
				}
			}
		}
		break;
	case 22:
		{
			if ((m_startrun == false) && (m_startCheck == false))
			{
				setBtmBmp(IDC_BUTTON_SWITCH_PIC, m_MenuBtnList[13]->m_BtnDownFileName);
			}
		}
		break;
	case 23:
		{
			if (m_startrun == false)
			{
				if (m_startCheck == false)
				{
					setBtmBmp(IDC_BUTTON_START_CHECK, m_MenuBtnList[15]->m_BtnDownFileName);
				}
				else
				{
					setBtmBmp(IDC_BUTTON_START_CHECK, m_MenuBtnList[14]->m_BtnDownFileName);
				}
			}
		}
		break;
	default:
		break;
	}
}

void ButtonDlg::BtnUp(HWND btnHwnd)
{
	int btn = SwitchBtn(btnHwnd);

	if ((btn > 2 && btn < 10) || btn==23)
	{	
		if (btn == 7 || (btn==23 && !m_startCheck ))
		{
			parent->m_pemf_wnd->setMode(0);//ϵͳ���ģʽ ���Զ�ģʽ
		}
		else
		{
			parent->m_pemf_wnd->setMode(1);//ϵͳ���ģʽ ���ֶ�ģʽ
		}
	}

	switch (btn)
	{
	case 1:
		{
			//�����˶� һ���˵��İ�ť�ָ� dzw 2017/3/25
			Btn1BmpInit();
			setBtmBmp(IDC_BTN_SYSTEM_INTRODUCTION, m_MenuBtnList[8]->m_BtnSetFileName);
			setBtmBmp(IDC_BTN_SYSTEM_DESIGN_REQUIREMENTS, m_MenuBtnList[9]->m_BtnUpFileName);
			SetFirstRangeNum(9);
			SendFirstRangeMsg(9);
			Btn2BmpInit(m_firstRangeBtnNum);
		}
		break;
	case 2:
		{
			//�����˶� һ���˵��İ�ť�ָ� dzw 2017/3/25
			Btn1BmpInit();
			setBtmBmp(IDC_BTN_SYSTEM_DESIGN_REQUIREMENTS, m_MenuBtnList[9]->m_BtnSetFileName);
			setBtmBmp(IDC_BTN_SYSTEM_INTRODUCTION, m_MenuBtnList[8]->m_BtnUpFileName);
			SetFirstRangeNum(10);
			SendFirstRangeMsg(10);
			Btn2BmpInit(m_firstRangeBtnNum);
		}
		break;
		//һ���˵� �˸���ť
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
		{
			Btn1BmpInit();
			setBtmBmp(IDC_BTN_DEVICE_SELECT + btn - 3, m_MenuBtnList[btn - 3]->m_BtnSetFileName);
			SetFirstRangeNum(btn - 2);
			Btn2BmpInit(m_firstRangeBtnNum);
		}
		break;
		//�����˵� 9����ť
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
		{
			if (m_secondRangeBtnNum == -1)
			{
				//Btn2BmpSet(2, btn - 10);
				if ((btn-10) < secondMenu[m_firstRangeBtnNum-1])
				{
					if ((m_firstRangeBtnNum != 3)||((btn - 10) != 5))
					{
						SetSecondRangeNum(btn - 10);
						Btn23BmpInit(m_firstRangeBtnNum, btn - 10);
					}
				}
				else
				{
					Btn2BmpInit(m_firstRangeBtnNum);
					setBtmBmp(IDC_BTN_ONE + btn - 11, m_MenuBtnList[m_firstRangeBtnNum-1]->m_MenuBtnList[btn-11]->m_BtnSetFileName);
					//SendMsg(m_firstRangeBtnNum, btn-10, m_thirdRangeBtnNum);
					SendMsg(m_firstRangeBtnNum, btn-10);
					//�޸Ĳ˵�������
					if (m_firstRangeBtnNum < 9)
					{
						CString str = titleList[m_firstRangeBtnNum - 1][btn-10 - 1];
						if (str.GetLength() > 0)
						{
							SetTitle(str);
						}
					}
				}
			}
			else
			{
				Btn23BmpSet(m_firstRangeBtnNum, m_secondRangeBtnNum, btn - 10);
				SetSecondRangeNum(btn - 10);
			}
		}
		break;
	case 19:
		{
			Btn2BmpInit(m_firstRangeBtnNum);
			SetSecondRangeNum(9);
			if (m_secondRangeBtnNum == -1)
			{
				setBtmBmp(IDC_BTN_ONE + btn - 11, m_MenuBtnList[m_firstRangeBtnNum-1]->m_MenuBtnList[btn-11]->m_BtnSetFileName);
			}
		}
		break;

		//�ײ�������ť
	case 20:
		{
			//Btn3BmpInit();
			setBtmBmp(IDC_BTN_INFO_CAP_RUN, m_MenuBtnList[10]->m_BtnUpFileName);
			SendFirstRangeMsg(11);
		}
		break;
	case 21:
		{
			if (m_startCheck == false)
			{
				//Btn3BmpInit();
				m_startrun = !m_startrun;
				if (m_startrun == false)
					setBtmBmp(IDC_BTN_ALARM_RUN, m_MenuBtnList[11]->m_BtnUpFileName);
				else
					setBtmBmp(IDC_BTN_ALARM_RUN, m_MenuBtnList[12]->m_BtnUpFileName);
				
				SendFirstRangeMsg(12);
			}
		}
		break;
	case 22:
		{
			if ((m_startrun == false) && (m_startCheck == false))
			{
				setBtmBmp(IDC_BUTTON_SWITCH_PIC, m_MenuBtnList[13]->m_BtnUpFileName);
			}
		}
		break;
	case 23:
		{
			if (m_startrun == false)
			{
				m_startCheck = !m_startCheck;
				if (m_startCheck == false)
				{
					setBtmBmp(IDC_BUTTON_START_CHECK, m_MenuBtnList[14]->m_BtnUpFileName);
				}
				else
				{
					setBtmBmp(IDC_BUTTON_START_CHECK, m_MenuBtnList[15]->m_BtnUpFileName);
				}
			}
		}
		break;
	default:
		break;
	}
}


BOOL ButtonDlg::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_LBUTTONDOWN)
	{
		// ��ť����
		BtnDown(pMsg->hwnd);
	}
	else if(pMsg->message == WM_LBUTTONUP)
	{
		// ��ť����
		BtnUp(pMsg->hwnd);
	}

	return CDialog::PreTranslateMessage(pMsg);
}


void ButtonDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()  
	CRect   rect;   
	GetClientRect(&rect);   
	CDC   dcMem;   
	dcMem.CreateCompatibleDC(&dc);   
	CBitmap   bmpBackground;   
	bmpBackground.LoadBitmap(IDB_BACKGURAND);

	BITMAP   bitmap;   
	bmpBackground.GetBitmap(&bitmap);   
	CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground);

	dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,
		rect.Width(),rect.Height(),SRCCOPY);

	CBitmap   title;
	BITMAP    bmpTitle;
	title.LoadBitmap(IDB_TITLE);
	title.GetBitmap(&bmpTitle);
	pbmpOld = dcMem.SelectObject(&title);

	dc.StretchBlt(25,40,bitmap.bmWidth, bitmap.bmWidth,&dcMem,0,0,
		bitmap.bmWidth, bitmap.bmWidth,SRCCOPY);

	int width = rect.right - rect.left;
	CString str = "�����ʵʩ";

	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(255,255,255));
	dc.SelectObject(&m_font);
	dc.TextOut((width - str.GetLength()*10)/2, 176, str);

	CFont font;
	font.CreatePointFont(120,"����");//����12������
	str = "����������Ϣ�������޹�˾";
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(255,255,255));
	dc.SelectObject(&font);
	dc.TextOut((width - str.GetLength()*8)/2, 830, str);

	EnterCriticalSection(&g_criSection); //��ʾ�����ٽ���

	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(255,255,255));
	dc.SelectObject(&m_font);
	dc.TextOut((width - m_titleText.GetLength()*10)/2, 372, m_titleText);

	LeaveCriticalSection(&g_criSection); //�뿪�ٽ���
}


HBRUSH ButtonDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

void ButtonDlg::SetTitle(CString str)
{
	EnterCriticalSection(&g_criSection); //��ʾ�����ٽ���

	m_titleText = str;

	RECT wRect;
	GetWindowRect(&wRect);
	CRect rect;
	rect.left = 0;
	rect.right = wRect.right;
	rect.top = 372;
	rect.bottom = 402;
	InvalidateRect(&rect);

	LeaveCriticalSection(&g_criSection); //�뿪�ٽ���
}

//��������
void ButtonDlg::OnBnClickedBtnInfoCapRun()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	parent->m_net->ShowWindow(true);
}

//��������
void ButtonDlg::OnBnClickedBtnAlarmRun()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_startCheck == true)
	{
		return;
	}
	
	if (m_startrun == true)
	{
		if (parent->m_net->send_cmd_whole_start_run() == false)
		{
			m_startrun = false;
			setBtmBmp(IDC_BTN_ALARM_RUN, m_MenuBtnList[11]->m_BtnUpFileName);
			return;
		}
		setBtmBmp(IDC_BUTTON_SWITCH_PIC, m_MenuBtnList[13]->m_BtnSetFileName);
		setBtmBmp(IDC_BUTTON_START_CHECK, m_MenuBtnList[14]->m_BtnSetFileName);
	}else
	{
		if (parent->m_net->send_cmd_whole_stop_run() == false)
		{
			m_startrun = true;
			setBtmBmp(IDC_BTN_ALARM_RUN, m_MenuBtnList[12]->m_BtnUpFileName);
			return;
		}
	
		setBtmBmp(IDC_BUTTON_SWITCH_PIC, m_MenuBtnList[13]->m_BtnUpFileName);
		setBtmBmp(IDC_BUTTON_START_CHECK, m_MenuBtnList[14]->m_BtnUpFileName);
	}

}


void ButtonDlg::OnBnClickedBtnConstructionCommissioning()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


//ѡ�񴫸���
void ButtonDlg::OnBnClickedButtonSwitchPic()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_startrun == true)
	{
		return;
	}

	if (m_startCheck == true)
	{
		return;
	}

	//parent->m_selectnetdlg->ShowWindow(true);
	Selectnet *dlg =new Selectnet(this);
		if (dlg->DoModal()==IDOK )
		{

		}else
		{
		
		}
		delete dlg;
}


//��ʼʩ�����
void ButtonDlg::OnBnClickedButtonStartCheck()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ʼ
	if (m_startrun == true)
	{
		return;
	}

	if (m_startCheck)
	{
 		if (parent->m_net->send_cmd_start_scan() == false)
 		{
			m_startCheck = false;
			setBtmBmp(IDC_BUTTON_START_CHECK, m_MenuBtnList[14]->m_BtnUpFileName);
			return;
 		}
		setBtmBmp(IDC_BUTTON_SWITCH_PIC, m_MenuBtnList[13]->m_BtnSetFileName);
		setBtmBmp(IDC_BTN_ALARM_RUN, m_MenuBtnList[11]->m_BtnSetFileName);
	}
	else //ֹͣ
	{
		if (parent->m_net->send_cmd_stop_scan() == false)
		{
			m_startCheck = true;
			setBtmBmp(IDC_BUTTON_START_CHECK, m_MenuBtnList[15]->m_BtnUpFileName);
			return;
		}

		setBtmBmp(IDC_BUTTON_SWITCH_PIC, m_MenuBtnList[13]->m_BtnUpFileName);
		setBtmBmp(IDC_BTN_ALARM_RUN, m_MenuBtnList[11]->m_BtnUpFileName);
	}
}
