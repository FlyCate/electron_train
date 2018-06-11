#pragma once


// PageDlg3 对话框

class PageDlg3 : public CDialogEx
{
	DECLARE_DYNAMIC(PageDlg3)

public:
	PageDlg3(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PageDlg3();

// 对话框数据
	enum { IDD = IDD_DLG_PAGE3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
