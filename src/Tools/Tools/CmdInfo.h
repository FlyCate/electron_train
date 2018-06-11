#pragma once
#include "afxwin.h"
#include <list>

using namespace std;

// CCmdInfo 对话框

class CCmdInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CCmdInfo)

public:
	CCmdInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCmdInfo();

// 对话框数据
	enum { IDD = IDD_DIALOG_CMD_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_cmd;
	CEdit m_title;
	CEdit m_backPic;
	CButton m_link;
	CEdit m_piclist;
	list<CString> m_listPic;
	afx_msg void OnBnClickedButtonPicLoad();
	afx_msg void OnBnClickedOk();

	void * parant;
};
