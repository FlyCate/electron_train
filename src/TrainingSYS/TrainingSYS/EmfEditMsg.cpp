// EmfEditMsg.cpp : 实现文件
//

#include "stdafx.h"
#include "TrainingSYS.h"
#include "EmfEditMsg.h"
#include "afxdialogex.h"


// EmfEditMsg 对话框

IMPLEMENT_DYNAMIC(EmfEditMsg, CDialogEx)

EmfEditMsg::EmfEditMsg(CWnd* pParent /*=NULL*/)
	: CDialogEx(EmfEditMsg::IDD, pParent)
	, m_image_selected(0)
	, m_edit_msg2(_T(""))
{

}



EmfEditMsg::~EmfEditMsg()
{
}

void EmfEditMsg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_image_selected);
	DDX_Text(pDX, IDC_RICHEDIT2_MSG, m_edit_msg2);
}


BEGIN_MESSAGE_MAP(EmfEditMsg, CDialogEx)
	ON_BN_CLICKED(IDOK, &EmfEditMsg::OnBnClickedOk)
END_MESSAGE_MAP()


// EmfEditMsg 消息处理程序




void EmfEditMsg::OnBnClickedOk()
{
	UpdateData();
	if (m_image_selected==0)
	{
		m_image_path = "res/right.png";
	}else if (m_image_selected==1)
	{
		m_image_path = "res/warning.png";
	}
	else if (m_image_selected==2)
	{
		m_image_path = "res/error.png";
	}else
	{
		m_image_path = "res/forbidden.png";
	}

	CDialogEx::OnOK();
}
