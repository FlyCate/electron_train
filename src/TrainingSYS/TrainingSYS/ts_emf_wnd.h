//ts_emf_wnd.h

#pragma once
#include <string>
#include <vector>
using namespace std;

#include "efm_struct.h"
// ts_emf_wnd


class ts_emf_wnd : public CWnd
{
	DECLARE_DYNAMIC(ts_emf_wnd)

public:
	ts_emf_wnd(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~ts_emf_wnd();
	static EFMMESSAGELIST msg_list;
	static bool saveMsgList(EFMMESSAGE efm_msg);
	static bool addMsgList(EFMMESSAGE efm_msg);
////////////////////////////////////////////////////
//对外提供的接口
	void setEmfType(int type);	//设置图形类型
	UINT32 GetCableStat();		//获得5-*线的状态
	bool LinkLine(BYTE *lines,int count );	//连接线号,如果有一个错误.返回false.
	void reset();				//复位
	BOOL Create(CWnd *parent,int emf_type = 1);
	void setMode(int mode); //1:为手动绘图.2:为前端设备连线绘图.初始化为手动
//////////////////////////////////////////////////////////////////////////
protected:
	DECLARE_MESSAGE_MAP()

private:
	HENHMETAFILE m_hemf;
	HENHMETAFILE m_rs485_hemf;	//元文件句柄
	ENHMETAHEADER m_emheader; //元文件结构头 
	HENHMETAFILE m_zigbee_hemf;	//元文件句柄
	HENHMETAFILE m_433_hemf;	//元文件句柄
	HENHMETAFILE m_wifi_hemf;	//元文件句柄

	CDC m_memDC;		// 内存句柄
	CBitmap m_memBitmap;	//内存 句柄图片
	CDC m_memBakDC;			//内存句柄的备份
	CBitmap m_memBakBitmap;	//内存句柄图片备份
	double m_scal;			//缩放比例
	vector<POINT_INFO*> m_points;
	vector<LINE_INFO*> m_lines;
	vector<LINE_INFO*> m_showing_lines;	//正在显示的连线
	vector<POINT_INFO*> m_showing_points;	//正在显示的点
	vector<vector<POINT_INFO>> m_error_point;
	
	UINT m_emf_w;			//emf的尺寸，单位像素
	UINT m_emf_h;
	double m_emf_top;	//绘制emf图左上角坐标
	double m_emf_left;
	bool m_is_move;		//是否需要移动

	POINT m_move_start;
	POINT m_move_end;

	int m_emf_type;
	int m_mode;
	DLGLIST m_dlg;

private:
	
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
private:
	// 初始化emf文件
	bool init_emf(void);
	void init_line_point();		//初始化连线和端子
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	static vector<string> split(string str,string pattern);
	void reDraw();//重新画图
	void reDraw(POINT_INFO *p);					//描点
	void clear(POINT_INFO *p);					//清除点
	void drawLine(LINE_INFO *line);				//画线
	vector<POINT> getPoints(LINE_INFO *line);	//获得连线的坐标
	POINT getPoint(string point_name);			//从名称获得坐标
	POINT_INFO *getPointByName(string p_name);
	LINE_INFO *getLine(string p1_name,string p2_name);	//从两点名称获得线
	void showMsgDlg(bool Ok,EFMMESSAGE msg,bool sdel_self = false);					//显示对话框
	EFMMESSAGE getEfmMsg(string p1_name,string p2_name);
	LINE_INFO * getLine(string line_name);
	bool existLine(string p1_name,string p2_name);		//判断是否已经存在连线
	bool drawLine(string line_name);	//画线
	string getPoint(BYTE line_no);
	bool in_dlglist(string p1_name,string p2_name);
	void remove_dlglist(string p1_name,string p2_name);
protected:
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, LPVOID lpParam = NULL);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void PreSubclassWindow();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	void reinit_memDC(void);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	POINT_INFO * click_hot_point(int x, int y);
	afx_msg LRESULT doLinkLineMsg(WPARAM wParam, LPARAM lParam);
public:
	
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	int getmode()
	{
	  return m_mode;
	}
};


