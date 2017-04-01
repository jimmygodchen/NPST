// CMyUDPDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UDP.h"
#include "CMyUDPDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyUDPDlg property page

IMPLEMENT_DYNCREATE(CMyUDPDlg, CBCGPPropertyPage)

CMyUDPDlg::CMyUDPDlg() : CBCGPPropertyPage(CMyUDPDlg::IDD)
{
	//{{AFX_DATA_INIT(CMyUDPDlg)
	m_nPortDest = 0;
	m_nPortSrc = 0;
    m_dwIPDest = 0;
    m_dwIPSrc = 0;
	//}}AFX_DATA_INIT
}

CMyUDPDlg::~CMyUDPDlg()
{
}

void CMyUDPDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyUDPDlg)
	DDX_Control(pDX, IDC_IPADDRESS_SRC, m_wndIPSrc);
	DDX_Control(pDX, IDC_IPADDRESS_DEST, m_wndIPDest);
	DDX_Text(pDX, IDC_EDIT_PORT_DEST, m_nPortDest);
	DDX_Text(pDX, IDC_EDIT_PORT_SRC, m_nPortSrc);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyUDPDlg, CBCGPPropertyPage)
	//{{AFX_MSG_MAP(CMyUDPDlg)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyUDPDlg message handlers


BOOL CMyUDPDlg::OnInitDialog() 
{
	CBCGPPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here

    tIPADDRESS tIP;
    tIP.dwIPAddr = m_dwIPSrc;
    m_wndIPSrc.SetAddress(tIP.byteIPAddr.Field0, tIP.byteIPAddr.Field1, tIP.byteIPAddr.Field2, tIP.byteIPAddr.Field3);
    tIP.dwIPAddr = m_dwIPDest;
    m_wndIPDest.SetAddress(tIP.byteIPAddr.Field0, tIP.byteIPAddr.Field1, tIP.byteIPAddr.Field2, tIP.byteIPAddr.Field3);

    return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMyUDPDlg::OnDestroy() 
{
	CBCGPPropertyPage::OnDestroy();
	
	// TODO: Add your message handler code here
    tIPADDRESS tIP;
    m_wndIPSrc.GetAddress(tIP.byteIPAddr.Field0, tIP.byteIPAddr.Field1, tIP.byteIPAddr.Field2, tIP.byteIPAddr.Field3);
    m_dwIPSrc = tIP.dwIPAddr;
    m_wndIPDest.GetAddress(tIP.byteIPAddr.Field0, tIP.byteIPAddr.Field1, tIP.byteIPAddr.Field2, tIP.byteIPAddr.Field3);
    m_dwIPDest = tIP.dwIPAddr;
}
