#pragma once
#include "afxwin.h"
#include "xSkinButton.h"
class PageDlg1;
#define  PICTURE_5_LEVEL     "\\res\\picture_5\\"  
// OptionSel 对话框

class OptionSel : public CDialogEx
{
	DECLARE_DYNAMIC(OptionSel)

public:
	OptionSel(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~OptionSel();

// 对话框数据
	enum { IDD = IDD_OPTION_DLG };
	
	PageDlg1 *parent;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CToolTipCtrl     m_Mytip;
	void CeateTipInfmation(byte num);
	DECLARE_MESSAGE_MAP()
public:
	
	 void OnBnClickedRadio1();
	 void OnBnClickedRadio2();
	 void OnBnClickedRadio3();
	 void OnBnClickedRadio4();
	 void OnBnClickedRadio5();
	 void OnBnClickedRadio6();
	//int m_radio_val;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void DrawBmp(CString strname);
	CString path;
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void setuserfont();
	void setuserfont(WORD size,CString fontname ="宋体");
	CFont m_font;

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	void NewRadioWithQuestion(byte num);
	int m_SelRadio;
	CxSkinButton *m_btnradio_1;
	CxSkinButton *m_btnradio_2;
	CxSkinButton *m_btnradio_3;
	CxSkinButton *m_btnradio_4;
	CxSkinButton *m_btnradio_5;
	CxSkinButton *m_btnradio_6;
	CxSkinButton* NewMyRadio(int nID,CRect rect,int nStyle);
	void  SetIteminfmation(byte num);
	byte m_num;
	CStatic m_txt_1;
	CStatic m_txt_2;
	CStatic m_txt_3;
	CStatic m_txt_4;
	CStatic m_txt_5;
	CStatic m_txt_6;
	CxSkinButton m_next;
	afx_msg void OnBnClickedButton1();
	void  ChangbtnVisable(byte num);
	CStatic m_optname;
};
