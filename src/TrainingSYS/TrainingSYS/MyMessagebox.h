#pragma once
#include "afxwin.h"
#include "xSkinButton.h"

// MyMessagebox 对话框

class MyMessagebox : public CDialogEx
{
	DECLARE_DYNAMIC(MyMessagebox)

public:
	MyMessagebox(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MyMessagebox();

// 对话框数据
	enum { IDD = IDD_DLGMESSAGEBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CxSkinButton m_btn_ok;
	virtual BOOL OnInitDialog();
	CString m_content;
	CString m_tittle;
	afx_msg void OnBnClickedBtnKnow();
	afx_msg void OnPaint();
	CStatic m_item;
	CStatic m_text;
	CString bkpicpath;
	CString btnpicpath;
	CString m_return_str;
	void SetTheContent(CString content);
	void SetTheTitle(CString tittle);
	CString GetReturnValue();
	void DrawBmp(CString strname);
	void SetBkPicture(CString picname);
	void SetbtnPicture(CString picname);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void RemoveWindow( );
	CFont m_font;
	void setuserfont(WORD size,CString fontname= "宋体");
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
//	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
CString MsgBox(CString tittle,CString content,CString bkpathbmp);
CString MsgBox(CString tittle,CString content,CString bkpathbmp,CString btnbmp);
