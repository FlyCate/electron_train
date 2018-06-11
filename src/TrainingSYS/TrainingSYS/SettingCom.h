#pragma once
#include "afxwin.h"
#include "xSkinButton.h"
//#include "SerialPort.h"
#include "HwCOM.h"
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
	byte payload[20];
	byte theend;
}PKT,*PPKT;

//#include "TrainingSYSDlg.h"
// SettingCom 对话框
class CTrainingSYSDlg;
class SettingCom : public CDialogEx
{
	DECLARE_DYNAMIC(SettingCom)

public:
	SettingCom(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~SettingCom();

// 对话框数据
	enum { IDD = IDD_DLG_SER_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cb_comsel;
	CComboBox m_cb_bundsel;
	CxSkinButton m_btn_ok;

	CxSkinButton m_btn_open;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	CString path;
	CTrainingSYSDlg *parent;
	void DrawBmp(CString strname);
	CString m_com_name;
	byte    m_com_index;
	int     m_bund;
    int      m_tm_id;
	bool     m_send_flag;
	CString  m_tmoutinf;
	afx_msg void OnBnClickedBtnOkCom();
	static bool m_first;
	afx_msg void OnCbnSelchangeCbCom();
	afx_msg void OnCbnSelchangeCbBund();
	//CSerialPort m_com;
	CHwCOM m_com;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	int removechildwnd(void);
	afx_msg void OnBnClickedCheckOpen();
	bool m_isopen;
	LONG OnComm(WPARAM ch,LPARAM port);
	bool serialsenddata(byte * p,int len);
	VOID MakeCMDPKT(PKT *pkt,byte cmd,byte  *payload,byte paylen);
	bool send_cmd_whole_start_run(void);
	bool send_cmd_whole_stop_run(void);
	bool send_cmd_start_scan(void);
	bool send_cmd_stop_scan(void);
	bool send_cmd_all_bsp_chk(void);
	bool send_link_error(void);
	void handerdatapkt(PKT * pkt);
	void ParselinkLine(PKT * pkt);
	bool serialsenddata(byte * p,int len,bool ischk= false ,CString inf="通讯超时",DWORD ms = 3000);

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	CWinThread *m_pThread; //线程指针
	BOOL m_runing;
	void start_serial_thread();
	void stop_serial_thread();
	LONG serial_hander_data(WPARAM ch,LPARAM port);
};
