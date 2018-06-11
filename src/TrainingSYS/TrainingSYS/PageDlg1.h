#pragma once
using namespace std;
#include "tinyxml.h"
#include <vector>
#include "afxwin.h"
#include "xSkinButton.h"
#define  XML_PICTUREINF		"res/picture.xml"
#define  XML_OPTIONTUREINF	"res/option.xml"
#define  PICTURE_4_LEVEL     "\\res\\picture_4\\"  

//图片信息
typedef struct  _PIC_INF_
{   
	CString  bmpname;	//图片名称
	byte     order;		//图片加载顺序索引
	_PIC_INF_()
	{
		bmpname   ="";
		order     = 0xff;
	};
} PIC_INF,*PPIC_INF;
typedef struct  _PIC_INF_ALL
{   
	vector<PIC_INF>  piclist;	//框需要加载的图片集合
	CString  path;				//图片路径
	CBitmap 		 *bmp;		//加载位图使用
	byte			 num;       //需要加载的图片数量
	CString          bkpic;

	_PIC_INF_ALL()
	{
		piclist.clear();
		bmp =NULL;
		num = 0 ;
		path = "";
	};
} PIC_INF_ALL,*PPIC_INF_ALL;

//选项信息
typedef struct  _OPT_INF_
{   
	CString  optname;		   //选项内容名称
	CString  explain;		   //选项对应提示信息
	byte	 order;			   //选项顺序索引
	_OPT_INF_()
	{
		explain   ="";
		optname   ="";
		order     = 0xff;
	};
} OPT_INF,*POPT_INF;
//一道选择题结构
typedef struct  _OPT_INF_ALL
{   
	CString option;				//选项卡名称
	byte  num;					//需要加载选项的个数
	byte  answer;				//正确选项答案索引
	vector<OPT_INF>	 optlist;	//选项信息集合
	_OPT_INF_ALL()
	{
		option = "";
		optlist.clear();
		num     = 0;
		answer  =	0xff;
	};
} OPT_INF_ALL,*POPT_INF_ALL;
//多道道选择题结构
typedef struct  _MUL_OPT_INF_ALL
{   
	vector<OPT_INF_ALL>	 moptlist;
	int num ;
	CString mainstr;//多道选择题的大标题
	_MUL_OPT_INF_ALL()
	{
	  moptlist.clear();
	  num =0;
	  mainstr = "";
	};
} MUL_OPT_INF_ALL,*PMUL_OPT_INF_ALL;



//对话框信息
typedef struct  _PAGE_INF_
{
	_PAGE_INF_(void)
	{
		runpath = "";
		cmd = "";
	};
	CString          runpath;//程序运行路径
	CString          cmd;    //当前对应窗口的命令
	PIC_INF_ALL  pic;	//图片信息
	MUL_OPT_INF_ALL	 opt;	//选项信息
	
	//vector<BACK_INF> backlist;	//返回内容集合
}PAGE_INF,*PPAGE_INF;

// PageDlg1 对话框
class CTrainingSYSDlg;
class PageDlg1 : public CDialogEx
{
	DECLARE_DYNAMIC(PageDlg1)

public:
	PageDlg1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PageDlg1();

// 对话框数据
	enum { IDD = IDD_DLG_PAGE1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();

	PAGE_INF m_pageinf;
	CTrainingSYSDlg *parent ;
	// 读取xml中保存的图片信息
	int ReadXMlPictureInfmation(CString cmd);
	// 读取xml中保存的选项信息
	int ReadXMlOptionInfmation(CString cmd);
	// 读取XML中保存的选项的名称以后用于显示列表使用
	int ReadXMlAnswerName(CString cmd);
	// 读取XML中保存的TABPAGE1的名称
	
	byte CheckHowMangPages();
	virtual BOOL OnInitDialog();

	
	CButton* NewMyButton(int nID,CRect rect,int nStyle,CString m_Caption);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMybuttonOK();
	afx_msg void OnMybuttonNEXT();
	afx_msg void OnMybuttonBACK();

	void ReMoveButton() ;
	byte m_index;//当前页面索引，用下一页控制

	void DrawBmp(CString name);
	int m_timeid;//定时器用于控制图片翻页动画效果
	CxSkinButton m_btn_back;
	CxSkinButton m_btn_next;
	CxSkinButton m_btn_ok;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void DrawBmp(CString name ,bool dir,int mul);
	bool m_isover;//动画是否加载中
	int  m_multiple;//放大倍数
	bool  m_dir; //true 下一页 false 上一页
	void OnInitButton();
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
