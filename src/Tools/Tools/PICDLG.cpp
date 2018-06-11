// PICDLG.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Tools.h"
#include "PICDLG.h"
#include "afxdialogex.h"
#include "ToolsDlg.h"
#include "CmdInfo.h"

// PICDLG �Ի���

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


// PICDLG ��Ϣ�������
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
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
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
	//����Video XML
	TiXmlDocument doc;
	if (!doc.LoadFile(path.GetBuffer()))
		return 1;
	//���Ҹ��ڵ�ʧ��
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

//����
void PICDLG::OnBnClickedButtonNew()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CCmdInfo * pcmd = new CCmdInfo(this);
	if(pcmd->DoModal() == IDOK)
	{
		m_listCmd.InsertItem(0, g_cmdList.back().cmd.GetBuffer());
		GetDlgItem(IDC_BUTTON_WRITE)->EnableWindow(TRUE);
	}
}

//���ͼƬ
void PICDLG::OnBnClickedButtonEditLoad()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString pathName,fileName,fileTitle;

	char* filters = ("BMP Files (*.bmp)|*.bmp|All Files (*.*)|*.*||");

	//����һ������ѡ�����ļ���CFileDialog
	CFileDialog fileDlg(true,NULL,"*.bmp",OFN_ALLOWMULTISELECT | OFN_ENABLESIZING | OFN_HIDEREADONLY,filters);

	//�����Դ�500���ļ�
	fileDlg.m_ofn.nMaxFile = 500 * MAX_PATH;

	char* ch = new TCHAR[fileDlg.m_ofn.nMaxFile];
	fileDlg.m_ofn.lpstrFile = ch;

	//���ڴ������
	ZeroMemory(fileDlg.m_ofn.lpstrFile,sizeof(TCHAR) * fileDlg.m_ofn.nMaxFile);

	//��ʾ�ļ��Ի��򣬻���ļ�������
	if(fileDlg.DoModal() == IDOK)
	{
		//��ȡ��һ���ļ���λ��
		POSITION pos_file;
		pos_file = fileDlg.GetStartPosition();

		//ѭ������ÿ��·���������������
		while(pos_file != NULL)
		{
			//���ļ�·�������������
			pathName = fileDlg.GetNextPathName(pos_file);

			//��ȡ�ļ���
			//���ַ����ĺ�����ǰ�������������'\'�����������'\'�ұߵ��ַ�����Ϊ�ļ���
			int length = pathName.GetLength();     
			for(int i = length -1; i>0;i--)
			{
				if('\\' == pathName. GetAt(i))
				{//�жϵ�ǰ�ַ��Ƿ���'\'
					fileName = pathName.Right(length - i -1);
					break;//����ѭ��
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

//�������б�
//void PICDLG::OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

//���浽�ṹ��
void PICDLG::OnBnClickedButtonSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		m_pCmd->linkTitle = "��������";
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

	MessageBox("�������ݳɹ���");
	GetDlgItem(IDC_BUTTON_WRITE)->EnableWindow(TRUE);
}

void PICDLG::OnBnClickedButtonWrite()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TiXmlDocument * myDoc = new TiXmlDocument;

	//������
	TiXmlElement * RootElement = new TiXmlElement("root");
	myDoc->LinkEndChild(RootElement);

	//��cmdѭ������root
	for (list<CMD>::iterator iter = g_cmdList.begin(); iter != g_cmdList.end(); iter++)
	{
		TiXmlElement * CmdElement = new TiXmlElement("cmd");
		RootElement->LinkEndChild(CmdElement);
		//����cmd����
		CmdElement->SetAttribute("priority", iter->cmd.GetBuffer());
		//��� title
		TiXmlElement * titleElement = new TiXmlElement("title");
		CmdElement->LinkEndChild(titleElement);
		titleElement->SetAttribute("name", iter->title.GetBuffer());
		//��� backpic
		TiXmlElement * backpictureElement = new TiXmlElement("backpicture");
		CmdElement->LinkEndChild(backpictureElement);
		backpictureElement->SetAttribute("name", iter->backpic.GetBuffer());
		//��� picture
		for (list<CString>::iterator picIter = iter->listpic.begin(); picIter != iter->listpic.end(); picIter++)
		{
			TiXmlElement * pic = new TiXmlElement("picture");
			CmdElement->LinkEndChild(pic);
			pic->SetAttribute("name", picIter->GetBuffer());
			pic->SetAttribute("index", "0");
		}
		//��� linkTitle
		if (iter->linkTitle.GetLength() > 0)
		{
			TiXmlElement * link = new TiXmlElement("linktitle");
			CmdElement->LinkEndChild(link);
			link->SetAttribute("name", iter->linkTitle.GetBuffer());
		}
	}

	MoveFile("picture.xml", "picture1.xml");
	myDoc->SaveFile("picture.xml");
	MessageBox("д���ļ��ɹ���");
	GetDlgItem(IDC_BUTTON_WRITE)->EnableWindow(FALSE);
}


//ɾ��cmd
void PICDLG::OnBnClickedButtonDel2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
