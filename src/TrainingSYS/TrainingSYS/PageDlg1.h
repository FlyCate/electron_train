#pragma once
using namespace std;
#include "tinyxml.h"
#include <vector>
#include "afxwin.h"
#include "xSkinButton.h"
#define  XML_PICTUREINF		"res/picture.xml"
#define  XML_OPTIONTUREINF	"res/option.xml"
#define  PICTURE_4_LEVEL     "\\res\\picture_4\\"  

//ͼƬ��Ϣ
typedef struct  _PIC_INF_
{   
	CString  bmpname;	//ͼƬ����
	byte     order;		//ͼƬ����˳������
	_PIC_INF_()
	{
		bmpname   ="";
		order     = 0xff;
	};
} PIC_INF,*PPIC_INF;
typedef struct  _PIC_INF_ALL
{   
	vector<PIC_INF>  piclist;	//����Ҫ���ص�ͼƬ����
	CString  path;				//ͼƬ·��
	CBitmap 		 *bmp;		//����λͼʹ��
	byte			 num;       //��Ҫ���ص�ͼƬ����
	CString          bkpic;

	_PIC_INF_ALL()
	{
		piclist.clear();
		bmp =NULL;
		num = 0 ;
		path = "";
	};
} PIC_INF_ALL,*PPIC_INF_ALL;

//ѡ����Ϣ
typedef struct  _OPT_INF_
{   
	CString  optname;		   //ѡ����������
	CString  explain;		   //ѡ���Ӧ��ʾ��Ϣ
	byte	 order;			   //ѡ��˳������
	_OPT_INF_()
	{
		explain   ="";
		optname   ="";
		order     = 0xff;
	};
} OPT_INF,*POPT_INF;
//һ��ѡ����ṹ
typedef struct  _OPT_INF_ALL
{   
	CString option;				//ѡ�����
	byte  num;					//��Ҫ����ѡ��ĸ���
	byte  answer;				//��ȷѡ�������
	vector<OPT_INF>	 optlist;	//ѡ����Ϣ����
	_OPT_INF_ALL()
	{
		option = "";
		optlist.clear();
		num     = 0;
		answer  =	0xff;
	};
} OPT_INF_ALL,*POPT_INF_ALL;
//�����ѡ����ṹ
typedef struct  _MUL_OPT_INF_ALL
{   
	vector<OPT_INF_ALL>	 moptlist;
	int num ;
	CString mainstr;//���ѡ����Ĵ����
	_MUL_OPT_INF_ALL()
	{
	  moptlist.clear();
	  num =0;
	  mainstr = "";
	};
} MUL_OPT_INF_ALL,*PMUL_OPT_INF_ALL;



//�Ի�����Ϣ
typedef struct  _PAGE_INF_
{
	_PAGE_INF_(void)
	{
		runpath = "";
		cmd = "";
	};
	CString          runpath;//��������·��
	CString          cmd;    //��ǰ��Ӧ���ڵ�����
	PIC_INF_ALL  pic;	//ͼƬ��Ϣ
	MUL_OPT_INF_ALL	 opt;	//ѡ����Ϣ
	
	//vector<BACK_INF> backlist;	//�������ݼ���
}PAGE_INF,*PPAGE_INF;

// PageDlg1 �Ի���
class CTrainingSYSDlg;
class PageDlg1 : public CDialogEx
{
	DECLARE_DYNAMIC(PageDlg1)

public:
	PageDlg1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PageDlg1();

// �Ի�������
	enum { IDD = IDD_DLG_PAGE1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();

	PAGE_INF m_pageinf;
	CTrainingSYSDlg *parent ;
	// ��ȡxml�б����ͼƬ��Ϣ
	int ReadXMlPictureInfmation(CString cmd);
	// ��ȡxml�б����ѡ����Ϣ
	int ReadXMlOptionInfmation(CString cmd);
	// ��ȡXML�б����ѡ��������Ժ�������ʾ�б�ʹ��
	int ReadXMlAnswerName(CString cmd);
	// ��ȡXML�б����TABPAGE1������
	
	byte CheckHowMangPages();
	virtual BOOL OnInitDialog();

	
	CButton* NewMyButton(int nID,CRect rect,int nStyle,CString m_Caption);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMybuttonOK();
	afx_msg void OnMybuttonNEXT();
	afx_msg void OnMybuttonBACK();

	void ReMoveButton() ;
	byte m_index;//��ǰҳ������������һҳ����

	void DrawBmp(CString name);
	int m_timeid;//��ʱ�����ڿ���ͼƬ��ҳ����Ч��
	CxSkinButton m_btn_back;
	CxSkinButton m_btn_next;
	CxSkinButton m_btn_ok;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void DrawBmp(CString name ,bool dir,int mul);
	bool m_isover;//�����Ƿ������
	int  m_multiple;//�Ŵ���
	bool  m_dir; //true ��һҳ false ��һҳ
	void OnInitButton();
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
