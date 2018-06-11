// PageDlg2.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "vlc/vlc.h"
#include "TrainingSYS.h"
#include "TrainingSYSDlg.h"
#include "PageDlg2.h"
#include "afxdialogex.h"
#include <gdiplus.h>

using namespace Gdiplus;

#define TEST 0

// PageDlg2 �Ի���

IMPLEMENT_DYNAMIC(PageDlg2, CDialogEx)

PageDlg2::PageDlg2(CWnd* pParent /*=NULL*/)
	: CDialogEx(PageDlg2::IDD, pParent)
{
	CTrainingSYSDlg * parent = (CTrainingSYSDlg *) pParent;
	m_runpath = parent->m_path;
	m_videoPath = m_runpath + "\\res\\video\\";
	m_cmd = parent->m_cmd;
}

PageDlg2::~PageDlg2()
{
}

void PageDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_VIDEO, m_videoListCtl);
	DDX_Control(pDX, IDC_SLIDER1, m_videoSlider);
	DDX_Control(pDX, IDC_SLIDER_AUDIO, m_audioSlider);
	DDX_Control(pDX, IDC_STATIC_AUDIO, m_audioStatic);
	DDX_Control(pDX, IDC_STATIC_VIDEO_TIME, m_videoTimeStatic);
	DDX_Control(pDX, IDC_BUTTON_PLAY, m_btn_play);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_btn_stop);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_btn_backword);
	DDX_Control(pDX, IDC_BUTTON_FAST, m_btn_forword);
	DDX_Control(pDX, IDC_BUTTON_PAUSE, m_btn_pause);
}


BEGIN_MESSAGE_MAP(PageDlg2, CDialogEx)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &PageDlg2::OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &PageDlg2::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &PageDlg2::OnBnClickedButtonBack)
	ON_BN_CLICKED(IDC_BUTTON_FAST, &PageDlg2::OnBnClickedButtonFast)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_VIDEO, &PageDlg2::OnNMDblclkListVideo)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_MOVE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, &PageDlg2::OnBnClickedButtonPause)
END_MESSAGE_MAP()

static void HandleVLCEvents(const VLCEvent* pEvt, void* pUserData)
{       
	PageDlg2* pDlg = reinterpret_cast<PageDlg2*>(pUserData); 

	switch(pEvt->type)
	{
	case libvlc_MediaPlayerTimeChanged:
		TRACE("VLC_EVT_TIME_CHANGED: new_time %d[ms]\n", pEvt->u.media_player_time_changed.new_time);
		if(pDlg)
			pDlg->UpdatePosition();
		break;
	}    
}

// PageDlg2 ��Ϣ�������
BOOL PageDlg2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	ReadXMLInfo();

	//����VLC�Ĳ��Ŵ���
	vlcPlayer.SetOutputWindow(GetDlgItem(IDC_STATIC_VIDEO)->GetSafeHwnd());
	//����VLC���¼��ص�����
	vlcPlayer.SetEventHandler(&HandleVLCEvents, this);

	//���ò��Ž�����������������
	m_videoSlider.SetRange(0,10000);
	m_audioSlider.SetRange(0,100);

	//����������С
	m_audioSlider.SetPos(50);
	m_audioStatic.SetWindowText("50");
	m_audioStatic.ShowWindow(SW_HIDE);
	m_videoTimeStatic.ShowWindow(SW_HIDE);

	ButtonImageInit();
	g_pause = false;

	CString path = m_runpath + "\\res\\player\\";
	m_btn_play.SetSkin(path+"play_up.bmp",path+"play_down.bmp",path+"play_up.bmp",path+"play_up.bmp",path+"play_up.bmp",path+"play_mask.bmp",0,0,0);
	m_btn_stop.SetSkin(path+"stop_up.bmp",path+"stop_down.bmp",path+"stop_up.bmp",path+"stop_up.bmp",path+"stop_up.bmp",path+"backword_mask.bmp",0,0,0);
	m_btn_backword.SetSkin(path+"backword_up.bmp",path+"backword_down.bmp",path+"backword_up.bmp",path+"backword_up.bmp",path+"backword_up.bmp",path+"backword_mask.bmp",0,0,0);
	m_btn_forword.SetSkin(path+"forword_up.bmp",path+"forword_down.bmp",path+"forword_up.bmp",path+"forword_up.bmp",path+"forword_up.bmp",path+"backword_mask.bmp",0,0,0);
	m_btn_pause.SetSkin(path+"pause_up.bmp",path+"pause_down.bmp",path+"pause_up.bmp",path+"pause_up.bmp",path+"pause_up.bmp",path+"backword_mask.bmp",0,0,0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void PageDlg2::ReadXMLInfo()
{
	//����Video XML
	TiXmlDocument doc;
	if (!doc.LoadFile(XML_VIDEOINF))
		return;
	//���Ҹ��ڵ�ʧ��
	TiXmlElement* root = doc.FirstChildElement();
	if(root == NULL)
	{	
		doc.Clear();
		return;
	}

	m_videoListCtl.DeleteAllItems();
	m_videoListCtl.InsertColumn(0, "��Ƶ");

	for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		CString elemName = elem->Value();
		// const char* attr;
		CString attr;
		attr = elem->Attribute("priority");
		//cmd ����ƥ����ȷ��
		if (m_cmd == attr)
		{	
			//cmd ����ƥ����ȷ��   
			for(TiXmlElement* e1 = elem->FirstChildElement(); e1 != NULL; e1 = e1->NextSiblingElement())
			{  
				string elemName = e1->Value();
				if (elemName =="video")
				{
					pVideoInfo video = new VideoInfo;
					video->videoName = e1->Attribute("name");
					video->videoPath = m_videoPath;
					video->videoPath += e1->Attribute("path");
					m_videoList.push_back(video);
					m_videoListCtl.InsertItem(0, video->videoName.GetBuffer());
				}
			}
		} 
	}
	doc.Clear();
}

void PageDlg2::UpdatePosition()
{
	mediaLength = vlcPlayer.GetLength();
	int64_t newPosition = vlcPlayer.GetTime();

	CTimeSpan actualPosition(static_cast<time_t>(newPosition/1000));
	CTimeSpan length(static_cast<time_t>(mediaLength/1000));

	CString lengthString;
	lengthString.Format("[%02d:%02d:%02d/%02d:%02d:%02d]",
		actualPosition.GetHours(), actualPosition.GetMinutes(), actualPosition.GetSeconds(),
		length.GetHours(), length.GetMinutes(), length.GetSeconds());

	m_videoTimeStatic.SetWindowText(lengthString);
	
	int newSliderPos = mediaLength ? static_cast<int>((static_cast<double>(newPosition)/static_cast<double>(mediaLength) * 10000)) : 0;
	m_videoSlider.SetPos(newSliderPos);
	
	CString str = "";
	str.Format("pos : %d\n", newSliderPos);
	TRACE(str);
}

void PageDlg2::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CSliderCtrl* pSlider = reinterpret_cast<CSliderCtrl*>(pScrollBar);

	//��������
	if(*pSlider == m_audioSlider)
	{
		int pos = m_audioSlider.GetPos();
		vlcPlayer.SetVolume(pos);
		//CString volume;
		//volume.Format("%d", pos);
		//m_audioStatic.SetWindowText(volume);
	}

	//���ý���
	if(*pSlider == m_videoSlider)
	{
		int pos = m_videoSlider.GetPos();
		vlcPlayer.SetTime(mediaLength/10000*pos);
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

string Unicode2Utf8(const std::wstring& widestring)  
{  
	int utf8size = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, NULL, 0, NULL, NULL);  
	if (utf8size == 0)  
	{  
		throw std::exception("Error in conversion.");  
	}  

	std::vector<char> resultstring(utf8size);  

	int convresult = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, &resultstring[0], utf8size, NULL, NULL);  

	if (convresult != utf8size)  
	{  
		throw std::exception("La falla!");  
	}  

	return std::string(&resultstring[0]);  
}

wstring Acsi2WideByte(std::string& strascii)  
{
	int widesize = MultiByteToWideChar (CP_ACP, 0, (char*)strascii.c_str(), -1, NULL, 0);  
	if (widesize == ERROR_NO_UNICODE_TRANSLATION)  
	{  
		throw std::exception("Invalid UTF-8 sequence.");  
	}  
	if (widesize == 0)  
	{  
		throw std::exception("Error in conversion.");  
	}  
	std::vector<wchar_t> resultstring(widesize);  
	int convresult = MultiByteToWideChar (CP_ACP, 0, (char*)strascii.c_str(), -1, &resultstring[0], widesize);  


	if (convresult != widesize)  
	{  
		throw std::exception("La falla!");  
	}  

	return std::wstring(&resultstring[0]);  
} 

string ASCII2UTF_8(std::string& strAsciiCode)  
{  
	std::string strRet("");  
	//�Ȱ� ascii תΪ unicode  
	std::wstring wstr = Acsi2WideByte(strAsciiCode);  
	//���� unicode תΪ utf8  
	strRet = Unicode2Utf8(wstr);  
	return strRet;  
}


//���� ��ͣ
void PageDlg2::OnBnClickedButtonPlay()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!vlcPlayer.IsPlaying())
	{
		if (g_pause == true)
		{
			vlcPlayer.Play();
			g_pause = false;
		}
		else
		{
			CString videoName;
			int nId;
			//���ȵõ������λ��
			POSITION pos = m_videoListCtl.GetFirstSelectedItemPosition();
			if(pos == NULL)
			{
				MessageBox("������ѡ��һ��","����",MB_ICONEXCLAMATION);
				return;
			}

			//�õ��кţ�ͨ��POSITIONת��
			nId = (int)m_videoListCtl.GetNextSelectedItem(pos);
			videoName = m_videoListCtl.GetItemText(nId,0);

			for (vector<pVideoInfo>::iterator iter = m_videoList.begin(); iter != m_videoList.end(); iter++)
			{
				if (videoName == (*iter)->videoName)
				{
					string videoPath = (*iter)->videoPath.GetBuffer();
					string str = ASCII2UTF_8(videoPath);
					vlcPlayer.OpenMedia(str.c_str());
					vlcPlayer.Play();
					g_pause = false;
				}
			}
		}
	}
}

//��ͣ
void PageDlg2::OnBnClickedButtonPause()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (vlcPlayer.IsPlaying())
	{
		vlcPlayer.Pause();
		g_pause = true;
	}
}

//ֹͣ
void PageDlg2::OnBnClickedButtonStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	vlcPlayer.Stop();
	mediaLength = 0;
	m_videoSlider.SetPos(0);
	CString length;
	m_videoTimeStatic.GetWindowText(length);
	length = CString("[00:00:00")+length.Right(10);

	m_videoTimeStatic.SetWindowText(length);

	CRect rect;
	GetDlgItem(IDC_STATIC_VIDEO)->GetClientRect(rect);
	m_pImgPlayStatic->Draw(GetDlgItem(IDC_STATIC_VIDEO)->GetWindowDC()->GetSafeHdc(), -10, -10, rect.Width()+20, rect.Height()+20);
}

//����
void PageDlg2::OnBnClickedButtonBack()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	vlcPlayer.FastBackward();
}

//���
void PageDlg2::OnBnClickedButtonFast()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	vlcPlayer.FastForward();
}


//˫���б�
void PageDlg2::OnNMDblclkListVideo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	OnBnClickedButtonPlay();
	return;
}


void PageDlg2::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
}

void PageDlg2::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect   rect;
	CRect   rect1;

	GetClientRect(rect);  
	dc.FillSolidRect(rect,RGB(3,46,94));

	int width = rect.Width();
	int height = rect.Height();
 	int totalwidth = 100;
	int totalheight = rect.bottom - rect.top;

	totalheight -= 70 + 10;
	GetDlgItem(IDC_BUTTON_BACK)->MoveWindow(totalwidth, totalheight, 60, 60);
	totalwidth += 60 + 80;
	GetDlgItem(IDC_BUTTON_PAUSE)->MoveWindow(totalwidth, totalheight, 60, 60);
	totalwidth += 60 + 80;
	GetDlgItem(IDC_BUTTON_PLAY)->MoveWindow(totalwidth, totalheight - 5, 70, 70);
	totalwidth += 70 + 80;
	GetDlgItem(IDC_BUTTON_STOP)->MoveWindow(totalwidth, totalheight, 60, 60);
	totalwidth += 60 + 80;
	GetDlgItem(IDC_BUTTON_FAST)->MoveWindow(totalwidth, totalheight, 60, 60);

#if TEST
	totalwidth += 60 + 5;
#else
	totalwidth += 60 + 80;
#endif
	GetDlgItem(IDC_STATIC_AUDIO_SOUND)->MoveWindow(totalwidth, totalheight+(60-m_pImgSound->GetHeight())/2, m_pImgSound->GetWidth(), m_pImgSound->GetHeight());
	m_pImgSound->Draw(GetDlgItem(IDC_STATIC_AUDIO_SOUND)->GetWindowDC()->GetSafeHdc(), 0, 0, m_pImgSound->GetWidth(), m_pImgSound->GetHeight());
	
	totalwidth += m_pImgSound->GetWidth() + 15;
	GetDlgItem(IDC_SLIDER_AUDIO)->GetClientRect(rect);
	GetDlgItem(IDC_SLIDER_AUDIO)->MoveWindow(totalwidth, totalheight+(60-rect.Height())/2, rect.Width(), rect.Height());

	totalwidth += rect.Width() + 15;
	GetDlgItem(IDC_STATIC_AUDIO)->GetClientRect(rect);
	GetDlgItem(IDC_STATIC_AUDIO)->MoveWindow(totalwidth, totalheight+(60-rect.Height())/2, rect.Width(), rect.Height());

	totalwidth += rect.Width() + 15;
	GetDlgItem(IDC_LIST_VIDEO)->MoveWindow(width-180-20, height-119-20, 180, 119);

	m_pImgList->Draw(dc.GetSafeHdc(), width-180-20, height-139-20, m_pImgList->GetWidth(), m_pImgList->GetHeight());

	totalwidth = 20;
	GetDlgItem(IDC_SLIDER1)->GetClientRect(rect);
	GetDlgItem(IDC_STATIC_VIDEO_TIME)->GetClientRect(rect1);
	GetDlgItem(IDC_SLIDER1)->MoveWindow(totalwidth, height-139-20, width-180-20-totalwidth, rect.Height());
	GetDlgItem(IDC_STATIC_VIDEO_TIME)->MoveWindow(width-180-20-15-rect1.Width(), height-139-20, rect1.Width(), rect1.Height());

	GetDlgItem(IDC_STATIC_VIDEO)->MoveWindow(20, 20, width-40, height-139-20-20-10);

	if (!vlcPlayer.IsPlaying())
	{
		GetDlgItem(IDC_STATIC_VIDEO)->GetClientRect(rect);
		m_pImgPlayStatic->Draw(GetDlgItem(IDC_STATIC_VIDEO)->GetWindowDC()->GetSafeHdc(), -10, -10, rect.Width()+20, rect.Height()+20);
	}
}


void PageDlg2::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	// TODO: �ڴ˴������Ϣ����������
}

void SetImgAlpha(CImage * img)
{
	if ( img->GetBPP() == 32 ) 
	{ 
		for(int i = 0; i < img->GetWidth(); i++) 
		{ 
			for(int j = 0; j < img->GetHeight(); j++) 
			{ 
				unsigned char* pucColor = reinterpret_cast<unsigned char *>(img->GetPixelAddress(i , j)); 
				pucColor[0] = pucColor[0] * pucColor[3] / 255; 
				pucColor[1] = pucColor[1] * pucColor[3] / 255; 
				pucColor[2] = pucColor[2] * pucColor[3] / 255; 
			} 
		} 
	}
}

void PageDlg2::ButtonImageInit()
{
	CString path = "";

	path = m_runpath + "\\res\\player\\sound.png";
	m_pImgSound = new CImage; 
	m_pImgSound->Load(path.GetBuffer());

	path = m_runpath + "\\res\\player\\list.png";
	m_pImgList = new CImage; 
	m_pImgList->Load(path.GetBuffer());
	
	path = m_runpath + "\\res\\player\\play.png";
	m_pImgPlayStatic = new CImage; 
	m_pImgPlayStatic->Load(path.GetBuffer());
}

HBRUSH PageDlg2::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	switch(pWnd->GetDlgCtrlID()) 
	{
	case IDC_STATIC_AUDIO:
	case IDC_STATIC_VIDEO_TIME: 
		pDC->SetBkMode(TRANSPARENT); 
		pDC->SetTextColor(RGB(255,255,255));
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	default: 
		break; 
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
