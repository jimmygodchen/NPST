// CMyDlgParam.cpp : implementation file
//

#include "stdafx.h"
#include "NPS7510.h"
#include "CMyDlgParam.h"
// #include "CustomCells.h"
#include "CMyGridCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CMyParamGridCtrl sample class
const CString c_strBaud[3] = 
{
    _T("2400"), _T("4800"), _T("9600")
};

CMyParamGridCtrl::CMyParamGridCtrl()
{
}

CMyParamGridCtrl::~CMyParamGridCtrl()
{
}

BEGIN_MESSAGE_MAP(CMyParamGridCtrl, CMyGridCtrl)
    //{{AFX_MSG_MAP(CMyParamGridCtrl)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyParamGridCtrl message handlers

int CMyParamGridCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if(CMyGridCtrl::OnCreate(lpCreateStruct) == -1)
        return -1;

    m_pParamNPSR = (DEVICEPARAM_NPS*)m_ParamR.wReserved;
    m_pParamNPSW = (DEVICEPARAM_NPS*)m_ParamW.wReserved;

    Mem2Ctr();

    return 0;
}

void CMyParamGridCtrl::Mem2Ctr(void)
{
    int i=0;
    CStringArray aContent;

    char szDevType[20];
    CString strDevType;
    for(i=0;i<16;i++)
    {
        szDevType[i] = m_ParamR.wszDeviceType[i]&0xff;
    }
    szDevType[i] = '\0';
    strDevType = szDevType;

    CBCGPGridRow* pRow = CreateNewRow();
    pRow->GetItem(0)->SetValue(_T("�豸����"));
    pRow->GetItem(1)->SetValue((LPCTSTR)strDevType);

    AddRow(pRow, FALSE);

    AddRowEdit(_T("ͨѶ��ַ"), (int)m_ParamR.wModbusAddr1, _T(""));

    aContent.RemoveAll();
    for(i=0;i<3;i++)
    {
        aContent.Add(c_strBaud[i]);
    }
    AddRowCombox(_T("������"), (int)m_ParamR.wBaudrate1, aContent, _T(""));

    aContent.RemoveAll();
    aContent.Add(_T("OFF"));
    aContent.Add(_T("ON"));
    AddRowCombox(_T("PT���߼��"), (int)m_pParamNPSR->wToggleAlarmPT, aContent, _T(""));
    AddRowCombox(_T("PT��ѹVV����"), (int)m_pParamNPSR->wModePT, aContent, _T(""));

    AddRowEdit(_T("CT���"), (int)m_pParamNPSR->wScaleCT, _T(""));
    AddRowEdit(_T("PT���"), (int)m_pParamNPSR->wScalePT, _T(""));
}

void CMyParamGridCtrl::Ctr2Mem(void)
{
    int nPos = 0;

    _variant_t var;
    CString strTmp;
    CBCGPGridRow* pRow = GetRow(nPos++);
    ASSERT(pRow);
    var = pRow->GetItem(1)->GetValue();
    if(var.vt==VT_BSTR)
    {
        strTmp = (LPCTSTR)(_bstr_t)var;
    }

    int nLen = strTmp.GetLength();
    if(nLen>16) nLen = 16;
    int i = 0;
    for(i=0;i<nLen;i++)
    {
        m_ParamW.wszDeviceType[i] = strTmp.GetAt(i);
    }
    m_ParamW.wszDeviceType[i] = 0;

    m_ParamW.wModbusAddr1 = GetRowEditInt(nPos++);
    m_ParamW.wBaudrate1 = GetRowCombox(nPos++);

    m_pParamNPSW->wToggleAlarmPT = GetRowCombox(nPos++);
    m_pParamNPSW->wModePT = GetRowCombox(nPos++);

    m_pParamNPSW->wScaleCT = GetRowEditInt(nPos++);
    m_pParamNPSW->wScalePT = GetRowEditInt(nPos++);
}


/////////////////////////////////////////////////////////////////////////////
// CMyDlgParam dialog

CMyDlgParam::CMyDlgParam(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CMyDlgParam::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDlgParam)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_pDataParam = NULL;
    EnableLayout ();
}


void CMyDlgParam::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlgParam)
	DDX_Control(pDX, IDC_LIST_PARAM, m_wndLocation);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyDlgParam, CBCGPDialog)
	//{{AFX_MSG_MAP(CMyDlgParam)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlgParam message handlers

BOOL CMyDlgParam::OnInitDialog() 
{
	CBCGPDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    ASSERT(m_pDataParam);
    CWaitCursor wait;
    
    // Create grid tree:
    CRect rectGrid;
    m_wndLocation.GetClientRect (&rectGrid);
    m_wndLocation.MapWindowPoints (this, &rectGrid);
    
    m_wndGrid.Create (WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rectGrid, this, IDC_LIST_PARAM);
    
    // Set grid colors
    CBCGPGridColors colors;
    colors.m_LeftOffsetColors.m_clrBackground = globalData.clrWindow;
    m_wndGrid.SetColorTheme (colors);
    
    CBCGPGridColors theme;
    CBCGPVisualManager::GetInstance ()->OnSetGridColorTheme(&m_wndGrid, theme);
    //     m_wndGridFloat.SendMessage(BCGM_ONSETCONTROLVMMODE, TRUE);
    m_wndGrid.SetColorTheme(theme);

    CBCGPStaticLayout* pLayout = (CBCGPStaticLayout*)GetLayout();
    if(pLayout != NULL)
    {
        pLayout->AddAnchor(IDC_LIST_PARAM, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeBoth);
        pLayout->AddAnchor(IDOK, CBCGPStaticLayout::e_MoveTypeBoth, CBCGPStaticLayout::e_SizeTypeNone);
        pLayout->AddAnchor(IDCANCEL, CBCGPStaticLayout::e_MoveTypeBoth, CBCGPStaticLayout::e_SizeTypeNone);
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CMyDlgParam::OnOK() 
{
	// TODO: Add extra validation here

    if(MyMessageBox("���������޸��豸��ǰ�����в���,\t\n��ȷ���Ƿ���װ?","��ע��",MB_YESNO|MB_ICONQUESTION)==IDYES)
    {
        m_wndGrid.Ctr2Mem();
        m_pDataParam->StoreToDevice(m_wndGrid.m_ParamW);
    }

//     CBCGPDialog::OnOK();
}
