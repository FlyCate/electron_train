#pragma once


// PageDlg3 �Ի���

class PageDlg3 : public CDialogEx
{
	DECLARE_DYNAMIC(PageDlg3)

public:
	PageDlg3(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PageDlg3();

// �Ի�������
	enum { IDD = IDD_DLG_PAGE3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
