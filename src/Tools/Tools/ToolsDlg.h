
// ToolsDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "PICDLG.h"
#include "../../TrainingSYS/tinyxml/tinyxml.h"

// CToolsDlg �Ի���
class CToolsDlg : public CDialogEx
{
// ����
public:
	CToolsDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TOOLS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	CString GetFilePath();
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
