// CMyPortSCIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CMySCI.h"
#include "CMyPortSCIDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyPortSCIDlg property page

IMPLEMENT_DYNCREATE(CMyPortSCIDlg, CBCGPPropertyPage)

CMyPortSCIDlg::CMyPortSCIDlg() : CBCGPPropertyPage(CMyPortSCIDlg::IDD)
{
	//{{AFX_DATA_INIT(CMyPortSCIDlg)
	m_nBaud = -1;
	m_nCom = -1;
	//}}AFX_DATA_INIT
    m_pEnumSCI = NULL;
}

CMyPortSCIDlg::~CMyPortSCIDlg()
{
}

void CMyPortSCIDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyPortSCIDlg)
	DDX_Control(pDX, IDC_COMBO_BAUD, m_wndBaud);
	DDX_Control(pDX, IDC_COMBO_PORT, m_wndPort);
	DDX_CBIndex(pDX, IDC_COMBO_BAUD, m_nBaud);
	DDX_CBIndex(pDX, IDC_COMBO_PORT, m_nCom);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyPortSCIDlg, CBCGPPropertyPage)
	//{{AFX_MSG_MAP(CMyPortSCIDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyPortSCIDlg message handlers

BOOL CMyPortSCIDlg::OnInitDialog() 
{
    CPropertyPage::OnInitDialog();

    int i;

    CMyEnumSCI::EnumSCI();

    int nSize = CMyEnumSCI::m_arCOM.GetSize();
    for(i=0;i<nSize;i++)
    {
        m_wndPort.AddString(m_pEnumSCI->m_arCOM[i]);
    }

    if(m_nCom>=nSize) m_nCom = -1;

    nSize = sizeof(g_cnBaud)/sizeof(int);

    for(i=0;i<nSize;i++)
    {
        CString strBaud;
        strBaud.Format(_T("%d"),g_cnBaud[i]);
        m_wndBaud.AddString(strBaud);
    }

    // TODO: Add extra initialization here

    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}
