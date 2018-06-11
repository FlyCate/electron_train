#pragma once

#include "efm_struct.h"
// EmfEditMsg 对话框

class EmfEditMsg : public CDialogEx
{
	DECLARE_DYNAMIC(EmfEditMsg)

public:
	EmfEditMsg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~EmfEditMsg();

// 对话框数据
	enum { IDD = IDD_DIALOG_EDITMSG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CString m_image_path;
public:
	void setImage_path(CString imagpath)
	{
		m_image_path = imagpath;
		
		if (m_image_path=="res/warning.png")
		{
			m_image_selected = 1;
		}
		else if (m_image_path=="res/error.png")
		{
			m_image_selected = 2;
		}else if (m_image_path=="res/forbidden.png")
		{
			m_image_selected = 3;
		}else
		{
			m_image_selected = 0;
		}

//		UpdateData(FALSE);
	}
	CString getImage_path()
	{
		return m_image_path;
	}
	void setMsg(CString msg)
	{
		m_edit_msg2 = msg;
//		UpdateData(FALSE);
	}
	CString getMsg()
	{
		return m_edit_msg2;
	}
private:
	afx_msg void OnBnClickedOk();
	int m_image_selected;
	
private:
	CString m_edit_msg2;
};
