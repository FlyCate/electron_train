#pragma once
#include "afxwin.h"
#include <vector>

using namespace std;

typedef struct _tag_MenuBtn MenuBtn, *pMenuBtn;

struct _tag_MenuBtn 
{
	int m_MenuBtnNum;
	CString m_BtnNum; //例：1   1-1   1-1-1
	CString m_BtnUpFileName;
	CString m_BtnDownFileName;
	CString m_BtnSetFileName;
	vector<pMenuBtn> m_MenuBtnList;
};

// ButtonDlg 对话框

class ButtonDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ButtonDlg)

public:
	ButtonDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ButtonDlg();

// 对话框数据
	enum { IDD = IDD_DLG_BUTTON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 二级菜单标题
	CStatic m_title;
	BOOL PreTranslateMessage(MSG* pMsg);
	BOOL OnInitDialog();

private:
	void BtnInit();
	void setBtmBmp(int btnID, int bmpID);
	void setBtmBmp(int btnID, CString strFileName);

	void BtnDown(HWND btnHwnd);
	void BtnUp(HWND btnHwnd);

	void Btn1BmpInit();
	void Btn2BmpInit(int btn);
	void Btn3BmpInit();
	void Btn23BmpInit(int btn1, int btn2);

	void Btn2BmpSet(int btn1, int btn2);
	void Btn2BmpDown(int btn1, int btn2);
	void Btn23BmpSet(int btn1, int btn2, int btn3);
	void Btn23BmpDown(int btn1, int btn2, int btn3);

	void SetFirstRangeNum(int btn);
	void SetSecondRangeNum(int btn);
	void SetThirdRangeNum(int btn);

	int SwitchBtn(HWND btnHwnd);
	void SendFirstRangeMsg(int btn);
	void SendSecondRangeMsg(int btn);
	void SendThirdRangeMsg(int btn);
	void SendMsg(int btn1, int btn2 = 0, int btn3 = 0);

private:
	int m_firstRangeBtnNum;	//保存一级菜单按下的编号
	int m_secondRangeBtnNum;//保存二级菜单按下的编号
	int m_thirdRangeBtnNum;//保存三级菜单按下的编号
	vector<pMenuBtn> m_MenuBtnList;
	CString m_picPath;

public:
	// 系统简介
	CButton m_system;
	CFont m_font;
	CString m_titleText;
	CRITICAL_SECTION g_criSection; //定义临界区变量
	CTrainingSYSDlg * parent;

	void SetTitle(CString str);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnInfoCapRun();
	afx_msg void OnBnClickedBtnAlarmRun();
	bool m_startrun;  //开始运行标志位
	bool m_startCheck;//开始检测标志位
	afx_msg void OnBnClickedBtnConstructionCommissioning();
	afx_msg void OnBnClickedButtonSwitchPic();
	afx_msg void OnBnClickedButtonStartCheck();
};
