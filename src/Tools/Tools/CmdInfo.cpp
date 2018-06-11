// CmdInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Tools.h"
#include "CmdInfo.h"
#include "afxdialogex.h"
#include "message.h"
#include "PICDLG.h"

// CCmdInfo �Ի���

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


// CCmdInfo ��Ϣ�������

BOOL CCmdInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_backPic.SetWindowText("01.bmp");

	return TRUE;
}

//����ͼƬ
void CCmdInfo::OnBnClickedButtonPicLoad()
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
		m_listPic.clear();
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	m_cmd.GetWindowText(str);
	if (str.GetLength() == 0)
	{
		MessageBox("CMD ����Ϊ��");
		return;
	}

	m_title.GetWindowText(str);
	if (str.GetLength() == 0)
	{
		MessageBox("Title ����Ϊ��");
		return;
	}

	if (m_listPic.size() == 0)
	{
		MessageBox("��ѡ��ͼƬ�ļ���");
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
		cmd.linkTitle = "��������";
	}

	for (list<CString>::iterator iter = m_listPic.begin(); iter != m_listPic.end(); iter++)
	{
		cmd.listpic.push_back(*iter);
	}

	pdlg->g_cmdList.push_back(cmd);

	CDialogEx::OnOK();
}
