#pragma once
#include "afxwin.h"
#include "xSkinButton.h"

// Selectnet 对话框
class CTrainingSYSDlg;
class Selectnet : public CDialogEx
{
	DECLARE_DYNAMIC(Selectnet)

public:
	Selectnet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Selectnet();

// 对话框数据
	enum { IDD = IDD_DIG_TYPE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_cb_type;
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	int removechildwnd(void);
	void DrawBmp(CString strname);
	afx_msg void OnBnClickedBtnOk();
	CTrainingSYSDlg *parent;
	CString path;
	CxSkinButton m_btn_ok;
	int m_index;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
