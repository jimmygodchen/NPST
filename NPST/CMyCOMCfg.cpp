// CMyCOMCfg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "IEC103Analysis.h"
#include "CMyCOMCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyCOMCfg dialog

struct MYIPADDRESS_BYTE
{
	BYTE IP1;
	BYTE IP2;
	BYTE IP3;
	BYTE IP4;
};

union MYIPADDRESS
{
	struct MYIPADDRESS_BYTE byteIPAddr;
	DWORD dwIPAddr;
};


CMyCOMCfg::CMyCOMCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyCOMCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyCOMCfg)
	m_nComBaud = 0;
	m_nComPort = 0;
	m_nUDPPortDest = 0;
	m_nUDPPortSrc = 0;
	m_nTCPPortServer = 0;
	m_nDeviceAddr = 1;
	m_nCycleTime = 1000;
	m_nComMode = 0;
	m_nTCPPortClient = 0;
	m_nTimeout = 1000;
	//}}AFX_DATA_INIT
}


void CMyCOMCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyCOMCfg)
	DDX_Control(pDX, IDC_IPADDRESS_TCPIPC, m_ctrTCPIPClient);
	DDX_Control(pDX, IDC_IPADDRESS_TCPIPS, m_ctrTCPIPServer);
	DDX_Control(pDX, IDC_IPADDRESS_SRC, m_ctrUDPIPSrc);
	DDX_Control(pDX, IDC_IPADDRESS_DEST, m_ctrUDPIPDest);
	DDX_CBIndex(pDX, IDC_COMBO_COMM_BAUD, m_nComBaud);
	DDX_CBIndex(pDX, IDC_COMBO_COMM_PORT, m_nComPort);
	DDX_Text(pDX, IDC_PORT_DEST, m_nUDPPortDest);
	DDX_Text(pDX, IDC_PORT_SRC, m_nUDPPortSrc);
	DDX_Text(pDX, IDC_PORT_TCPIPSERVER, m_nTCPPortServer);
	DDX_Text(pDX, IDC_EDIT_DEVICEADDR, m_nDeviceAddr);
	DDX_Text(pDX, IDC_EDIT_CYCLETIME, m_nCycleTime);
	DDV_MinMaxInt(pDX, m_nCycleTime, 10, 999999);
	DDX_Radio(pDX, IDC_RADIO_COMM, m_nComMode);
	DDX_Text(pDX, IDC_PORT_TCPIPCLIENT, m_nTCPPortClient);
	DDX_Text(pDX, IDC_EDIT_TIMEOUT, m_nTimeout);
	DDV_MinMaxInt(pDX, m_nTimeout, 100, 999999);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyCOMCfg, CDialog)
	//{{AFX_MSG_MAP(CMyCOMCfg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyCOMCfg message handlers

BOOL CMyCOMCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

    m_EnumSCI.EnumSCI();
    
    CComboBox* pCCombox = (CComboBox*)GetDlgItem(IDC_COMBO_COMM_PORT);
    pCCombox->ResetContent();
    int nSize = m_EnumSCI.m_arCOM.GetSize();
    for(int i=0;i<nSize;i++)
    {
        pCCombox->AddString(m_EnumSCI.m_arCOM[i]);
    }

	ComOption2Ctr();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMyCOMCfg::ComOption2Ctr(void)
{
	if(UpdateData(TRUE)==FALSE) return;
    int nSize = m_EnumSCI.m_arCOM.GetSize();
    m_nComPort = 0;
    for(int i=0;i<nSize;i++)
    {
        CString strTmp;
        strTmp.Format(_T("COM%d"),m_PortInfo.nComPort);
        if(strTmp==m_EnumSCI.m_arCOM[i])
        {
            m_nComPort = i;
        }
    }
	m_nComMode = m_PortInfo.nComMode;
// 	m_nComPort = m_PortInfo.nComPort;
	m_nComBaud = m_PortInfo.nComBaud;
	m_nUDPPortDest = m_PortInfo.nCommPortDest;
	m_nUDPPortSrc = m_PortInfo.nCommPortSrc;
	m_nTCPPortServer = m_PortInfo.nPortTCPIPServer;
	m_nTCPPortClient = m_PortInfo.nPortTCPIPClient;

	MYIPADDRESS ipaddr;
	ipaddr.dwIPAddr = m_PortInfo.dwCommIPSrc;
	m_ctrUDPIPSrc.SetAddress(ipaddr.byteIPAddr.IP1,ipaddr.byteIPAddr.IP2,ipaddr.byteIPAddr.IP3,ipaddr.byteIPAddr.IP4);
	ipaddr.dwIPAddr = m_PortInfo.dwCommIPDest;
	m_ctrUDPIPDest.SetAddress(ipaddr.byteIPAddr.IP1,ipaddr.byteIPAddr.IP2,ipaddr.byteIPAddr.IP3,ipaddr.byteIPAddr.IP4);
	ipaddr.dwIPAddr = m_PortInfo.dwTCPIPServer;
	m_ctrTCPIPServer.SetAddress(ipaddr.byteIPAddr.IP1,ipaddr.byteIPAddr.IP2,ipaddr.byteIPAddr.IP3,ipaddr.byteIPAddr.IP4);
	ipaddr.dwIPAddr = m_PortInfo.dwTCPIPClient;
	m_ctrTCPIPClient.SetAddress(ipaddr.byteIPAddr.IP1,ipaddr.byteIPAddr.IP2,ipaddr.byteIPAddr.IP3,ipaddr.byteIPAddr.IP4);

// 	EnableDlgCtrls(m_nComMode);
	UpdateData(FALSE);
}

void CMyCOMCfg::Ctr2ComOption(void)
{
	if(UpdateData(TRUE)==FALSE) return;
	
	m_PortInfo.nComMode = m_nComMode;
	m_PortInfo.nComPort = m_EnumSCI.GetSCI(m_nComPort);
	m_PortInfo.nComBaud = m_nComBaud;
	m_PortInfo.nCommPortDest = m_nUDPPortDest;
	m_PortInfo.nCommPortSrc = m_nUDPPortSrc;
	m_PortInfo.nPortTCPIPServer = m_nTCPPortServer;
	m_PortInfo.nPortTCPIPClient = m_nTCPPortClient;

	MYIPADDRESS ipaddr;
	m_ctrUDPIPSrc.GetAddress(ipaddr.byteIPAddr.IP1,ipaddr.byteIPAddr.IP2,ipaddr.byteIPAddr.IP3,ipaddr.byteIPAddr.IP4);
	m_PortInfo.dwCommIPSrc = ipaddr.dwIPAddr;
	m_ctrUDPIPDest.GetAddress(ipaddr.byteIPAddr.IP1,ipaddr.byteIPAddr.IP2,ipaddr.byteIPAddr.IP3,ipaddr.byteIPAddr.IP4);
	m_PortInfo.dwCommIPDest = ipaddr.dwIPAddr;
	m_ctrTCPIPServer.GetAddress(ipaddr.byteIPAddr.IP1,ipaddr.byteIPAddr.IP2,ipaddr.byteIPAddr.IP3,ipaddr.byteIPAddr.IP4);
	m_PortInfo.dwTCPIPServer = ipaddr.dwIPAddr;
	m_ctrTCPIPClient.GetAddress(ipaddr.byteIPAddr.IP1,ipaddr.byteIPAddr.IP2,ipaddr.byteIPAddr.IP3,ipaddr.byteIPAddr.IP4);
	m_PortInfo.dwTCPIPClient = ipaddr.dwIPAddr;

	// 	EnableDlgCtrls(m_nComMode);
	UpdateData(FALSE);
}

void CMyCOMCfg::OnOK() 
{
	// TODO: Add extra validation here
	Ctr2ComOption();
	CDialog::OnOK();
}
