#pragma once

#include <vector>
#include "VLCWrapper.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "xSkinButton.h"
#include "myslider.h"

using namespace std;

#define  XML_VIDEOINF		"res/video.xml"

typedef struct _tag_VideoInfo 
{
	CString videoName;
	CString videoPath;
}VideoInfo, *pVideoInfo;

// PageDlg2 �Ի���
class PageDlg2 : public CDialogEx
{
	DECLARE_DYNAMIC(PageDlg2)

public:
	PageDlg2(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PageDlg2();

// �Ի�������
	enum { IDD = IDD_DLG_PAGE2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
public:
	virtual BOOL OnInitDialog();
	void ReadXMLInfo();
	void UpdatePosition();

public:
	vector<pVideoInfo> m_videoList;
	CString m_cmd;
	CString m_runpath;
	CString m_videoPath;
	VLCWrapper       vlcPlayer; //������
	int64_t          mediaLength;

	DECLARE_MESSAGE_MAP()
	CListCtrl m_videoListCtl;
	// ������
	CMySliderCtrl m_videoSlider;
	// ������С
	CMySliderCtrl m_audioSlider;
	// ������ʾ
	CStatic m_audioStatic;
	// ����ʱ��
	CStatic m_videoTimeStatic;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedButtonPlay();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonBack();
	afx_msg void OnBnClickedButtonFast();
	afx_msg void OnNMDblclkListVideo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
	afx_msg void OnPaint();
	afx_msg void OnMove(int x, int y);

private:
	CImage* m_pImgSound;
	CImage* m_pImgList;
	CImage* m_pImgPlayStatic;

	bool g_pause;

public:
	void ButtonImageInit();
	CxSkinButton m_btn_play;
	CxSkinButton m_btn_stop;
	CxSkinButton m_btn_backword;
	CxSkinButton m_btn_forword;
	CxSkinButton m_btn_pause;

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonPause();
};
