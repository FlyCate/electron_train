// EmfMsgBox.cpp : 实现文件
//

#include "stdafx.h"
#include "TrainingSYS.h"
#include "EmfMsgBox.h"
#include "afxdialogex.h"
#include "ts_emf_wnd.h"
#include "EmfEditMsg.h"


#define CLOSETIME	3*1000

// EmfMsgBox 对话框

IMPLEMENT_DYNAMIC(EmfMsgBox, CDialog)



EmfMsgBox::EmfMsgBox(CWnd* pParent,bool del_self)
	:CDialog(EmfMsgBox::IDD, pParent)
{
	m_msg = "";
	m_back_imag_name = "res/right.png";
	m_move  = false;
	m_del_self = del_self;
}

EmfMsgBox::EmfMsgBox(string msg,string back_img_name,CWnd* pParent,bool del_self)
	:CDialog(EmfMsgBox::IDD, pParent)
{
	if (msg.length()==0)
	{
		m_msg = "";
		m_back_imag_name = "res/right.png";
	}else
	{
		m_msg = msg;
		m_back_imag_name = back_img_name;
	}
	m_move  = false;
	m_del_self = del_self;
}
EmfMsgBox::EmfMsgBox(bool ok,EFMMESSAGE msg,CWnd* pParent,bool del_self)
	:CDialog(EmfMsgBox::IDD, pParent)
{
	m_efmmsg = msg;
	m_ok = ok;
	if (!ok)
	{
		if (msg.msg.length()==0)
		{
			m_msg = "";
			m_back_imag_name = "res/error.png";
		}else
		{
			m_msg = msg.msg;
			m_back_imag_name = msg.imagpathname;
		}
	}else
	{
		m_msg = "";
		m_back_imag_name = "res/right.png";
	}

	m_move  = false;
	m_del_self = del_self;
}


EmfMsgBox::~EmfMsgBox()
{
}

void EmfMsgBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_EDIT, m_edit_bt);
	DDX_Control(pDX, IDC_BT_EMF_OK, m_ok_bt);
}


BEGIN_MESSAGE_MAP(EmfMsgBox, CDialog)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON_EDIT, &EmfMsgBox::OnBnClickedButtonEdit)
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BT_EMF_OK, &EmfMsgBox::OnBnClickedBtEmfOk)
END_MESSAGE_MAP()


// EmfMsgBox 消息处理程序


BOOL EmfMsgBox::OnInitDialog()
{
	CDialog::OnInitDialog();
// 	CString filepath;
// 	AfxGetModuleFileName(AfxGetInstanceHandle(),filepath);
	CString tmp_filePath = "res\\picture_5\\";
	m_ok_bt.SetSkin(tmp_filePath+"know_normal.bmp",tmp_filePath+"know_down.bmp",tmp_filePath+"know_over.bmp",tmp_filePath+"know_normal.bmp",tmp_filePath+"know_normal.bmp",tmp_filePath+"know_mask.bmp",0,0,0);

	reinitDlg();
	CFileFind fFind;
	if (!fFind.FindFile("res/debug") || m_ok)
	{
		m_edit_bt.ShowWindow(SW_HIDE);
	}

	if (!fFind.FindFile("res/debug") || m_del_self)
	{
	//	SetTimer(1,CLOSETIME,NULL);
	}

	return TRUE; 
}


void EmfMsgBox::OnPaint()
{
	CPaintDC dc(this); // device context for painting
 	if (!m_backBitmap.IsNull())
 		m_backBitmap.BitBlt(dc.GetSafeHdc(),0,0);
//	CDialog::OnPaint();
}


BOOL EmfMsgBox::OnEraseBkgnd(CDC* pDC)
{

	return CDialog::OnEraseBkgnd(pDC);
}


void EmfMsgBox::OnBnClickedButtonEdit()
{
	EmfEditMsg dlg(this);
	dlg.setImage_path(m_efmmsg.imagpathname.c_str());
	dlg.setMsg(m_efmmsg.msg.c_str());
	if (dlg.DoModal()==IDOK )
	{
		string imagepathname = (LPCTSTR)dlg.getImage_path();
		string msg = (LPCTSTR)dlg.getMsg();
		m_msg = msg;
		m_back_imag_name = imagepathname;
		reinitDlg();
		m_efmmsg.imagpathname = imagepathname;
		m_efmmsg.msg = msg;

		ts_emf_wnd::saveMsgList(m_efmmsg);
		ts_emf_wnd::addMsgList(m_efmmsg);
		

	}

}
void EmfMsgBox::reinitDlg()
{
	TRY 
	{
		if(!m_backBitmap.IsNull())
		{
			m_backBitmap.Detach();
		}
		m_backBitmap.Load(m_back_imag_name.c_str());
		int w = m_backBitmap.GetWidth();
		int h = m_backBitmap.GetHeight();
		SetWindowPos(NULL,0,0,w,h,SWP_NOMOVE);

		m_ok_bt.MoveWindow((w-81)/2,h-20-5,81,20);

		if (m_msg.length()>0)
		{
			CDC* pDC = CDC::FromHandle(m_backBitmap.GetDC());
			CRect rect(10,48,w-10,h-35);
			CFont m_pFont;
			m_pFont.CreateFont(20,            // nHeight
				0,                            // nWidth
				0,                            // nEscapement
				0,                            // nOrientation
				FW_NORMAL,                      // nWeight
				FALSE,                        // bItalic
				FALSE,                        // bUnderline
				0,                            // cStrikeOut
				ANSI_CHARSET,                    // nCharSet
				OUT_DEFAULT_PRECIS,            // nOutPrecision
				CLIP_DEFAULT_PRECIS,            // nClipPrecision
				DEFAULT_QUALITY,                // nQuality
				DEFAULT_PITCH | FF_SWISS,        // nPitchAndFamily
				_T("微软雅黑"));                    // lpszFac
			pDC->SelectObject(&m_pFont);
			pDC->SetTextColor(RGB(255,0,0));
			pDC->SetBkMode(TRANSPARENT );
			pDC->DrawText(m_msg.c_str(),-1,rect,/*DT_CENTER |*/ DT_EDITCONTROL | DT_WORDBREAK);
			m_backBitmap.ReleaseDC();
			m_pFont.DeleteObject();

		}

	}
	CATCH (CException, e)
	{
		
	}
	END_CATCH
	Invalidate();
}


void EmfMsgBox::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent==1)
	{
		KillTimer(nIDEvent);
		CDialog::OnCancel();
	}
	CDialog::OnTimer(nIDEvent);
}


void EmfMsgBox::OnMouseMove(UINT nFlags, CPoint point)
{
	if ( m_move && (MK_LBUTTON & nFlags)==MK_LBUTTON )
	{
		POINT tmp_p1;
		tmp_p1.x = point.x;
		tmp_p1.y = point.y;
		ClientToScreen(&tmp_p1);
		point.x = tmp_p1.x;
		point.y = tmp_p1.y;
	//	TRACE("*******%d*****%d*******\n",point.x,point.y);
		int x = point.x-m_startPoint.x;
		int y = point.y-m_startPoint.y;
	//	TRACE("%d,%d\n",x,y);
		CRect winRect;
		GetWindowRect(winRect);
	//	TRACE("--%d--%d-\n",winRect.left,winRect.top);
		winRect.OffsetRect(x,y);
	//	TRACE("==%d==%d-\n",winRect.left,winRect.top);
		MoveWindow(winRect);

		m_startPoint = point;
	}
//	CDialog::OnMouseMove(nFlags, point);
}


void EmfMsgBox::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect clientRect;
	GetClientRect(clientRect);
	CRect rect(0,0,clientRect.Width(),45);
	if (rect.PtInRect(point))
	{
		m_move = true;
		POINT tmp_p1;
		tmp_p1.x = point.x;
		tmp_p1.y = point.y;
		ClientToScreen(&tmp_p1);
		point.x = tmp_p1.x;
		point.y = tmp_p1.y;
		m_startPoint = point;
	
	}
//	CDialog::OnLButtonDown(nFlags, point);
}


void EmfMsgBox::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_move = false;
//	CDialog::OnLButtonUp(nFlags, point);
}


void EmfMsgBox::OnBnClickedBtEmfOk()
{
	OnOK();
}


void EmfMsgBox::OnOK()
{
	CDialog::OnOK();
// 	if (m_del_self)
// 	{
// 		delete this;
// 	}
}


void EmfMsgBox::OnCancel()
{
	CDialog::OnCancel();
// 	if (m_del_self)
// 	{
// 		delete this;
// 	}
}
void EmfMsgBox::showDlg()
{
	ShowWindow(SW_NORMAL);
	SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	
}
void EmfMsgBox::reset(bool ok,EFMMESSAGE msg)
{
	m_efmmsg = msg;
	m_ok = ok;
	if (!ok)
	{
		if (msg.msg.length()==0)
		{
			m_msg = "";
			m_back_imag_name = "res/error.png";
		}else
		{
			m_msg = msg.msg;
			m_back_imag_name = msg.imagpathname;
		}
	}else
	{
		m_msg = "";
		m_back_imag_name = "res/right.png";
	}

	m_move  = false;
	reinitDlg();
	showDlg();
	CFileFind fFind;
	if (!fFind.FindFile("res/debug") || m_del_self)
	{
		KillTimer(1);
		SetTimer(1,CLOSETIME,NULL);
	}
}