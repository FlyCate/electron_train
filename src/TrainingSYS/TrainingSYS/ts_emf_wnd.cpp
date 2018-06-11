// ts_emf_wnd.cpp : 实现文件
//

#include "stdafx.h"
#include "TrainingSYS.h"
#include "ts_emf_wnd.h"

#include "tinyxml.h"
#include "EmfMsgBox.h"

#define  RS485_EMFFILE_PATH  "res/rs485.emf"
#define  R433_EMFFILE_PATH  "res/433.emf"
#define  ZIGBEE_EMFFILE_PATH  "res/zigbee.emf"
#define  WIFI_EMFFILE_PATH  "res/wifi.emf"

#define  POINTSCONFIG_FILEPATH	"res/points.xml"
#define  LINECONFIG_FILEPATH	"res/lines.xml"
#define  EMF_MSG_FILEPATH "res/emf_msg.xml"

#define  MAX_SCAL	5.0f
#define  MIN_SCAL	0.2f
#define STEP_SIZE	0.06f

#define HOTPOINT_RADIUS		8	//热点半径

//轮询100ms 轮询30次  每次减1 当减为0 认为线不存在
#define HIDELINE_TOTAL		30		// 轮询次数
#define HIDEINT				100		//轮询间隔 单位毫秒

//错误连线轮询监测，时间：200ms，轮休7次，每次减1，当减为0时，认为错误消失。
#define  SHOWDLG_TOTAL		7
#define  SHOWDLG_INT		200

#define WM_LINKLINE WM_USER+1000

EFMMESSAGELIST ts_emf_wnd::msg_list;
// ts_emf_wnd

IMPLEMENT_DYNAMIC(ts_emf_wnd, CWnd)
ts_emf_wnd::ts_emf_wnd(CWnd* pParent /*=NULL*/)
//ts_emf_wnd::ts_emf_wnd()
{
	m_hemf = NULL;
	m_scal = 0.5f;
	m_is_move = false;
	m_mode = 1;
}

ts_emf_wnd::~ts_emf_wnd()
{
	vector<POINT_INFO*>::iterator piter = m_points.begin();
	while(piter!=m_points.end())
	{
		delete (*piter);
		piter++;
	}
	m_points.clear();

	vector<LINE_INFO*>::iterator liter = m_lines.begin();
	while(liter!=m_lines.end())
	{
		if ((*liter)->m_p_size>0)
			delete [](*liter)->m_p;
		delete (*liter);
		liter++;
	}
	m_lines.clear();

	m_memBakBitmap.DeleteObject();
	m_memBakDC.DeleteDC();

	m_memBitmap.DeleteObject();
	m_memDC.DeleteDC();

	DeleteEnhMetaFile(m_rs485_hemf);
	DeleteEnhMetaFile(m_wifi_hemf);
	DeleteEnhMetaFile(m_zigbee_hemf);
	DeleteEnhMetaFile(m_433_hemf);

}


BEGIN_MESSAGE_MAP(ts_emf_wnd, CWnd)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_MESSAGE(WM_LINKLINE, doLinkLineMsg)
	ON_WM_KEYDOWN()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()



// ts_emf_wnd 消息处理程序




BOOL ts_emf_wnd::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	
	BOOL r = CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
	init_line_point();
	init_emf();
	return r;
}


// 初始化emf文件
bool ts_emf_wnd::init_emf(void)
{
	ASSERT(IsWindow(GetSafeHwnd()));
	m_rs485_hemf= GetEnhMetaFile(RS485_EMFFILE_PATH);
	m_zigbee_hemf= GetEnhMetaFile(ZIGBEE_EMFFILE_PATH);
	m_433_hemf= GetEnhMetaFile(R433_EMFFILE_PATH);
	m_wifi_hemf= GetEnhMetaFile(WIFI_EMFFILE_PATH);
	m_memDC.CreateCompatibleDC(GetDC());
	m_memBakDC.CreateCompatibleDC(GetDC());
	setEmfType(m_emf_type);
	return true;
}


LRESULT ts_emf_wnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CWnd::WindowProc(message, wParam, lParam);
}


void ts_emf_wnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// 不为绘图消息调用 CWnd::OnPaint()
	CRect clientrect;
	GetClientRect(&clientrect);

	int w = m_emf_w*m_scal;
	int h = m_emf_h*m_scal;

	int dstx  = 0;
	int dsty = 0;
	int dstw = clientrect.Width();
	int dsth = clientrect.Height();


	if (m_emf_left>0)
	{
		m_emf_left = 0;
		dstx = m_emf_left;

	}
	if (m_emf_top>0)
	{
		m_emf_top = 0;
		dsty = m_emf_top;
	}

	if (m_emf_left+w<dstw)
	{
		m_emf_left = dstw-w;
	}

	if (m_emf_top+h<dsth)
	{
		m_emf_top = dsth-h;
	}

	int srcx = -m_emf_left;
	int srcy = -m_emf_top;

	//dc.BitBlt(dstx,dsty,dstw,dsth,&m_memDC,srcx,srcy,SRCCOPY);
	dc.BitBlt(0,0,clientrect.Width(),clientrect.Height(),&m_memDC,srcx,srcy,SRCCOPY);
}


void ts_emf_wnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	if (IsWindow(GetSafeHwnd()))
	{

	}
}
void ts_emf_wnd::init_line_point()
{
	//从配置文件中获得点信息
	TiXmlDocument doc;
	if (doc.LoadFile(POINTSCONFIG_FILEPATH))
	{
		TiXmlElement* rootE = doc.FirstChildElement("system");
		if (rootE)
		{
			TiXmlElement* pointE = rootE->FirstChildElement("point");
			while (pointE)
			{
				POINT_INFO *point_info = new POINT_INFO;
				const char *tmp_str = pointE->Attribute("name");
				if (tmp_str)
				{
					point_info->point_name = tmp_str;
				}
				tmp_str = pointE->Attribute("p");
				if (tmp_str)
				{
					char tmp_str2[128];
					strcpy_s(tmp_str2,tmp_str);
					char *p = strtok(tmp_str2,",");
					if (p)
					{
						point_info->start_p.x = atoi(p);
					}
					p = strtok(NULL,",");
					if (p)
					{
						point_info->start_p.y = atoi(p);
					}
				}
				m_points.push_back(point_info);
				pointE = pointE->NextSiblingElement("point");
			}
		}
	}
	if (doc.LoadFile(LINECONFIG_FILEPATH))
	{
		TiXmlElement* rootE = doc.FirstChildElement("system");
		if (rootE)
		{
			TiXmlElement* lineE = rootE->FirstChildElement("line");
			while (lineE)
			{
				LINE_INFO *pline =  new LINE_INFO;
				pline->line_name = lineE->Attribute("name");
				string points = lineE->Attribute("point_name");
				vector<string> ps = split(points,",");
				pline->p1_name = ps[0];
				pline->p2_name = ps[1];
				const char * tmp_char = lineE->Attribute("points");
				if (tmp_char)
				{

					ps = split(lineE->Attribute("points"),";");
					pline->m_p_size = ps.size();
					pline->m_p = new POINT[pline->m_p_size];
					for (int i=0;i<pline->m_p_size;i++)
					{
						vector<string> ps2 = split(ps[i],",");
						pline->m_p[i].x = atoi(ps2[0].c_str());
						pline->m_p[i].y = atoi(ps2[1].c_str());
					}
				}else
					pline->m_p_size = 0;
				pline->is_yellow = atoi(lineE->Attribute("yellow"));
				m_lines.push_back(pline);
				lineE = lineE->NextSiblingElement("line");
			}
		
		}
	}

	if (doc.LoadFile(EMF_MSG_FILEPATH))
	{
		TiXmlElement* rootE = doc.FirstChildElement("system");
		if (rootE)
		{
			TiXmlElement* lineE = rootE->FirstChildElement("emf_msg");
			while (lineE)
			{
				EFMMESSAGE msg;
				msg.msg = lineE->Attribute("msg");
				msg.imagpathname = lineE->Attribute("image");

				vector<string> ps = split(lineE->Attribute("points"),",");

				msg.p1_name = ps[0];
				msg.p2_name = ps[1];
				msg_list.push_back(msg);
				lineE = lineE->NextSiblingElement("emf_msg");
			}

		}
	}
	printf_s("读取xml结束\n");
}

void ts_emf_wnd::OnRButtonDown(UINT nFlags, CPoint point)
{
	SetFocus();
	m_is_move = true;
	m_move_start = point;
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_HAND ));
	CWnd::OnRButtonDown(nFlags, point);
}


void ts_emf_wnd::OnRButtonUp(UINT nFlags, CPoint point)
{
	m_is_move = false;
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS ));
	CWnd::OnRButtonUp(nFlags, point);
	SetFocus();
}


BOOL ts_emf_wnd::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	//pt点的坐标相对于屏幕左上角
	CPoint tmp_p = pt;

//	CWnd *MainWnd  = AfxGetApp()->GetMainWnd();
//	MainWnd->ClientToScreen(&tmp_p);
	::ScreenToClient(GetSafeHwnd(),&tmp_p);
	CRect clientrect;
	GetClientRect(&clientrect);
	if ( !clientrect.PtInRect(tmp_p))
	{
		return CWnd::OnMouseWheel(nFlags, zDelta, pt);
	}
	double left = (tmp_p.x-m_emf_left)/m_scal;
	double top  = (tmp_p.y-m_emf_top)/m_scal;

	double tmp_scal = m_scal;
	if (zDelta>0)
	{
		m_scal += STEP_SIZE;
	}else
	{
		m_scal -= STEP_SIZE;
	}

	if (m_scal<MIN_SCAL)
	{
		m_scal=MIN_SCAL;
	}
	if (m_scal>MAX_SCAL)
	{
		m_scal=MAX_SCAL;
	}
	if (m_emf_w*m_scal<clientrect.Width() || m_emf_h*m_scal<clientrect.Height())
	{
		//计算最小的比例
		double scal_w = ((double)clientrect.Width()/m_emf_w);
		double scal_h = ((double)clientrect.Height()/m_emf_h);
		m_scal = scal_w>scal_h?scal_w:scal_h;
	}
	m_emf_left = -(left*m_scal-tmp_p.x);
	m_emf_top = -(top*m_scal-tmp_p.y);

	KillTimer(1);
	SetTimer(1,300,NULL);		//延迟缩放
	SetFocus();
	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}





BOOL ts_emf_wnd::CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, LPVOID lpParam)
{

	BOOL r=  CWnd::CreateEx(dwExStyle, lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, lpParam);
	init_line_point();
	init_emf();
//	SetTimer(4,200,NULL); //测试使用
	return r;
}


BOOL ts_emf_wnd::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	return true;
	return CWnd::OnEraseBkgnd(pDC);
}


void ts_emf_wnd::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
//	this->ModifyStyle(NULL, BS_OWNERDRAW);
	CWnd::PreSubclassWindow();
}
BOOL ts_emf_wnd::Create(CWnd *parent,int emf_type)
{
	m_emf_type  = emf_type;
	return CreateEx(0,   AfxRegisterWndClass(0/*CS_VREDRAW|CS_HREDRAW*/,AfxGetApp()->LoadStandardCursor(IDC_CROSS), 
		(HBRUSH) ::GetStockObject(WHITE_BRUSH),NULL),     _T ("emf_windows "),  WS_VISIBLE|WS_CHILDWINDOW /*WS_OVERLAPPEDWINDOW */,  CRect(0,0,600,400),parent,   0); 
}


BOOL ts_emf_wnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{

	if (m_is_move)
	{
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_HAND ));
		return TRUE;
	}
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}


void ts_emf_wnd::OnMouseMove(UINT nFlags, CPoint point)
{
	if ((nFlags & MK_RBUTTON)==MK_RBUTTON )
	{
		m_move_end = point;

		double left = m_emf_left;
		double top = m_emf_top;

		left += m_move_end.x-m_move_start.x;
		top += m_move_end.y-m_move_start.y;
		m_move_start = point;

		int emf_w = m_emf_w*m_scal+0.5;
		int emf_h = m_emf_h*m_scal+0.5;

		CRect r1(left,top,left+emf_w,top+emf_h);
		CRect r2;
		GetClientRect(r2);
		CRect r3;
		r3 = r1&r2;
		if (r3==r1 || r3==r2) //相互包容
		{
			m_emf_left = left;
			m_emf_top = top;
			Invalidate();
		}

	}

//	CWnd::OnMouseMove(nFlags, point);
}


void ts_emf_wnd::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CWnd::OnMouseHover(nFlags, point);
}


void ts_emf_wnd::OnMouseLeave()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_is_move = false;
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS ));
	CWnd::OnMouseLeave();
}


void ts_emf_wnd::reinit_memDC(void)
{
	int bitmapw = m_emf_w*m_scal+5;
	int bitmaph = m_emf_h*m_scal+5;

	m_memBitmap.DeleteObject();
	m_memBitmap.CreateCompatibleBitmap(GetDC(),bitmapw,bitmaph);
	m_memDC.SelectObject(m_memBitmap);

	m_memBakBitmap.DeleteObject();
	m_memBakBitmap.CreateCompatibleBitmap(GetDC(),bitmapw,bitmaph);
	m_memBakDC.SelectObject(m_memBakBitmap);


	CRect rect;
	rect.top = 0;
	rect.left = 0;
	rect.bottom = bitmaph;
	rect.right = bitmapw;
	CBrush *brush = new CBrush(RGB(255,255,255)) ;
	m_memDC.FillRect(&rect,brush);
	brush->DeleteObject();
	delete brush;
	rect.top = 0;
	rect.left = 0;
	rect.bottom =m_emf_h*m_scal;
	rect.right = m_emf_w*m_scal;
	PlayEnhMetaFile(m_memDC.GetSafeHdc(), m_hemf, &rect); 
	m_memBakDC.BitBlt(0,0,bitmapw,bitmaph,&m_memDC,0,0,SRCCOPY);
	reDraw();

}


void ts_emf_wnd::OnLButtonUp(UINT nFlags, CPoint point)
{

	if (m_mode!=1) return; //非手动模式
	int x = point.x-m_emf_left;
	int y = point.y-m_emf_top;
	x = x/m_scal;
	y = y/m_scal;
	
	POINT_INFO *clickP = click_hot_point(x,y);

	if (clickP)
	{
		m_showing_points.push_back(clickP);
		reDraw(clickP);
	}

	if (m_showing_points.size()==2)
	{
		//查找连接线
		bool exist_line = false;
		LINE_INFO *line = getLine(m_showing_points[0]->point_name,m_showing_points[1]->point_name);
		if (line)
		{
			exist_line = existLine(m_showing_points[0]->point_name,m_showing_points[1]->point_name);
			if (!exist_line)
			{
				m_showing_lines.push_back(line);
				drawLine(line);
			}

		}
		if (!exist_line)
			showMsgDlg(line,getEfmMsg(m_showing_points[0]->point_name,m_showing_points[1]->point_name));
	
		clear(m_showing_points[0]);
		clear(m_showing_points[1]);
		m_showing_points.clear();
		
	}
//	CWnd::OnLButtonUp(nFlags, point);
	SetFocus();
}

bool ts_emf_wnd::existLine(string p1_name,string p2_name)
{
	vector<LINE_INFO*>::iterator iter = m_showing_lines.begin();
	while (iter!=m_showing_lines.end())
	{
		LINE_INFO *tmp_line = (*iter);
		if ((((tmp_line->p1_name==p1_name) && (tmp_line->p2_name==p2_name)) ||
			((tmp_line->p1_name==p2_name) && (tmp_line->p2_name==p1_name))) )
		{
			return true;
		}

		iter++;
	}
	return false;
}
POINT_INFO * ts_emf_wnd::click_hot_point(int x, int y)
{

	vector<POINT_INFO*>::iterator it = m_points.begin();
	POINT click_p = {x,y};
	while(it!=m_points.end())
	{
		POINT_INFO *p = *it;
		CRect rect( p->start_p.x-HOTPOINT_RADIUS,p->start_p.y-HOTPOINT_RADIUS,p->start_p.x+HOTPOINT_RADIUS,p->start_p.y+HOTPOINT_RADIUS);
		if (rect.PtInRect(click_p))
		{
			return p;
		}
		it++;
	}
	return NULL;
}

void ts_emf_wnd::setEmfType(int type)
{
	m_emf_type = type;
	if (type==1)
	{
		m_hemf = m_rs485_hemf;

	}else if (type==2)
	{
		m_hemf = m_433_hemf;
	}
	else if (type==3)
	{
		m_hemf = m_zigbee_hemf;
	}
	else
	{
		m_hemf = m_wifi_hemf;
	}
	m_scal = 0.5f;
	if (m_hemf)
	{
		GetEnhMetaFileHeader(m_hemf,sizeof(ENHMETAHEADER),&m_emheader);
		UINT plaetteNum = GetEnhMetaFilePaletteEntries(m_hemf,10,NULL);

		m_emf_w = m_emheader.rclBounds.right-m_emheader.rclBounds.left;
		m_emf_h = m_emheader.rclBounds.bottom-m_emheader.rclBounds.top;


		int bitmapw = m_emf_w*m_scal+5;
		int bitmaph = m_emf_h*m_scal+5;

		m_memBitmap.DeleteObject();
		m_memBitmap.CreateCompatibleBitmap(GetDC(),bitmapw,bitmaph);
		m_memDC.SelectObject(m_memBitmap);

		m_memBakBitmap.DeleteObject();
		m_memBakBitmap.CreateCompatibleBitmap(GetDC(),bitmapw,bitmaph);
		m_memBakDC.SelectObject(m_memBakBitmap);


		CRect rect;
		rect.top = 0;
		rect.left = 0;
		rect.bottom =bitmaph;
		rect.right = bitmapw;
		CBrush pb;
		pb.Attach(GetStockObject(WHITE_BRUSH));
		m_memDC.FillRect(&rect,&pb);
		pb.DeleteObject();
		rect.top = 0;
		rect.left = 0;
		rect.bottom =m_emf_h*m_scal;
		rect.right = m_emf_w*m_scal;
		m_memDC.SetBkColor(RGB(255,255,255));
		m_memDC.SetDCPenColor(RGB(255,255,255));
		PlayEnhMetaFile(m_memDC.GetSafeHdc(), m_hemf, &rect); 
		m_memBakDC.BitBlt(0,0,bitmapw,bitmaph,&m_memDC,0,0,SRCCOPY);
		CRect rect1;
		GetClientRect(&rect1);
		m_emf_left = rect1.Width()/2-m_emf_w*m_scal/2;
		m_emf_top = rect1.Height()/2-m_emf_h*m_scal/2;
		reDraw();
	}

}


void ts_emf_wnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetFocus();

//	CWnd::OnLButtonDown(nFlags, point);
}
vector<string> ts_emf_wnd::split(string str,string pattern)
{
	 string::size_type pos;
	 vector< string> result;
	 if (str.length()==0 || pattern.length()==0 )
		 return result;
	 if (str.substr(str.length()-pattern.length(),pattern.length())!=pattern)
	 {
		 str+=pattern;//扩展字符串以方便操作
	 }
	 else
	 {
	 }
	
	int size=str.size();

	for(int i=0; i<size; i++)
	{
		pos=str.find(pattern,i);
		if(pos<size)
		{
			 string s=str.substr(i,pos-i);
			result.push_back(s);
			i=pos+pattern.size()-1;
		}
	}
	return result;
}

void ts_emf_wnd::reDraw()
{
	
	int bitmapw = m_emf_w*m_scal+5;
	int bitmaph = m_emf_h*m_scal+5;

	m_memDC.BitBlt(0,0,bitmapw,bitmaph,&m_memBakDC,0,0,SRCCOPY);

	//画点
	CBrush brush(RGB(255,0,0));
	CPen pen(PS_SOLID,1,RGB(255,0,0));
	CBrush *oldBrush =  m_memDC.SelectObject(&brush);
	CPen *oldpen =  m_memDC.SelectObject(&pen);
//	m_showing_points = m_points;
	vector<POINT_INFO*> ::iterator iter = m_showing_points.begin();
	while (iter != m_showing_points.end())
	{
		int x = (*iter)->start_p.x;
		int y = (*iter)->start_p.y;
		x = x*m_scal+0.5;
		y = y*m_scal+0.5;
		int r = HOTPOINT_RADIUS*m_scal+0.5;

		m_memDC.Ellipse(x-r,y-r,x+r,y+r);

		iter++;
	}
	m_memDC.SelectObject(oldBrush);
	m_memDC.SelectObject(oldpen);
	//画线
//	m_showing_lines = m_lines;
	vector<LINE_INFO*> ::iterator iter1 = m_showing_lines.begin();
	CPen pen2(PS_SOLID,1,RGB(255,0,0));
	oldpen = m_memDC.SelectObject(&pen2);
	while (iter1!=m_showing_lines.end())
	{
		vector<POINT> ps = getPoints((*iter1));
		for (int i=0;i<ps.size()-1;i++)
		{
			int x1 = ps[i].x*m_scal+0.5;
			int y1 = ps[i].y*m_scal+0.5;

			int x2 = ps[i+1].x*m_scal+0.5;
			int y2 = ps[i+1].y*m_scal+0.5;
			m_memDC.MoveTo(x1,y1);
			m_memDC.LineTo(x2,y2);
		}
		iter1++;


	}
	m_memDC.SelectObject(oldpen);
	Invalidate();
}

void ts_emf_wnd::reDraw(POINT_INFO *p)
{
	CBrush brush(RGB(255,0,0));
	CBrush *oldBrush =  m_memDC.SelectObject(&brush);

	int x = p->start_p.x;
	int y = p->start_p.y;
	x = x*m_scal+0.5;
	y = y*m_scal+0.5;
	int r = HOTPOINT_RADIUS*m_scal+0.5;

	m_memDC.Ellipse(x-r,y-r,x+r,y+r);

	m_memDC.SelectObject(oldBrush);
	
	Invalidate();
}

void ts_emf_wnd::clear(POINT_INFO *p)
{

	int r = (HOTPOINT_RADIUS*m_scal+0.5);
	int x = (p->start_p.x*m_scal+0.5);
	int y = (p->start_p.y*m_scal+0.5);


	m_memDC.BitBlt(x-r,y-r,2*r,2*r,&m_memBakDC,x-r,y-r,SRCCOPY);
	Invalidate();


}

void ts_emf_wnd::drawLine(LINE_INFO *line)
{
	vector<POINT> ps = getPoints(line);
	for (int i=0;i<ps.size()-1;i++)
	{
		int x1 = ps[i].x*m_scal+0.5;
		int y1 = ps[i].y*m_scal+0.5;

		int x2 = ps[i+1].x*m_scal+0.5;
		int y2 = ps[i+1].y*m_scal+0.5;
		CPen pen2(PS_SOLID,3,RGB(255,0,0));
		CPen *oldpen = m_memDC.SelectObject(&pen2);
		m_memDC.MoveTo(x1,y1);
		m_memDC.LineTo(x2,y2);
		m_memDC.SelectObject(oldpen);

	}
	Invalidate();
}
vector<POINT> ts_emf_wnd::getPoints(LINE_INFO *line)
{
	vector<POINT> tmp_ps;
	tmp_ps.push_back(getPoint(line->p1_name));
	for (int i=0;i<line->m_p_size;i++)
	{
		tmp_ps.push_back(line->m_p[i]);
	}
	tmp_ps.push_back(getPoint(line->p2_name));
	return tmp_ps;
}

POINT ts_emf_wnd::getPoint(string point_name)
{
	vector<POINT_INFO*>::iterator iter = m_points.begin();
	while (iter!=m_points.end())
	{
		if ((*iter)->point_name==point_name)
		{
			return (*iter)->start_p;
		}
		iter++;
	}
 	POINT p;
 	p.x = 0;
 	p.y = 0;
	return p;
}

LINE_INFO *ts_emf_wnd::getLine(string p1_name,string p2_name)
{
	vector<LINE_INFO*>::iterator iter = m_lines.begin();
	while(iter!=m_lines.end())
	{
		LINE_INFO *tmp_line = (*iter);
		if ((((tmp_line->p1_name==p1_name) && (tmp_line->p2_name==p2_name)) ||
			((tmp_line->p1_name==p2_name) && (tmp_line->p2_name==p1_name))) )
		{
			if (!tmp_line->is_yellow)
			{
				return tmp_line;
			}else if (m_emf_type==1 && tmp_line->is_yellow)
			{
				return tmp_line;
			}
		}
		iter++;
	}
	return NULL;
}
bool ts_emf_wnd::saveMsgList(EFMMESSAGE efm_msg)
{
	TiXmlDocument doc;
	if (doc.LoadFile(EMF_MSG_FILEPATH))
	{
		TiXmlElement* rootE = doc.FirstChildElement("system");
		if (rootE)
		{
			TiXmlElement* pointE = rootE->FirstChildElement("emf_msg");
			while (pointE)
			{

				string psname = pointE->Attribute("points");

				vector<string> ps = split(psname,",");
				if ( (ps[0]==efm_msg.p1_name && ps[1]==efm_msg.p2_name ) ||
					(ps[1]==efm_msg.p1_name && ps[0]==efm_msg.p2_name ))
				{

					pointE->SetAttribute("msg",efm_msg.msg.c_str());
					pointE->SetAttribute("image",efm_msg.imagpathname.c_str());
					doc.SaveFile();
					return true;
				}
				pointE = pointE->NextSiblingElement("emf_msg");
			}
			TiXmlElement tmpE("emf_msg");
			tmpE.SetAttribute("msg",efm_msg.msg.c_str());
			tmpE.SetAttribute("image",efm_msg.imagpathname.c_str());
			tmpE.SetAttribute("points",efm_msg.p1_name+","+efm_msg.p2_name);
			rootE->InsertEndChild(tmpE);
			doc.SaveFile();
		}
	}

	return true;
}

bool ts_emf_wnd::addMsgList(EFMMESSAGE efm_msg)
{
	EFMMESSAGELIST::iterator iter = msg_list.begin();
	while (iter!=msg_list.end())
	{
		EFMMESSAGE tmp_msg = (*iter);
		if (tmp_msg==efm_msg)
		{
			msg_list.erase(iter);
			break;
		}
		iter++;
	}
	msg_list.push_back(efm_msg);
	return true;
}

void ts_emf_wnd::showMsgDlg(bool Ok,EFMMESSAGE msg,bool del_self)
{
	if (!del_self)
	{
		EmfMsgBox dlg(Ok,msg,this);
		dlg.DoModal();
	}else
	{
		if (!::IsIconic(AfxGetMainWnd()->GetSafeHwnd()))
		{
			static EmfMsgBox *pdlg = NULL;
			if (!pdlg)
			{ 
				pdlg = new EmfMsgBox(Ok,msg,this,true);
				pdlg->Create(EmfMsgBox::IDD,this);
			}

			pdlg->reset(Ok,msg);
		}

	}
}
EFMMESSAGE ts_emf_wnd::getEfmMsg(string p1_name,string p2_name)
{
	DWORD start = GetTickCount();
	EFMMESSAGELIST::iterator iter = msg_list.begin();
	while(iter!=msg_list.end())
	{
		EFMMESSAGE msg = (*iter);
		if ((msg.p1_name==p1_name && msg.p2_name==p2_name) || (msg.p1_name==p2_name && msg.p2_name==p1_name))
		{
			return msg;
			printf_s("获得信息所用时间:%d\n", GetTickCount()-start);
		}
		iter++;
	}
	printf_s("获得信息所用时间:%d\n", GetTickCount()-start);
	return EFMMESSAGE(p1_name,p2_name);
}

bool ts_emf_wnd::drawLine(string line_name)	//画线
{
	LINE_INFO * line = getLine(line_name);
	if (line)
		drawLine(line);
	else
		return false;
	return true;
}


void ts_emf_wnd::reset() //复位
{
	m_showing_lines.clear();
	m_showing_points.clear();
	setEmfType(m_emf_type);
}

LINE_INFO * ts_emf_wnd::getLine(string line_name)
{
	vector<LINE_INFO*>::iterator iter = m_lines.begin();
	while (iter!=m_lines.end())
	{
		if ((*iter)->line_name==line_name)
		{
			if (!(*iter)->is_yellow)
			{
				return (*iter);
			}else if (m_emf_type==1 && (*iter)->is_yellow )
			{
				return (*iter);
			}
			
		}
		iter++;
	}
	return NULL;
}

void ts_emf_wnd::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent==1) //延迟缩放
	{
		KillTimer(1);
		reinit_memDC();
		Invalidate();
	}
	if (2==nIDEvent) //刷新连线
	{

		bool repaint = false;
		vector<LINE_INFO *>::iterator iter = m_showing_lines.begin();
		while (iter!=m_showing_lines.end())
		{
			LINE_INFO *tmp_line = (*iter);
			tmp_line->hide_count--;
			if (tmp_line->hide_count<=0)
			{
				iter = m_showing_lines.erase(iter);
				repaint = true;
				remove_dlglist(tmp_line->p1_name,tmp_line->p2_name);
				continue;
			}

			iter++;
		}


		if (repaint)
		{
			reDraw();
			printf_s("掉线刷新\n");
		}
	}
	if (4==nIDEvent)		//测试使用
	{
		BYTE tmpb[] = {1,20};
		LinkLine(tmpb,2);
	}

	if (5==nIDEvent)		//定时检查错误连线的对话框列表
	{
		DLGLIST::iterator iter = m_dlg.begin();
		while(iter!=m_dlg.end())
		{
		
			iter->wait_for_count--;
			if (iter->wait_for_count<0)
			{
				iter = m_dlg.erase(iter);
				continue;
			}
			iter++;
		}
	}

	if (6==nIDEvent)
	{
		KillTimer(6);
		if (m_error_point.size()>0)
		{
			vector<POINT_INFO> tmp_ps = (*m_error_point.erase(m_error_point.begin()));
			vector<POINT_INFO>::iterator iter = tmp_ps.begin();
			while(iter!=tmp_ps.end())
			{
				POINT_INFO pi = (*iter);
				clear(&pi);
				iter++;
			}
		}
		
	}
	CWnd::OnTimer(nIDEvent);
}

UINT32 ts_emf_wnd::GetCableStat()		//获得5-*线的状态
{
	return 0xFFFFFFFF;
	UINT32 stat = 0;
	if (m_mode==1) return stat;
	vector<LINE_INFO*>::iterator iter = m_showing_lines.begin();

	for (;iter!=m_showing_lines.end();iter++)
	{
		LINE_INFO* ptmpline = (*iter);

		if (ptmpline->line_name.substr(0,1)=="5")
		{
			string noline = ptmpline->line_name.substr(2,ptmpline->line_name.length()-2);
			int no = atoi(noline.c_str());
			stat = stat&(1<<no);
		}

	}
	return stat;
}

char* itoaa(BYTE num)
{
	static CString str = "";
	str.Format("%d", num);
	return str.GetBuffer();
}

bool ts_emf_wnd::LinkLine(BYTE *lines,int count )	//连接线号,如果有一个错误.返回false.
{

	
	if (m_mode==1) return false;

	bool ok = false;
	string p1_name;
	string p2_name;

	for (int i=1;i<count;i++)
	{
		p1_name = getPoint(lines[0]);
		p2_name = getPoint(lines[i]);
		LINE_INFO *line = getLine(p1_name,p2_name);
		ok = ok | (line!=NULL);
		if (line)
		{
			//是否线已经存在
			bool lineexist = existLine(p1_name,p2_name);
			if (!lineexist)
			{
				line->hide_count = HIDELINE_TOTAL;
				drawLine(line);
				m_showing_lines.push_back(line);
				if (IsWindowVisible())
				{
					showMsgDlg(line,EFMMESSAGE(),true);
				}

			}else
			{
				line->hide_count = HIDELINE_TOTAL;
			}

		}else
		{

		}

	}
	if (!ok)
	{
		 //m_error_point
// 		vector<POINT_INFO> tmp_ps;
// 		for (int i=0;i<count;i++)
// 		{
// 			string tmp_p1_name = getPoint(lines[i]);
// 			POINT_INFO *p3 =  getPointByName(tmp_p1_name);
// 			tmp_ps.push_back(*p3);
// 			reDraw(p3);
// 		}
// 		m_error_point.push_back(tmp_ps);
// 		SetTimer(6,4000,NULL);

		if (!in_dlglist(p1_name,p2_name)) //错误是否在错误连线链表中
		{
			if (IsWindowVisible())
			{
				showMsgDlg(ok,getEfmMsg(p1_name,p2_name),true);
				printf_s("弹出错误提示对话框.\n");
			}	
			EMFMSGDLGED dlg;
			dlg.p1_name = p1_name;
			dlg.p2_name = p2_name;
			dlg.wait_for_count = SHOWDLG_TOTAL;
			m_dlg.push_back(dlg);
		
		}else
		{
			if (IsWindowVisible())
				showMsgDlg(ok,getEfmMsg(p1_name,p2_name),true);
			remove_dlglist(p1_name,p2_name);
			EMFMSGDLGED dlg;
			dlg.p1_name = p1_name;
			dlg.p2_name = p2_name;
			dlg.wait_for_count = SHOWDLG_TOTAL;
			m_dlg.push_back(dlg);

		}
		
	}
	
	return ok;
}

string ts_emf_wnd::getPoint(BYTE line_no)
{
	/*
	上传点号 1   ～  36表示“环境采集系统”的点号1-1～1-36；
	上传点号 37  ～  70表示“家电控制系统”的点号2-1～2-34；
	上传点号 71  ～ 112表示“安防控制系统”的点号3-1～3-42；
	上传点号 113 ～ 174表示“弱电控制系统”的点号4-1～4-62；
	上传点号 175 ～ 219表示“强电控制系统”的点号5-1～5-45；
	*/
	int  indexCount = 5;
	BYTE indexArray[] = {36,34,42,62,45};
	UINT tmpIndex = 0;
	UINT totalIndex = 0;
	for (int i=0;i<indexCount;i++)
	{
		totalIndex += indexArray[i];
		if (line_no<=totalIndex)
		{
			char p_name[20];
			sprintf_s(p_name,"%d-%d",i+1,line_no-tmpIndex);
			return p_name;
		}
		tmpIndex = totalIndex;
	}
	return "";
}

LRESULT ts_emf_wnd::doLinkLineMsg(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

void ts_emf_wnd::setMode(int mode)
{
	m_mode = mode;
	if (m_mode!=1)
	{
		m_showing_points.clear();
		m_showing_lines.clear();
		reDraw();
		SetTimer(2,HIDEINT,NULL);		//刷新连线是否在线
		SetTimer(5,SHOWDLG_INT,NULL);	//刷新错误连线
		
	}else{
		KillTimer(2);
		KillTimer(5);
	}

	
}

bool ts_emf_wnd::in_dlglist(string p1_name,string p2_name)
{
	bool in = false;
	DLGLIST::iterator iter = m_dlg.begin();
	while(iter!=m_dlg.end())
	{
		EMFMSGDLGED dlg = (*iter);

		if ((dlg.p1_name==p1_name && dlg.p2_name==p2_name) || (dlg.p2_name==p1_name && dlg.p1_name==p2_name))
		{
			return true;
		}
		iter++;
	}
	return in;
}

void ts_emf_wnd::remove_dlglist(string p1_name,string p2_name)
{
	DLGLIST::iterator iter = m_dlg.begin();
	while(iter!=m_dlg.end())
	{
		EMFMSGDLGED dlg = (*iter);

		if ((dlg.p1_name==p1_name && dlg.p2_name==p2_name) || (dlg.p2_name==p1_name && dlg.p1_name==p2_name))
		{
			m_dlg.erase(iter);
			return;
		}
		iter++;
	}
}

POINT_INFO *ts_emf_wnd::getPointByName(string p_name)
{
	vector<POINT_INFO*>::iterator piter = m_points.begin();
	while(piter!=m_points.end())
	{
		if ((*piter)->point_name==p_name)
			return (*piter);
		piter++;
	}
	return NULL;
}

void ts_emf_wnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nChar==VK_DELETE)
	{
		reset();
	}
	
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


