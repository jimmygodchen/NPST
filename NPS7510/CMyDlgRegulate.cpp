// CMyDlgRegulate.cpp : implementation file
//

#include "stdafx.h"
#include "NPS7510.h"
#include "CMyDlgRegulate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyRegulateGridCtrl sample class
CMyRegulateGridCtrl::CMyRegulateGridCtrl()
{
}

CMyRegulateGridCtrl::~CMyRegulateGridCtrl()
{
}

BEGIN_MESSAGE_MAP(CMyRegulateGridCtrl, CBCGPGridCtrl)
    //{{AFX_MSG_MAP(CMyRegulateGridCtrl)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyRegulateGridCtrl message handlers

int CMyRegulateGridCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if(CBCGPGridCtrl::OnCreate(lpCreateStruct) == -1)
        return -1;

    EnableColumnAutoSize (TRUE);
    SetSingleSel (FALSE);
    EnableGroupByBox (FALSE);
    //     m_wndGridFloat.SetReadOnly ();
    SetWholeRowSel ();
    EnableHeader (TRUE, 0);
    
    // Set grid tab order (first):
    SetWindowPos (&CWnd::wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    
    InsertColumn (0, _T("����"), 50);
    InsertColumn (1, _T("ʵ��"), 50);
    InsertColumn (2, _T("�鲿"), 50);

    Mem2Ctr();
    
    return 0;
}

CBCGPGridRow* CMyRegulateGridCtrl::CreateNewRow(void)
{
    int nColumnCount = GetColumnCount();
    CBCGPGridRow* pRow = CreateRow(nColumnCount);
    ASSERT(pRow);

    pRow->GetItem(0)->AllowEdit(FALSE);
    pRow->GetItem(1)->AllowEdit(TRUE);
    pRow->GetItem(2)->AllowEdit(TRUE);

    return pRow;
}

void CMyRegulateGridCtrl::AddRowEdit(CString strLable, short nR, short nX)
{
    _variant_t var;

    CBCGPGridRow* pRow = CreateNewRow();
    ASSERT(pRow);
    pRow->GetItem(0)->SetValue((LPCTSTR)strLable);
    float fR = nR*0.0001f;
    float fX = nX*0.0001f;
    var = (_variant_t)fR;
    pRow->GetItem(1)->SetValue(var);
    var = (_variant_t)fX;
    pRow->GetItem(2)->SetValue(var);
    AddRow(pRow, FALSE);
}

REGULATE CMyRegulateGridCtrl::GetRowEdit(int nPos)
{
    REGULATE reg;
    _variant_t var;
    CBCGPGridRow* pRow = GetRow(nPos);
    ASSERT(pRow);
    var = pRow->GetItem(1)->GetValue();
    if(var.vt==VT_R4)
    {
         reg.nRegulateR = (float)var*10000;
    }
    var = pRow->GetItem(2)->GetValue();
    if(var.vt==VT_R4)
    {
        reg.nRegulateX = (float)var*10000;
    }
    return reg;
}

void CMyRegulateGridCtrl::Mem2Ctr(void)
{
    CBCGPGridRow::m_strFormatFloat = _T("%.4f");
    AddRowEdit(_T("Ia"), m_RegulateR.regulate[0].nRegulateR, m_RegulateR.regulate[0].nRegulateX);
    AddRowEdit(_T("Ib"), m_RegulateR.regulate[1].nRegulateR, m_RegulateR.regulate[1].nRegulateX);
    AddRowEdit(_T("Ic"), m_RegulateR.regulate[2].nRegulateR, m_RegulateR.regulate[2].nRegulateX);
    AddRowEdit(_T("IA"), m_RegulateR.regulate[3].nRegulateR, m_RegulateR.regulate[3].nRegulateX);
    AddRowEdit(_T("IB"), m_RegulateR.regulate[4].nRegulateR, m_RegulateR.regulate[4].nRegulateX);
    AddRowEdit(_T("IC"), m_RegulateR.regulate[5].nRegulateR, m_RegulateR.regulate[5].nRegulateX);
    AddRowEdit(_T("3I0"), m_RegulateR.regulate[6].nRegulateR, m_RegulateR.regulate[6].nRegulateX);
    AddRowEdit(_T("Ua"), m_RegulateR.regulate[7].nRegulateR, m_RegulateR.regulate[7].nRegulateX);
    AddRowEdit(_T("Ub"), m_RegulateR.regulate[8].nRegulateR, m_RegulateR.regulate[8].nRegulateX);
    AddRowEdit(_T("Uc"), m_RegulateR.regulate[9].nRegulateR, m_RegulateR.regulate[9].nRegulateX);
}

void CMyRegulateGridCtrl::Ctr2Mem(void)
{
    int nPos = 0;
    REGULATE reg;
    reg = GetRowEdit(nPos);
    m_RegulateW.regulate[nPos++] = reg;
    reg = GetRowEdit(nPos);
    m_RegulateW.regulate[nPos++] = reg;
    reg = GetRowEdit(nPos);
    m_RegulateW.regulate[nPos++] = reg;
    reg = GetRowEdit(nPos);
    m_RegulateW.regulate[nPos++] = reg;
    reg = GetRowEdit(nPos);
    m_RegulateW.regulate[nPos++] = reg;
    reg = GetRowEdit(nPos);
    m_RegulateW.regulate[nPos++] = reg;
    reg = GetRowEdit(nPos);
    m_RegulateW.regulate[nPos++] = reg;
    reg = GetRowEdit(nPos);
    m_RegulateW.regulate[nPos++] = reg;
    reg = GetRowEdit(nPos);
    m_RegulateW.regulate[nPos++] = reg;
    reg = GetRowEdit(nPos);
    m_RegulateW.regulate[nPos++] = reg;
}



/////////////////////////////////////////////////////////////////////////////
// CMyDlgRegulate dialog


CMyDlgRegulate::CMyDlgRegulate(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CMyDlgRegulate::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDlgRegulate)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_pDataRegulte = NULL;
    EnableLayout();
}


void CMyDlgRegulate::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlgRegulate)
	DDX_Control(pDX, IDC_LIST_PARAM, m_wndLocation);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyDlgRegulate, CBCGPDialog)
	//{{AFX_MSG_MAP(CMyDlgRegulate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlgRegulate message handlers

void CMyDlgRegulate::OnOK() 
{
	// TODO: Add extra validation here
// 	m_wndGrid.Ctr2Mem();
    if(MyMessageBox("���������޸��豸��ǰ�����в���,\t\n��ȷ���Ƿ���װ?","��ע��",MB_YESNO|MB_ICONQUESTION)==IDYES)
    {
        m_wndGrid.Ctr2Mem();
        m_pDataRegulte->StoreToDevice(m_wndGrid.m_RegulateW);
    }
// 	CBCGPDialog::OnOK();
}

BOOL CMyDlgRegulate::OnInitDialog() 
{
	CBCGPDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    ASSERT(m_pDataRegulte);
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
