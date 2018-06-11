#pragma once
#include "afxcmn.h"
#include "message.h"
#include <list>
#include "afxwin.h"

using namespace std;

// PICDLG 对话框

class PICDLG : public CDialog
{
	DECLARE_DYNAMIC(PICDLG)

public:
	PICDLG(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PICDLG();

// 对话框数据
	enum { IDD = IDD_DIALOG_ADD_PIC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listCmd;
	void * m_parant;
	afx_msg void OnPaint();

	int ReadPictureXMl(CString path);
	afx_msg void OnBnClickedButtonNew();

	list<CMD> g_cmdList;
	CEdit m_cmdEdit;
	CEdit m_titleEdit;
	CEdit m_backEdit;
	CButton m_linkEdit;
	CEdit m_picEdit;
	list<CString> m_picEditstr;
	pCMD m_pCmd;
	afx_msg void OnBnClickedButtonEditLoad();
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonWrite();
	afx_msg void OnBnClickedButtonDel2();
};
