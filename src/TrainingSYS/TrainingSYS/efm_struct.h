
#include "stdafx.h"
#include <string>
#include <vector>
using namespace std;

#ifndef _EFM_STRUCT_H_
#define _EFM_STRUCT_H_

typedef struct tag_line_info
{
	tag_line_info()
	{
		m_p = 0;
		m_p_size = 0;
		show = false;
	}
	string line_name;
	string p1_name;
	string p2_name;
	POINT *m_p;		//�м��
	int m_p_size;	//�м�����
	bool show;	//�Ƿ���ʾ
	bool is_yellow;	//�ǲ��ǻ���,����׼����rs485���豸��ͼ

	int hide_count;	//��ʱ


}LINE_INFO;

typedef struct 
{
	string p1_name;
	string p2_name;
	int wait_for_count;
}EMFMSGDLGED;

typedef vector<EMFMSGDLGED> DLGLIST;

typedef struct tageEFMMESSAGE
{
	tageEFMMESSAGE(){};
	tageEFMMESSAGE(string p1,string p2)
	{
		p1_name = p1;
		p2_name = p2;
	};
	string p1_name;
	string p2_name;
	string msg;
	string imagpathname;

	BOOL operator == (tageEFMMESSAGE othermsg)
	{
		if ((p1_name==othermsg.p1_name && p2_name==othermsg.p2_name) ||
			(p2_name==othermsg.p1_name && p1_name==othermsg.p2_name))
		return TRUE;
		return FALSE;
	}
}EFMMESSAGE;

typedef vector<EFMMESSAGE> EFMMESSAGELIST;

typedef struct tag_point_info
{
	tag_point_info()
	{
		start_p.x = 0;
		start_p.y = 0;

	};
	string point_name;
	POINT start_p;	//ԭʼ��

}POINT_INFO;


#endif