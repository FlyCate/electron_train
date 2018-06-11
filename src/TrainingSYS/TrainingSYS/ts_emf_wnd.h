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
	ts_emf_wnd(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~ts_emf_wnd();
	static EFMMESSAGELIST msg_list;
	static bool saveMsgList(EFMMESSAGE efm_msg);
	static bool addMsgList(EFMMESSAGE efm_msg);
////////////////////////////////////////////////////
//�����ṩ�Ľӿ�
	void setEmfType(int type);	//����ͼ������
	UINT32 GetCableStat();		//���5-*�ߵ�״̬
	bool LinkLine(BYTE *lines,int count );	//�����ߺ�,�����һ������.����false.
	void reset();				//��λ
	BOOL Create(CWnd *parent,int emf_type = 1);
	void setMode(int mode); //1:Ϊ�ֶ���ͼ.2:Ϊǰ���豸���߻�ͼ.��ʼ��Ϊ�ֶ�
//////////////////////////////////////////////////////////////////////////
protected:
	DECLARE_MESSAGE_MAP()

private:
	HENHMETAFILE m_hemf;
	HENHMETAFILE m_rs485_hemf;	//Ԫ�ļ����
	ENHMETAHEADER m_emheader; //Ԫ�ļ��ṹͷ 
	HENHMETAFILE m_zigbee_hemf;	//Ԫ�ļ����
	HENHMETAFILE m_433_hemf;	//Ԫ�ļ����
	HENHMETAFILE m_wifi_hemf;	//Ԫ�ļ����

	CDC m_memDC;		// �ڴ���
	CBitmap m_memBitmap;	//�ڴ� ���ͼƬ
	CDC m_memBakDC;			//�ڴ����ı���
	CBitmap m_memBakBitmap;	//�ڴ���ͼƬ����
	double m_scal;			//���ű���
	vector<POINT_INFO*> m_points;
	vector<LINE_INFO*> m_lines;
	vector<LINE_INFO*> m_showing_lines;	//������ʾ������
	vector<POINT_INFO*> m_showing_points;	//������ʾ�ĵ�
	vector<vector<POINT_INFO>> m_error_point;
	
	UINT m_emf_w;			//emf�ĳߴ磬��λ����
	UINT m_emf_h;
	double m_emf_top;	//����emfͼ���Ͻ�����
	double m_emf_left;
	bool m_is_move;		//�Ƿ���Ҫ�ƶ�

	POINT m_move_start;
	POINT m_move_end;

	int m_emf_type;
	int m_mode;
	DLGLIST m_dlg;

private:
	
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
private:
	// ��ʼ��emf�ļ�
	bool init_emf(void);
	void init_line_point();		//��ʼ�����ߺͶ���
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	static vector<string> split(string str,string pattern);
	void reDraw();//���»�ͼ
	void reDraw(POINT_INFO *p);					//���
	void clear(POINT_INFO *p);					//�����
	void drawLine(LINE_INFO *line);				//����
	vector<POINT> getPoints(LINE_INFO *line);	//������ߵ�����
	POINT getPoint(string point_name);			//�����ƻ������
	POINT_INFO *getPointByName(string p_name);
	LINE_INFO *getLine(string p1_name,string p2_name);	//���������ƻ����
	void showMsgDlg(bool Ok,EFMMESSAGE msg,bool sdel_self = false);					//��ʾ�Ի���
	EFMMESSAGE getEfmMsg(string p1_name,string p2_name);
	LINE_INFO * getLine(string line_name);
	bool existLine(string p1_name,string p2_name);		//�ж��Ƿ��Ѿ���������
	bool drawLine(string line_name);	//����
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


