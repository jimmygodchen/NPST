// CMyDisPlayInfo.cpp : implementation file
//

#include "stdafx.h"
#include "WaveForm.h"
#include "WaveFormDoc.h"
#include "WaveFormView.h"
#include "CMyDisPlayInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDisPlayInfo dialog


CMyDisPlayInfo::CMyDisPlayInfo(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CMyDisPlayInfo::IDD, pParent)
{
    //{{AFX_DATA_INIT(CMyDisPlayInfo)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
    EnableVisualManagerStyle(TRUE, TRUE);
//     m_pToolTip = NULL;
}


void CMyDisPlayInfo::DoDataExchange(CDataExchange* pDX)
{
    CBCGPDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CMyDisPlayInfo)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    DDX_Control(pDX, IDC_LIST_SET, m_listSet);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyDisPlayInfo, CBCGPDialog)
	//{{AFX_MSG_MAP(CMyDisPlayInfo)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SET, OnDblclkListSet)
// 	ON_WM_CREATE()
// 	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDisPlayInfo message handlers

BOOL CMyDisPlayInfo::OnInitDialog() 
{
	CBCGPDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    DWORD dwExtendedStyle = m_listSet.GetExtendedStyle();
    m_listSet.SetExtendedStyle(dwExtendedStyle|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
    m_listSet.InsertColumn(0, _T("序号"), LVCFMT_CENTER, 40);
    m_listSet.InsertColumn(1, _T("通道名称"), LVCFMT_LEFT, 200);
    m_listSet.InsertColumn(2, _T("可见"), LVCFMT_LEFT, 40);
//     m_listSet.InsertColumn(2,"值",LVCFMT_LEFT,80);
    ASSERT(m_pDoc);
    int nBINO = m_pDoc->m_Wave.m_NumChannelDI;
    int nAINO = m_pDoc->m_Wave.m_NumChannelAD;

    CString strItem;
    for(int i=0;i<nAINO;++i)
    {
        strItem.Format(_T("%d"), i+1);
        m_listSet.InsertItem(i,strItem);
        strItem = m_pDoc->m_Wave.m_astrNameAD[i];
        m_listSet.SetItemText(i, 1, strItem);
        strItem = m_aCHDisplalyInfo[i].bVisible?_T("√"):_T("×");
        m_listSet.SetItemText(i, 2, strItem);
    }
    for(i=0;i<nBINO;++i)
    {
        strItem.Format(_T("%d"), i+nAINO+1);
        m_listSet.InsertItem(i+nAINO,strItem);
        strItem = m_pDoc->m_Wave.m_astrNameDI[i];
        m_listSet.SetItemText(i+nAINO, 1, strItem);
        strItem = m_aCHDisplalyInfo[i+nAINO].bVisible?_T("√"):_T("×");
        m_listSet.SetItemText(i+nAINO, 2, strItem);
    }

//     CRect rcClient;
//     GetClientRect(rcClient);
//     m_pToolTip->AddTool(GetDlgItem(IDC_LIST_SET), _T("双击修改通道显示状态!"));
//     CBCGPToolTipCtrl* pToolTip = DYNAMIC_DOWNCAST(CBCGPToolTipCtrl, m_pToolTip);

//     globalData.m_nMaxToolTipWidth = 200;
//     pToolTip->Activate(TRUE);

//     CBCGPToolTipParams params;
//     params.m_bBallonTooltip = TRUE;
//     params.m_bDrawSeparator = TRUE;
//     params.m_bVislManagerTheme = TRUE;
//     pToolTip->SetParams (&params);

    m_ToolTip.Create(this);
    m_ToolTip.Activate(TRUE);
    
    CBCGPToolTipParams params;
    params.m_bVislManagerTheme = TRUE;
    
    m_ToolTip.SetParams (&params);
    
    // TODO: Use one of the following forms to add controls:
    m_ToolTip.AddTool (GetDlgItem(IDC_LIST_SET), _T("双击修改通道显示状态！"));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMyDisPlayInfo::OnDblclkListSet(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    ASSERT(pNMListView);
    int nRow = pNMListView->iItem;
    if(nRow>-1)
    {
        m_aCHDisplalyInfo[nRow].bVisible = !m_aCHDisplalyInfo[nRow].bVisible;
        CString strItem = m_aCHDisplalyInfo[nRow].bVisible?_T("√"):_T("×");
        m_listSet.SetItemText(nRow, 2, strItem);
    }
    *pResult = 0;
}

// int CMyDisPlayInfo::OnCreate(LPCREATESTRUCT lpCreateStruct) 
// {
// 	if (CBCGPDialog::OnCreate(lpCreateStruct) == -1)
// 		return -1;
// 	
// 	// TODO: Add your specialized creation code here
//     CBCGPTooltipManager::CreateToolTip(m_pToolTip, this, BCGP_TOOLTIP_TYPE_DEFAULT/*BCGP_TOOLTIP_TYPE_ALL*/);
//     ASSERT_VALID(m_pToolTip);
// 	return 0;
// }
// 
// void CMyDisPlayInfo::OnDestroy() 
// {
//     CBCGPTooltipManager::DeleteToolTip(m_pToolTip);
// 
// 	CBCGPDialog::OnDestroy();
// 	
// 	// TODO: Add your message handler code here
// 	
// }

BOOL CMyDisPlayInfo::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
//     if(m_pToolTip->GetSafeHwnd()!=NULL)
//         m_pToolTip->RelayEvent(pMsg);

    switch (pMsg->message)
    {
    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:
    case WM_MOUSEMOVE:
//         if(m_pToolTip->GetSafeHwnd()!=NULL)
//         {
//             m_pToolTip->RelayEvent(pMsg);
//         }
        m_ToolTip.RelayEvent(pMsg);
        break;
    }
	return CBCGPDialog::PreTranslateMessage(pMsg);
}

