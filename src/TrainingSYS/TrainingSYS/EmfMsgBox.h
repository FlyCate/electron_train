#pragma once


// EmfMsgBox 对话框
#include "stdafx.h"
#include <string>
using namespace std;

#include "efm_struct.h"
#include "afxwin.h"
#include "xSkinButton.h"

class EmfMsgBox : public CDialog
{
	DECLARE_DYNAMIC(EmfMsgBox)

public:
	EmfMsgBox(CWnd* pParent = NULL,bool del_self = false);
	EmfMsgBox(string msg,string back_img_name,CWnd* pParent = NULL,bool del_self = false);
	EmfMsgBox(bool ok,EFMMESSAGE msg,CWnd* pParent = NULL,bool del_self = false);
	virtual ~EmfMsgBox();
	void showDlg();
	void reset(bool ok,EFMMESSAGE msg);
// 对话框数据
	enum { IDD = IDD_DIALOG_EMFMESSAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


private:
	string m_back_imag_name;
	string m_msg;
	CImage m_backBitmap;
	EFMMESSAGE m_efmmsg;
	bool m_ok;

	bool m_move;
	CPoint m_startPoint;
	CxSkinButton m_ok_bt;
	bool m_del_self;

private:
	void reinitDlg();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
private:
	CButton m_edit_bt;
public:
	afx_msg void OnBnClickedButtonEdit();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedBtEmfOk();
	virtual void OnOK();
	virtual void OnCancel();
};
