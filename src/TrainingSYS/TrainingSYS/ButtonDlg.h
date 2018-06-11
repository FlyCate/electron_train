#pragma once
#include "afxwin.h"
#include <vector>

using namespace std;

typedef struct _tag_MenuBtn MenuBtn, *pMenuBtn;

struct _tag_MenuBtn 
{
	int m_MenuBtnNum;
	CString m_BtnNum; //����1   1-1   1-1-1
	CString m_BtnUpFileName;
	CString m_BtnDownFileName;
	CString m_BtnSetFileName;
	vector<pMenuBtn> m_MenuBtnList;
};

// ButtonDlg �Ի���

class ButtonDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ButtonDlg)

public:
	ButtonDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ButtonDlg();

// �Ի�������
	enum { IDD = IDD_DLG_BUTTON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// �����˵�����
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
	int m_firstRangeBtnNum;	//����һ���˵����µı��
	int m_secondRangeBtnNum;//��������˵����µı��
	int m_thirdRangeBtnNum;//���������˵����µı��
	vector<pMenuBtn> m_MenuBtnList;
	CString m_picPath;

public:
	// ϵͳ���
	CButton m_system;
	CFont m_font;
	CString m_titleText;
	CRITICAL_SECTION g_criSection; //�����ٽ�������
	CTrainingSYSDlg * parent;

	void SetTitle(CString str);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnInfoCapRun();
	afx_msg void OnBnClickedBtnAlarmRun();
	bool m_startrun;  //��ʼ���б�־λ
	bool m_startCheck;//��ʼ����־λ
	afx_msg void OnBnClickedBtnConstructionCommissioning();
	afx_msg void OnBnClickedButtonSwitchPic();
	afx_msg void OnBnClickedButtonStartCheck();
};
