#pragma once
#include "xSkinButton.h"
#include "PageDlg1.h"
#include "afxwin.h"
// OptionSelMul 对话框

class OptionSelMul : public CDialogEx
{
	DECLARE_DYNAMIC(OptionSelMul)

public:
	OptionSelMul(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~OptionSelMul();

// 对话框数据
	enum { IDD = IDD_MULOPTION_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CxSkinButton *m_radio[12];
	void NewRadioWithQuestion(byte num);
	CxSkinButton* NewMyRadio(int nID,CRect rect,int nStyle);
	RECT calcwndrect(byte num ,byte style,byte optnum);
	virtual BOOL OnInitDialog();
	CStatic * GetDlgYithNum(byte num);
	void RemoveChildWND(void);
	afx_msg void OnPaint();
	CString path;//图片路径
	PageDlg1 *parent;
	void DrawBmp(CString strname);
	void  Initdlgchildwnd(void);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CFont m_font;
	CFont m_fnt;
	void setuserfont(WORD size,CString fontname ="宋体");
	CxSkinButton m_btn_next;

	void IintOptionContentuser(void);
	void HideUNnedWND(void);
	void OnBnClickedRadio1();
	void OnBnClickedRadio2();
	void OnBnClickedRadio3();
	void OnBnClickedRadio4();
	void OnBnClickedRadio5();
	void OnBnClickedRadio6();
	void OnBnClickedRadio7();
	void OnBnClickedRadio8();
	void OnBnClickedRadio9();
	void OnBnClickedRadio10();
	void OnBnClickedRadio11();
	void OnBnClickedRadio12();
	byte m_group_0_sel ;
	byte m_group_1_sel ;
	byte m_group_2_sel ;
	byte m_group_3_sel ;
	afx_msg void OnBnClickedButton1();
	byte m_optglag[4];
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
