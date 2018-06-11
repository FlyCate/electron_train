#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "xSkinButton.h"
#include "TrainingSYSDlg.h"

#define  FRAME_HEADER 0xfd
#define  FRAME_END    0xCC

#define	CMD_START_RUN   0x04
#define	CMD_START_STOP  0x04
#define	CMD_DEG_SCAN  0x05
#define	CMD_END_SCAN  0x05
#define	CMD_POWER_CHK 0x06

#define	CMD_START_RUN_FD   0x04
#define	CMD_START_STOP_FD  0x04
#define	CMD_DEG_SCAN_FD  0x05
#define	CMD_END_SCAN_FD  0x05
#define	CMD_POWER_CHK_FD 0x06  
#define CMD_POWER_LINK_FD 0x07
#define CMD_POWER_LINK_ERROR_FD 0x08
typedef struct {
	byte header;
	byte length;
	byte cmd;
	byte payload[100];
	byte theend;
}PKT,*PPKT;

// Net_setting 对话框

class Net_setting : public CDialogEx
{
	DECLARE_DYNAMIC(Net_setting)

public:
	Net_setting(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Net_setting();

// 对话框数据
	enum { IDD = IDD_DLG_NET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedBtnNetClose();
	afx_msg void OnBnClickedBtnNetLink();
	CString m_ip;
	 int m_port;
	int m_r_port;
	bool m_islink;
	int m_sock;
	CWinThread *m_pThread; //线程指针
	BOOL m_runing;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	CString path;
	CTrainingSYSDlg *parent;
	int udp_send_data(byte *data,WORD len);
	bool send_cmd_whole_start_run(void);
	bool send_cmd_whole_stop_run(void);
	bool send_cmd_start_scan(void);
	bool send_cmd_stop_scan(void);
	bool send_cmd_all_bsp_chk(void);
	bool  send_link_error(void);
	bool check_pkt_header(PKT  *pkt,unsigned int pkt_len);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
private:
	CString get_ip_address();
	int get_port_address();
	int get_port_address(CEdit  *pedit);
	void start_net_thread();
	void stop_net_thread();
	afx_msg	LONG serial_hander_data(WPARAM ch,LPARAM port);
	void handerdatapkt(PKT * pkt);
	bool get_int(CEdit * edit_ctrl, unsigned int min,unsigned int max, unsigned int &val,const CString & mess);
	int net_link_init();
	VOID MakeCMDPKT(PKT *pkt,byte cmd,byte  *payload,byte paylen);
	void ParselinkLine(PKT * pkt);
	void DrawBmp(CString strname);
	int removechildwnd(void);
public:
	CIPAddressCtrl m_ip_input;
	CxSkinButton m_link_net;
	CxSkinButton m_close_wind;
	CEdit m_port_input;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CEdit m_r_port_input;
};
