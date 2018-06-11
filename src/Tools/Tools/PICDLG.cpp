// PICDLG.cpp : 实现文件
//

#include "stdafx.h"
#include "Tools.h"
#include "PICDLG.h"
#include "afxdialogex.h"
#include "ToolsDlg.h"
#include "CmdInfo.h"

// PICDLG 对话框

IMPLEMENT_DYNAMIC(PICDLG, CDialog)

PICDLG::PICDLG(CWnd* pParent /*=NULL*/)
	: CDialog(PICDLG::IDD, pParent)
{
	m_parant = (void *)pParent;
}

PICDLG::~PICDLG()
{
}

void PICDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listCmd);
	DDX_Control(pDX, IDC_EDIT_EDIT_CMD, m_cmdEdit);
	DDX_Control(pDX, IDC_EDIT_EDIT_TITLE, m_titleEdit);
	DDX_Control(pDX, IDC_EDIT_EDIT_BACK, m_backEdit);
	DDX_Control(pDX, IDC_CHECK_EDIT_LINK, m_linkEdit);
	DDX_Control(pDX, IDC_EDIT_EDIT_PIC, m_picEdit);
}


BEGIN_MESSAGE_MAP(PICDLG, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_NEW, &PICDLG::OnBnClickedButtonNew)
	ON_BN_CLICKED(IDC_BUTTON_EDIT_LOAD, &PICDLG::OnBnClickedButtonEditLoad)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &PICDLG::OnNMClickList1)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &PICDLG::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_WRITE, &PICDLG::OnBnClickedButtonWrite)
	ON_BN_CLICKED(IDC_BUTTON_DEL2, &PICDLG::OnBnClickedButtonDel2)
END_MESSAGE_MAP()


// PICDLG 消息处理程序
BOOL PICDLG::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_pCmd = NULL;
	m_listCmd.DeleteAllItems();
	m_listCmd.InsertColumn(0, "cmd");
	ReadPictureXMl("picture.xml");

	m_cmdEdit.EnableWindow(FALSE);
	m_titleEdit.EnableWindow(FALSE);
	m_backEdit.EnableWindow(FALSE);
	m_linkEdit.EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_EDIT_LOAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_DEL2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_WRITE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_DEL)->ShowWindow(SW_HIDE);

	return TRUE;
}

void PICDLG::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	RECT rect, rect1;
	GetClientRect(&rect);
	m_listCmd.GetClientRect(&rect1);
 	rect1.right = rect1.left + (rect.right-rect.left)/4;
 	rect1.bottom = rect1.top + (rect.bottom-rect.top) - 30;
	m_listCmd.MoveWindow(rect1.left, rect1.top, rect1.right, rect1.bottom);
	GetDlgItem(IDC_BUTTON_NEW)->MoveWindow((rect1.right - rect1.left)/2 - 40 - 10, rect1.bottom + 5, 40, 22);
	//GetDlgItem(IDC_BUTTON_NEW2)->MoveWindow((rect1.right - rect1.left)/2 + 10, rect1.bottom + 5, 40, 22);
	GetDlgItem(IDC_BUTTON_DEL2)->MoveWindow((rect1.right - rect1.left)/2 + 10, rect1.bottom + 5, 40, 22);

	GetDlgItem(IDC_STATIC_INFO)->MoveWindow(rect1.right + 10, 0, 455, 353);

	GetDlgItem(IDC_STATIC_CMD)->GetClientRect(&rect);
	GetDlgItem(IDC_STATIC_CMD)->MoveWindow(rect1.right + 30, rect.top + 25, rect.right-rect.left, rect.bottom-rect.top);
	GetDlgItem(IDC_EDIT_EDIT_CMD)->GetClientRect(&rect);
	GetDlgItem(IDC_EDIT_EDIT_CMD)->MoveWindow(rect1.right + 100, rect.top + 20, 200, 25);

	GetDlgItem(IDC_STATIC_TITLE)->GetClientRect(&rect);
	GetDlgItem(IDC_STATIC_TITLE)->MoveWindow(rect1.right + 30, rect.top + 60, rect.right-rect.left, rect.bottom-rect.top);
	GetDlgItem(IDC_EDIT_EDIT_TITLE)->GetClientRect(&rect);
	GetDlgItem(IDC_EDIT_EDIT_TITLE)->MoveWindow(rect1.right + 100, rect.top + 55, 200, 25);

	GetDlgItem(IDC_STATIC_BACK)->GetClientRect(&rect);
	GetDlgItem(IDC_STATIC_BACK)->MoveWindow(rect1.right + 30, rect.top + 95, rect.right-rect.left, rect.bottom-rect.top);
	GetDlgItem(IDC_EDIT_EDIT_BACK)->GetClientRect(&rect);
	GetDlgItem(IDC_EDIT_EDIT_BACK)->MoveWindow(rect1.right + 100, rect.top + 90, 200, 25);

	GetDlgItem(IDC_STATIC_LINK)->GetClientRect(&rect);
	GetDlgItem(IDC_STATIC_LINK)->MoveWindow(rect1.right + 30, rect.top + 130, rect.right-rect.left, rect.bottom-rect.top);
	GetDlgItem(IDC_CHECK_EDIT_LINK)->GetClientRect(&rect);
	GetDlgItem(IDC_CHECK_EDIT_LINK)->MoveWindow(rect1.right + 100, rect.top + 125, 200, 25);

	GetDlgItem(IDC_STATIC_PIC)->GetClientRect(&rect);
	GetDlgItem(IDC_STATIC_PIC)->MoveWindow(rect1.right + 30, rect.top + 165, rect.right-rect.left, rect.bottom-rect.top);
	GetDlgItem(IDC_EDIT_EDIT_PIC)->GetClientRect(&rect);
	GetDlgItem(IDC_EDIT_EDIT_PIC)->MoveWindow(rect1.right + 100, rect.top + 160, 320, 180);

	GetDlgItem(IDC_BUTTON_EDIT_LOAD)->MoveWindow(rect1.right + 428, rect.top + 160, 25, 22);
	GetDlgItem(IDC_BUTTON_SAVE)->MoveWindow(rect1.right + 300, 357, 60, 22);
	GetDlgItem(IDC_BUTTON_WRITE)->MoveWindow(rect1.right + 380, 357, 60, 22);
}

int PICDLG::ReadPictureXMl(CString path)
{
	//查找Video XML
	TiXmlDocument doc;
	if (!doc.LoadFile(path.GetBuffer()))
		return 1;
	//查找根节点失败
	TiXmlElement* root = doc.FirstChildElement();
	if(root == NULL)
	{	
		doc.Clear();
		return 1;
	}
	for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		CString elemName = elem->Value();
		CString attr;
		attr = elem->Attribute("priority");
		
		CMD cmd;
		cmd.cmd = attr;
		m_listCmd.InsertItem(0, attr.GetBuffer());
		for(TiXmlElement* e1 = elem->FirstChildElement(); e1 != NULL; e1 = e1->NextSiblingElement())
		{  
			string elemName = e1->Value();
			CString name;
			if (elemName =="title")
			{
				name =e1->Attribute("name");
				cmd.title = name;
			}

			if (elemName =="linktitle")
			{
				name =e1->Attribute("name");
				cmd.linkTitle = name;
			}

			if (elemName == "picture")
			{
				name = e1->Attribute("name");
				cmd.listpic.push_back(name);
			}

			if (elemName == "backpicture")
			{
				name = e1->Attribute("name");
				cmd.backpic = name;
			}
		}//end for
		g_cmdList.push_back(cmd);
	}
	doc.Clear();

	return 1;
}

//新添
void PICDLG::OnBnClickedButtonNew()
{
	// TODO: 在此添加控件通知处理程序代码
	CCmdInfo * pcmd = new CCmdInfo(this);
	if(pcmd->DoModal() == IDOK)
	{
		m_listCmd.InsertItem(0, g_cmdList.back().cmd.GetBuffer());
		GetDlgItem(IDC_BUTTON_WRITE)->EnableWindow(TRUE);
	}
}

//浏览图片
void PICDLG::OnBnClickedButtonEditLoad()
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
			m_picEditstr.push_back(fileName);
		}      
	}
	delete[] ch;

	CString str;
	for (list<CString>::iterator iter = m_picEditstr.begin(); iter != m_picEditstr.end(); iter++)
	{
		str += "\"";
		str += *iter;
		str += "\"\r\n";
	}
}

//单击了列表
//void PICDLG::OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
//	// TODO: 在此添加控件通知处理程序代码
//	int nItem = -1;
//
//	LPNMITEMACTIVATE lpNMItemActivate = (LPNMITEMACTIVATE)pNMHDR;
//	if(lpNMItemActivate != NULL)
//	{
//		nItem = lpNMItemActivate->iItem;
//	}
//
//	LV_ITEM lvitem = {0};
//	lvitem.iItem = nItem;
//	lvitem.iSubItem = 0;
//	lvitem.mask = LVIF_TEXT|LVIF_IMAGE|LVIF_PARAM;
//	m_listCmd.GetItem(&lvitem);
//	CString str = *((CString *)lvitem.lParam);
//
//	*pResult = 0;
//}


void PICDLG::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	POSITION ps;
	int nIndex;
	ps=m_listCmd.GetFirstSelectedItemPosition();
	nIndex=m_listCmd.GetNextSelectedItem(ps);
	CString str = m_listCmd.GetItemText(nIndex,0);

	for (list<CMD>::iterator iter = g_cmdList.begin(); iter != g_cmdList.end(); iter++)
	{
		if (str == iter->cmd)
		{
			m_pCmd = &(*iter);
			break;
		}
	}

	if (m_pCmd == NULL) return;

	m_cmdEdit.SetWindowText(m_pCmd->cmd);
	m_titleEdit.SetWindowText(m_pCmd->title);
	m_backEdit.SetWindowText(m_pCmd->backpic);

	str = "";
	m_picEditstr.clear();
	for (list<CString>::iterator iter = m_pCmd->listpic.begin(); iter != m_pCmd->listpic.end(); iter++)
	{
		str += "\"";
		str += *iter;
		str += "\"\r\n";
		m_picEditstr.push_back(*iter);
	}
	m_picEdit.SetWindowText(str);

	if (m_pCmd->linkTitle.GetLength() > 0)
	{
		m_linkEdit.SetCheck(1);
	}
	else
	{
		m_linkEdit.SetCheck(0);
	}

	//m_cmdEdit.EnableWindow(TRUE);
	m_titleEdit.EnableWindow(TRUE);
	m_backEdit.EnableWindow(TRUE);
	m_linkEdit.EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_DEL2)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_EDIT_LOAD)->EnableWindow(TRUE);

	*pResult = 0;
}

//保存到结构体
void PICDLG::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_pCmd == NULL)
	{
		return;
	}

	CString str;
	m_cmdEdit.GetWindowText(str);
	m_pCmd->cmd = str;

	m_titleEdit.GetWindowText(str);
	m_pCmd->title = str;

	m_backEdit.GetWindowText(str);
	m_pCmd->backpic = str;

	if (m_linkEdit.GetCheck() == 1)
	{
		m_pCmd->linkTitle = "网络连线";
	}
	else
	{
		m_pCmd->linkTitle = "";
	}

	m_pCmd->listpic.clear();
	for (list<CString>::iterator iter = m_picEditstr.begin(); iter != m_picEditstr.end(); iter++)
	{
		m_pCmd->listpic.push_back(*iter);
	}

	MessageBox("保存数据成功！");
	GetDlgItem(IDC_BUTTON_WRITE)->EnableWindow(TRUE);
}

void PICDLG::OnBnClickedButtonWrite()
{
	// TODO: 在此添加控件通知处理程序代码
	TiXmlDocument * myDoc = new TiXmlDocument;

	//创建根
	TiXmlElement * RootElement = new TiXmlElement("root");
	myDoc->LinkEndChild(RootElement);

	//将cmd循环加入root
	for (list<CMD>::iterator iter = g_cmdList.begin(); iter != g_cmdList.end(); iter++)
	{
		TiXmlElement * CmdElement = new TiXmlElement("cmd");
		RootElement->LinkEndChild(CmdElement);
		//设置cmd属性
		CmdElement->SetAttribute("priority", iter->cmd.GetBuffer());
		//添加 title
		TiXmlElement * titleElement = new TiXmlElement("title");
		CmdElement->LinkEndChild(titleElement);
		titleElement->SetAttribute("name", iter->title.GetBuffer());
		//添加 backpic
		TiXmlElement * backpictureElement = new TiXmlElement("backpicture");
		CmdElement->LinkEndChild(backpictureElement);
		backpictureElement->SetAttribute("name", iter->backpic.GetBuffer());
		//添加 picture
		for (list<CString>::iterator picIter = iter->listpic.begin(); picIter != iter->listpic.end(); picIter++)
		{
			TiXmlElement * pic = new TiXmlElement("picture");
			CmdElement->LinkEndChild(pic);
			pic->SetAttribute("name", picIter->GetBuffer());
			pic->SetAttribute("index", "0");
		}
		//添加 linkTitle
		if (iter->linkTitle.GetLength() > 0)
		{
			TiXmlElement * link = new TiXmlElement("linktitle");
			CmdElement->LinkEndChild(link);
			link->SetAttribute("name", iter->linkTitle.GetBuffer());
		}
	}

	MoveFile("picture.xml", "picture1.xml");
	myDoc->SaveFile("picture.xml");
	MessageBox("写入文件成功！");
	GetDlgItem(IDC_BUTTON_WRITE)->EnableWindow(FALSE);
}


//删除cmd
void PICDLG::OnBnClickedButtonDel2()
{
	// TODO: 在此添加控件通知处理程序代码
	for (list<CMD>::iterator iter = g_cmdList.begin(); iter != g_cmdList.end(); iter++)
	{
		if (iter->cmd == m_pCmd->cmd)
		{
			g_cmdList.erase(iter);
			break;
		}
	}

	int nItem = m_listCmd.GetSelectionMark();
	m_listCmd.DeleteItem(nItem);

	m_pCmd = NULL;
	m_cmdEdit.SetWindowText("");
	m_titleEdit.SetWindowText("");
	m_backEdit.SetWindowText("");
	m_linkEdit.SetCheck(0);
	m_picEditstr.clear();
	m_picEdit.SetWindowText("");

	m_cmdEdit.EnableWindow(FALSE);
	m_titleEdit.EnableWindow(FALSE);
	m_backEdit.EnableWindow(FALSE);
	m_linkEdit.EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_EDIT_LOAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_DEL2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(FALSE);

	GetDlgItem(IDC_BUTTON_WRITE)->EnableWindow(TRUE);
}
