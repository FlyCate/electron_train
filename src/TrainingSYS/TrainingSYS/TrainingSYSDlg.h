
// TrainingSYSDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "PageDlg1.h"
#include "PageDlg2.h"
#include "PageDlg3.h"
#include "ButtonDlg.h"
#include "MyTabCtrl.h"
//#include "SettingCom.h"
#include "Selectnet.h"
#include "Net_setting.h"
class PageDlg1;
class PageDlg2;
class PageDlg3;
class ts_emf_wnd;
class ButtonDlg; 
class CMyTabCtrl;
class Net_setting;
// #define  UI_X_SIZE  1600
// #define UI_Y_SIZE   860

typedef struct  _BACK_INF_
{   
	CString  cmd;
	CString  name;	//返回选项标内容信息	 如温度传感器
	byte  num;		//返回项目内容所选个数   如温度传感器两个
	_BACK_INF_()
	{
		name   ="";
		num	    =0;           
	};
} BACK_INF,*PBACK_INF;
// CTrainingSYSDlg 对话框
class CTrainingSYSDlg : public CDialogEx
{
// 构造
public:
	CTrainingSYSDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CTrainingSYSDlg();
// 对话框数据
	enum { IDD = IDD_TRAININGSYS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void CTrainingSYSDlg::SetMainWindowFullScreen();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	void InitMainTabControl(void);
	void RepainTabchidWnd(void);
	CString GetFilePath() ;
	// tab列表
	CMyTabCtrl m_tab_main;
	CRect	m_oldRect;
	CString m_cmd;		//保存按键发送给窗口的命令
	PageDlg1 *m_page1;
	PageDlg2 *m_page2;
	PageDlg3 *m_page3;
	CRect	m_mainoldRect;//主对话框原始大小
//	Selectnet *m_selectnetdlg;
	CString m_path;
	CString pictitlename;
	CString videotitlename;
	CString linktittlename;
	CString old_linktittlename;
	vector<BACK_INF> m_bacakinf;	//返回内容集合
	ts_emf_wnd *m_pemf_wnd;		//矢量图显示窗口
//yng 2016-3-22
public:
	//ts_emf_wnd *m_pemf_wnd;		//矢量图显示窗口
	//dzw 2016-3-24
	ButtonDlg * m_btnDlg;		//按钮窗口
public:
	afx_msg void OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnButtnMsg(WPARAM wParam, LPARAM lParam);
	int ReadXMlTitleName(CString cmd);
	int ReadVideoXMlTitleName(CString cmd);	//搜索video xml title name
	void RepainMainWnd(void);
	BOOL PreTranslateMessage(MSG* pMsg);

	bool FindDataWitchcmd(CString cmd);

	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedMin();
//	afx_msg void OnClose();
//	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
//	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnOK();
	virtual void OnCancel();
//yng 
	void close_window();


//dzhw
	void setBtmBmp(int btnID, int bmpID);
	//SettingCom *m_com;
	Net_setting *m_net;
	byte m_pictype;//当前图片类型 1 485图片 2 433图片 3zigbee图片  4 wifi图片 0 未设置
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
   