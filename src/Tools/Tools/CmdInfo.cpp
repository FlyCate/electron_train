// CmdInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "Tools.h"
#include "CmdInfo.h"
#include "afxdialogex.h"
#include "message.h"
#include "PICDLG.h"

// CCmdInfo 对话框

IMPLEMENT_DYNAMIC(CCmdInfo, CDialogEx)

CCmdInfo::CCmdInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCmdInfo::IDD, pParent)
{
	parant = (void *) pParent;
}

CCmdInfo::~CCmdInfo()
{
}

void CCmdInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_CMD, m_cmd);
	DDX_Control(pDX, IDC_EDIT_TITLE, m_title);
	DDX_Control(pDX, IDC_EDIT_BACK_PIC, m_backPic);
	DDX_Control(pDX, IDC_CHECK_LINK, m_link);
	DDX_Control(pDX, IDC_EDIT_PICTURE, m_piclist);
}


BEGIN_MESSAGE_MAP(CCmdInfo, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_PIC_LOAD, &CCmdInfo::OnBnClickedButtonPicLoad)
	ON_BN_CLICKED(IDOK, &CCmdInfo::OnBnClickedOk)
END_MESSAGE_MAP()


// CCmdInfo 消息处理程序

BOOL CCmdInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_backPic.SetWindowText("01.bmp");

	return TRUE;
}

//加载图片
void CCmdInfo::OnBnClickedButtonPicLoad()
{
	// TODO: 在此添加控件通知处理程序代码
	CString pathName,fileName,fileTitle;

	char* filters = ("BMP Files (*.bmp)|*.bmp|All Files (*.*)|*.*||");

	//创建一个可以选择多个文件的CFileDialog
	CFileDialog fileDlg(true,NULL,"*.bmp",OFN_ALLOWMULTISELECT | OFN_ENABLESIZING | OFN_HIDEREADONLY,filters);

	//最多可以打开500个文件
	fileDlg.m_ofn.nMaxFile = 500 * MAX_PATH;

	char* ch = new TCHAR[fileDlg.m_ofn.nMaxFile];
	fileDlg.m_ofn.lpstrFile = ch;

	//对内存块清零
	ZeroMemory(fileDlg.m_ofn.lpstrFile,sizeof(TCHAR) * fileDlg.m_ofn.nMaxFile);

	//显示文件对话框，获得文件名集合
	if(fileDlg.DoModal() == IDOK)
	{
		m_listPic.clear();
		//获取第一个文件的位置
		POSITION pos_file;
		pos_file = fileDlg.GetStartPosition();

		//循环读出每个路径并存放在数组中
		while(pos_file != NULL)
		{
			//将文件路径存放在数组中
			pathName = fileDlg.GetNextPathName(pos_file);

			//获取文件名
			//从字符串的后面往前遍历，如果遇到'\'则结束遍历，'\'右边的字符串则为文件名
			int length = pathName.GetLength();     
			for(int i = length -1; i>0;i--)
			{
				if('\\' == pathName. GetAt(i))
				{//判断当前字符是否是'\'
					fileName = pathName.Right(length - i -1);
					break;//跳出循环
				}
			}//endfor
			m_listPic.push_back(fileName);
		}      
	}
	delete[] ch;

	CString m_disp;
	for (list<CString>::iterator iter = m_listPic.begin(); iter != m_listPic.end(); iter++)
	{
		m_disp += "\"";
		m_disp += *iter;
		m_disp += "\"\r\n";
	}

	m_piclist.SetWindowText(m_disp.GetBuffer());
}


void CCmdInfo::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	m_cmd.GetWindowText(str);
	if (str.GetLength() == 0)
	{
		MessageBox("CMD 不能为空");
		return;
	}

	m_title.GetWindowText(str);
	if (str.GetLength() == 0)
	{
		MessageBox("Title 不能为空");
		return;
	}

	if (m_listPic.size() == 0)
	{
		MessageBox("请选择图片文件！");
		return;
	}

	PICDLG * pdlg = (PICDLG *) parant;
	CMD cmd;
	
	m_cmd.GetWindowText(str);
	cmd.cmd = str;

	m_title.GetWindowText(str);
	cmd.title = str;

	m_backPic.GetWindowText(str);
	cmd.backpic = str;

	if (m_link.GetCheck() == 1)
	{
		cmd.linkTitle = "网络连线";
	}

	for (list<CString>::iterator iter = m_listPic.begin(); iter != m_listPic.end(); iter++)
	{
		cmd.listpic.push_back(*iter);
	}

	pdlg->g_cmdList.push_back(cmd);

	CDialogEx::OnOK();
}
