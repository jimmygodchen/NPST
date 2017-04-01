// CMyDlgSetpoint.cpp : implementation file
//

#include "stdafx.h"
#include "NPS7510.h"
#include "CMyGridCtrl.h"
#include "CMyDlgSetpoint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMySetpointGridCtrl sample class

CMySetpointGridCtrl::CMySetpointGridCtrl()
{
}

CMySetpointGridCtrl::~CMySetpointGridCtrl()
{
}

BEGIN_MESSAGE_MAP(CMySetpointGridCtrl, CMyGridCtrl)
    //{{AFX_MSG_MAP(CMySetpointGridCtrl)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMySetpointGridCtrl message handlers

int CMySetpointGridCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if(CMyGridCtrl::OnCreate(lpCreateStruct) == -1)
        return -1;

    m_pSetpointR = (DEVICESETPOINT_NPS*)m_SetpointR.wSetpointArea1;
    m_pSetpointW = (DEVICESETPOINT_NPS*)m_SetpointW.wSetpointArea1;
    
    Mem2Ctr();
    
    return 0;
}

void CMySetpointGridCtrl::Mem2Ctr(void)
{
    float fData;

    CBCGPGridRow::m_strFormatFloat = _T("%.2f");

    CBCGPGridRow* pRow = AddProtectTog(_T("����I��"), m_SetpointR.wToggle[0]);
    fData = m_pSetpointR->wDL1_SetI*0.01f;
    AddEditSub(pRow, _T("������ֵ"), fData, _T("A"));
    fData = m_pSetpointR->wDL1_SetT*0.01f;
    AddEditSub(pRow, _T("ʱ�䶨ֵ"), fData, _T("s"));
    AddTogSub(pRow, _T("��ѹ����"), m_pSetpointR->wDL1_TogU);

    pRow = AddProtectTog(_T("����II��"), m_SetpointR.wToggle[1]);
    fData = m_pSetpointR->wDL2_SetI*0.01f;
    AddEditSub(pRow, _T("������ֵ"), fData, _T("A"));
    fData = m_pSetpointR->wDL2_SetT*0.01f;
    AddEditSub(pRow, _T("ʱ�䶨ֵ"), fData, _T("s"));
    AddTogSub(pRow, _T("��ѹ����"), m_pSetpointR->wDL2_TogU);

    pRow = AddProtectTog(_T("����III��"), m_SetpointR.wToggle[2]);
    fData = m_pSetpointR->wDL3_SetI*0.01f;
    AddEditSub(pRow, _T("������ֵ"), fData, _T("A"));
    fData = m_pSetpointR->wDL3_SetT*0.01f;
    AddEditSub(pRow, _T("ʱ�䶨ֵ"), fData, _T("s"));
    AddTogSub(pRow, _T("��ѹ����"), m_pSetpointR->wDL2_TogU);

    fData = m_pSetpointR->wDL_SetU*0.01f;
    AddRowEdit(_T("��������������ѹ"), fData,_T("V"));

    pRow = AddProtectTog(_T("����I��"), m_SetpointR.wToggle[3]);
    fData = m_pSetpointR->wLX1_SetI*0.01f;
    AddEditSub(pRow, _T("������ֵ"), fData, _T("A"));
    fData = m_pSetpointR->wLX1_SetT*0.01f;
    AddEditSub(pRow, _T("ʱ�䶨ֵ"), fData, _T("s"));

    pRow = AddProtectTog(_T("����II��"), m_SetpointR.wToggle[4]);
    fData = m_pSetpointR->wLX2_SetI*0.01f;
    AddEditSub(pRow, _T("������ֵ"), fData, _T("A"));
    fData = m_pSetpointR->wLX2_SetT*0.01f;
    AddEditSub(pRow, _T("ʱ�䶨ֵ"), fData, _T("s"));

    pRow = AddProtectTog(_T("������"), m_SetpointR.wToggle[5]);
    fData = m_pSetpointR->wGFH_SetI*0.01f;
    AddEditSub(pRow, _T("������ֵ"), fData, _T("A"));
    fData = m_pSetpointR->wGFH_SetT*0.01f;
    AddEditSub(pRow, _T("ʱ�䶨ֵ"), fData, _T("s"));

    pRow = AddProtectTog(_T("�͵�ѹ"), m_SetpointR.wToggle[6]);
    fData = m_pSetpointR->wDDY_SetU*0.01f;
    AddEditSub(pRow, _T("��ѹ��ֵ"), fData, _T("V"));
    fData = m_pSetpointR->wDDY_SetI*0.01f;
    AddEditSub(pRow, _T("��������"), fData, _T("A"));
    fData = m_pSetpointR->wDDY_SetT*0.01f;
    AddEditSub(pRow, _T("ʱ�䶨ֵ"), fData, _T("s"));

    AddProtectTog(_T("����˹"), m_SetpointR.INSetpoint[0].wToggle);
    AddProtectTog(_T("����˹"), m_SetpointR.INSetpoint[1].wToggle);
    AddProtectTog(_T("�¸���բ"), m_SetpointR.INSetpoint[2].wToggle);
    AddProtectTog(_T("�¸߸澯"), m_SetpointR.INSetpoint[3].wToggle);
}

CBCGPGridRow* CMySetpointGridCtrl::AddProtectTog(CString strLable, WORD wTog)
{
    CBCGPGridRow* pRow = CreateNewRow();
    ASSERT_VALID(pRow);
    pRow->AllowSubItems();
    pRow->GetItem(0)->SetValue((LPCTSTR)strLable);

    CStringArray aContent;
    aContent.Add(_T("OFF"));
    aContent.Add(_T("ON"));
    int nSize = aContent.GetSize();
    CBCGPGridItem* pItem;
    if(wTog>=0 && wTog<nSize)
    {
        pItem = new CBCGPGridItem((LPCTSTR)aContent[wTog]);
    }
    else
    {
        pItem = new CBCGPGridItem((LPCTSTR)_T(""));
    }
    ASSERT(pItem);
    pItem->SetReadOnly(TRUE);
    for(int i=0;i<nSize;i++)
    {
        pItem->AddOption((LPCTSTR)aContent[i], TRUE);
    }
    pRow->ReplaceItem(1, pItem);
//     pRow->GetItem(2)->SetValue((LPCTSTR)strUnit);
    AddRow(pRow, FALSE);
    return pRow;
}

void CMySetpointGridCtrl::AddTogSub(CBCGPGridRow* pRoot, CString strLable, WORD wTog)
{
    ASSERT_VALID(pRoot);

    CBCGPGridRow* pRow = CreateNewRow();
    ASSERT_VALID(pRow);
    pRow->AllowSubItems();
    pRow->GetItem(0)->SetValue((LPCTSTR)strLable);
    
    CStringArray aContent;
    aContent.Add(_T("OFF"));
    aContent.Add(_T("ON"));
    int nSize = aContent.GetSize();
    CBCGPGridItem* pItem;
    if(wTog>=0 && wTog<nSize)
    {
        pItem = new CBCGPGridItem((LPCTSTR)aContent[wTog]);
    }
    else
    {
        pItem = new CBCGPGridItem((LPCTSTR)_T(""));
    }
    ASSERT(pItem);
    pItem->SetReadOnly(TRUE);
    for(int i=0;i<nSize;i++)
    {
        pItem->AddOption((LPCTSTR)aContent[i], TRUE);
    }
    pRow->ReplaceItem(1, pItem);
    pRoot->AddSubItem(pRow, FALSE);
}

void CMySetpointGridCtrl::AddEditSub(CBCGPGridRow* pRoot, CString strLable, float fValue, CString strUnit)
{
    ASSERT_VALID(pRoot);

    CBCGPGridRow* pSub = CreateNewRow();
    ASSERT_VALID(pSub);
    pSub->GetItem(0)->SetValue((LPCTSTR)strLable);
    _variant_t var;
    var = (_variant_t)fValue;
    pSub->GetItem(1)->SetValue(var);
    pSub->GetItem(2)->SetValue((LPCTSTR)strUnit);
    pRoot->AddSubItem(pSub, FALSE);
}

void CMySetpointGridCtrl::Ctr2Mem(void)
{
    int nPos = 0;
    float fData;

    m_SetpointW.wToggle[0] = GetRowCombox(nPos++);
    fData = GetRowEditFloat(nPos++);
    m_pSetpointW->wDL1_SetI = fData*100;
    fData = GetRowEditFloat(nPos++);
    m_pSetpointW->wDL1_SetT = fData*100;
    m_pSetpointW->wDL1_TogU = GetRowCombox(nPos++);

    m_SetpointW.wToggle[1] = GetRowCombox(nPos++);
    fData = GetRowEditFloat(nPos++);
    m_pSetpointW->wDL2_SetI = fData*100;
    fData = GetRowEditFloat(nPos++);
    m_pSetpointW->wDL2_SetT = fData*100;
    m_pSetpointW->wDL2_TogU = GetRowCombox(nPos++);

    m_SetpointW.wToggle[2] = GetRowCombox(nPos++);
    fData = GetRowEditFloat(nPos++);
    m_pSetpointW->wDL3_SetI = fData*100;
    fData = GetRowEditFloat(nPos++);
    m_pSetpointW->wDL3_SetT = fData*100;
    m_pSetpointW->wDL3_TogU = GetRowCombox(nPos++);

    fData = GetRowEditFloat(nPos++);
    m_pSetpointW->wDL_SetU = fData*100;

    m_SetpointW.wToggle[3] = GetRowCombox(nPos++);
    fData = GetRowEditFloat(nPos++);
    m_pSetpointW->wLX1_SetI = fData*100;
    fData = GetRowEditFloat(nPos++);
    m_pSetpointW->wLX1_SetT = fData*100;

    m_SetpointW.wToggle[4] = GetRowCombox(nPos++);
    fData = GetRowEditFloat(nPos++);
    m_pSetpointW->wLX2_SetI = fData*100;
    fData = GetRowEditFloat(nPos++);
    m_pSetpointW->wLX2_SetT = fData*100;

    m_SetpointW.wToggle[5] = GetRowCombox(nPos++);
    fData = GetRowEditFloat(nPos++);
    m_pSetpointW->wGFH_SetI = fData*100;
    fData = GetRowEditFloat(nPos++);
    m_pSetpointW->wGFH_SetT = fData*100;

    m_SetpointW.wToggle[6] = GetRowCombox(nPos++);
    fData = GetRowEditFloat(nPos++);
    m_pSetpointW->wDDY_SetU = fData*100;
    fData = GetRowEditFloat(nPos++);
    m_pSetpointW->wDDY_SetI = fData*100;
    fData = GetRowEditFloat(nPos++);
    m_pSetpointW->wDDY_SetT = fData*100;
    
    m_SetpointW.INSetpoint[0].wToggle = GetRowCombox(nPos++);
    m_SetpointW.INSetpoint[1].wToggle = GetRowCombox(nPos++);
    m_SetpointW.INSetpoint[2].wToggle = GetRowCombox(nPos++);
    m_SetpointW.INSetpoint[3].wToggle = GetRowCombox(nPos++);
}

/////////////////////////////////////////////////////////////////////////////
// CMyDlgSetpoint dialog


CMyDlgSetpoint::CMyDlgSetpoint(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CMyDlgSetpoint::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDlgSetpoint)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_pDataSetpoint = NULL;
    EnableLayout();
}


void CMyDlgSetpoint::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlgSetpoint)
	DDX_Control(pDX, IDC_LIST_PARAM, m_wndLocation);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyDlgSetpoint, CBCGPDialog)
	//{{AFX_MSG_MAP(CMyDlgSetpoint)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlgSetpoint message handlers

void CMyDlgSetpoint::OnOK() 
{
	// TODO: Add extra validation here

    if(MyMessageBox("���������޸��豸��ǰ�����в���,\t\n��ȷ���Ƿ���װ?","��ע��",MB_YESNO|MB_ICONQUESTION)==IDYES)
    {
        m_wndGrid.Ctr2Mem();
        m_pDataSetpoint->StoreToDevice(m_wndGrid.m_SetpointW);
    }

// 	CDialog::OnOK();
}

BOOL CMyDlgSetpoint::OnInitDialog() 
{
	CBCGPDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    ASSERT(m_pDataSetpoint);
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
