
// ToolsDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "PICDLG.h"
#include "../../TrainingSYS/tinyxml/tinyxml.h"

// CToolsDlg 对话框
class CToolsDlg : public CDialogEx
{
// 构造
public:
	CToolsDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TOOLS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	CString GetFilePath();
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	CString m_path;
	PICDLG * m_picDlg;
public:
	CTabCtrl m_tabCtrl;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMove(int x, int y);
};
