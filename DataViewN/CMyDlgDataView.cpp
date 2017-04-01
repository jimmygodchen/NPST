// CMyDlgDataView.cpp : implementation file
//

#include "stdafx.h"
#include "CustomCells.h"
#include "CMyDlgDataView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define TIMEREFRESH         100

/////////////////////////////////////////////////////////////////////////////
// CMyDataGridCtrl sample class

CMyDataGridCtrl::CMyDataGridCtrl()
{
}

CMyDataGridCtrl::~CMyDataGridCtrl()
{
}

BEGIN_MESSAGE_MAP(CMyDataGridCtrl, CBCGPGridCtrl)
    //{{AFX_MSG_MAP(CCellTypesGridCtrl)
    ON_WM_CREATE()
    ON_WM_DESTROY()
    ON_WM_TIMER()
    //}}AFX_MSG_MAP
    ON_COMMAND_RANGE(IDC_BUTTON_OPERATESTART,IDC_BUTTON_OPERATEEND, OnOperate)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlgDataView message handlers

int CMyDataGridCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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

    InsertColumn (0, _T("名称"), 80);
    InsertColumn (1, _T("数据"), 80);
    InsertColumn (2, _T("单位"), 20);

//     SetHeaderAlign(1, HDF_RIGHT);
//     SetColumnAlign(1, HDF_RIGHT);
    if(g_MngPort.m_pPort==NULL) return 0;

    InitUpdateID();
    // Create root item:
    CBCGPGridRow* pRoot = CreateNewRow ();
    ASSERT_VALID(pRoot);
    pRoot->AllowSubItems();
    pRoot->GetItem(0)->SetValue(_T("模拟量"));
    AddRow(pRoot, FALSE);

    AddRowFloat(pRoot);

    pRoot = CreateNewRow();
    ASSERT_VALID(pRoot);
    pRoot->AllowSubItems();
    pRoot->GetItem(0)->SetValue(_T("开关量"));
    //     pRoot->GetItem(0)->AllowEdit(TRUE);
    //     pRoot->GetItem (0)->SetImage (0);
    //     pRoot->SetData();
    AddRow(pRoot, FALSE);

    AddRowBI(pRoot);

    pRoot = CreateNewRow();
    ASSERT_VALID(pRoot);
    pRoot->AllowSubItems();
    pRoot->GetItem(0)->SetValue(_T("字符"));
    //     pRoot->GetItem(0)->AllowEdit(TRUE);
    //     pRoot->GetItem (0)->SetImage (0);
    //     pRoot->SetData();
    AddRow(pRoot, FALSE);
    
    AddRowString(pRoot);

    pRoot = CreateNewRow();
    ASSERT_VALID(pRoot);
    pRoot->AllowSubItems();
    pRoot->GetItem(0)->SetValue(_T("操作"));
    AddRow(pRoot, FALSE);

    AddRowOperate(pRoot);

    SetTimer(TIMEREFRESH, 50, NULL);

    return 0;
}

void CMyDataGridCtrl::OnDestroy() 
{
    CBCGPGridCtrl::OnDestroy();
    
    KillTimer(TIMEREFRESH);
}

CBCGPGridRow* CMyDataGridCtrl::CreateNewRow(void)
{
    int nColumnCount = GetColumnCount();
    CBCGPGridRow* pRow = CreateRow(nColumnCount);
    
    for(int i=0; i<nColumnCount; i++)
    {
        pRow->GetItem(i)->AllowEdit(FALSE);
    }

    return pRow;
}

void CMyDataGridCtrl::InitUpdateID(void)
{
    m_aUpdateID.RemoveAll();
    int nSize = g_MngPort.m_pPort->m_aUnit.GetSize();
    ASSERT(nSize>0);
    nSize = g_MngPort.m_pPort->m_aUnit[0]->m_aFactory.GetSize();
    for(int i=0;i<nSize;i++)
    {
        CMyFactory* pFactory = g_MngPort.m_pPort->m_aUnit[0]->m_aFactory[i];
        ASSERT(pFactory);
        CMyData* pData = pFactory->m_pData;
        if(pData)
        {
            m_aUpdateID.Add(pData->m_dwUpdateID);
        }
    }
}

// CMyDataOperate* CMyDataGridCtrl::GetOperate(int nIndex)
// {
//     int nSize = g_MngPort.m_pPort->m_aUnit.GetSize();
//     ASSERT(nSize>0);
//     int nBottonIndex = 0;
//     nSize = g_MngPort.m_pPort->m_aUnit[0]->m_aFactory.GetSize();
//     for(int i=0;i<nSize;i++)
//     {
//         CMyFactory* pFactory = g_MngPort.m_pPort->m_aUnit[0]->m_aFactory[i];
//         ASSERT(pFactory);
//         CMyData* pData = pFactory->m_pData;
//         if(pData)
//         {
//             CRuntimeClass* pRuntimeClass = pData->GetRuntimeClass();
//             if(pRuntimeClass->IsDerivedFrom(RUNTIME_CLASS(CMyDataOperate)))
//             {
//                 if(nIndex==nBottonIndex) return (CMyDataOperate*)pData;
//                 nBottonIndex++;
//             }
//         }
//     }
//     return NULL;
// }

void CMyDataGridCtrl::OnOperate(UINT nID)
{
    int nIndex = nID - IDC_BUTTON_OPERATESTART;
    CMyDataOperate* pOperate = (CMyDataOperate*)m_aOperate[nIndex];  // GetOperate(nIndex);
    ASSERT(pOperate);
//     MessageBox(pOperate->m_strName);
    pOperate->ExeOperate();
}

void CMyDataGridCtrl::AddRowFloat(CBCGPGridRow* pRoot)
{
    int nSize = g_MngPort.m_pPort->m_aUnit.GetSize();
    ASSERT(nSize>0);
    nSize = g_MngPort.m_pPort->m_aUnit[0]->m_aFactory.GetSize();
    for(int i=0;i<nSize;i++)
    {
        CMyFactory* pFactory = g_MngPort.m_pPort->m_aUnit[0]->m_aFactory[i];
        ASSERT(pFactory);
        CMyData* pData = pFactory->m_pData;
        if(pData)
        {
            CRuntimeClass* pRuntimeClass = pData->GetRuntimeClass();
            if(pRuntimeClass->IsDerivedFrom(RUNTIME_CLASS(CMyDataVector)))
            {
                CMyDataVector* pDataVec = (CMyDataVector*)pData;
                CBCGPGridRow* pSub = CreateNewRow();
                ASSERT_VALID(pSub);
                pSub->GetItem(0)->SetValue((LPCTSTR)pData->m_strName);
                CString strVlue;
                CString strFormat;
                strFormat.Format(_T("%%.%df"),pDataVec->m_Format&0xf);
                if(pDataVec->m_nDisplayType==0)
                {
                    if(pDataVec->m_vec.m_fX>0)
                    {
                        strFormat = strFormat + _T(" + ") + strFormat + _T("i");
                    }
                    else
                    {
                        strFormat = strFormat + _T(" - ") + strFormat + _T("i");
                    }
                    strVlue.Format(strFormat, pDataVec->m_vec.m_fR, fabs(pDataVec->m_vec.m_fX));
                }
                else
                {
                    strVlue = strFormat;
                    strFormat.Format(_T("%%.%df"), pDataVec->m_AngFormat&0xf);
                    strFormat = strVlue + _T(" ∠") + strFormat + _T("°");
                    float fA, fDegree;
                    pDataVec->m_vec.GetPolar(fA, fDegree);
                    strVlue.Format(strFormat, fA, bcg_rad2deg(fDegree));
                }
                pSub->GetItem(1)->SetValue((LPCTSTR)strVlue);
                pSub->GetItem(2)->SetValue((LPCTSTR)pDataVec->m_strUnitage);
                pSub->SetData((DWORD_PTR)pData);
                pRoot->AddSubItem(pSub, FALSE);
            }
            else if(pRuntimeClass->IsDerivedFrom(RUNTIME_CLASS(CMyDataFloat)))
            {
                CMyDataFloat* pDataFloat = (CMyDataFloat*)pData;
                CBCGPGridRow* pSub = CreateNewRow();
                ASSERT_VALID(pSub);
                pSub->GetItem(0)->SetValue((LPCTSTR)pData->m_strName);
                CString strVlue;
                CString strFormat;
                strFormat.Format(_T("%%.%df"),pDataFloat->m_Format&0xf);
//                 strFormat = _T("%") + strFormat;
                strVlue.Format(strFormat, pDataFloat->m_fData);
                pSub->GetItem(1)->SetValue((LPCTSTR)strVlue);
                pSub->GetItem(2)->SetValue((LPCTSTR)pDataFloat->m_strUnitage);
                pSub->SetData((DWORD_PTR)pData);
                pRoot->AddSubItem(pSub, FALSE);
            }
        }
    }
}

void CMyDataGridCtrl::AddRowBI(CBCGPGridRow* pRoot)
{
    int nSize = g_MngPort.m_pPort->m_aUnit.GetSize();
    ASSERT(nSize>0);
    nSize = g_MngPort.m_pPort->m_aUnit[0]->m_aFactory.GetSize();
    for(int i=0;i<nSize;i++)
    {
        CMyFactory* pFactory = g_MngPort.m_pPort->m_aUnit[0]->m_aFactory[i];
        ASSERT(pFactory);
        CMyData* pData = pFactory->m_pData;
        if(pData)
        {
            CRuntimeClass* pRuntimeClass = pData->GetRuntimeClass();
            if(pRuntimeClass->IsDerivedFrom(RUNTIME_CLASS(CMyDataBin)))
            {
                CMyDataBin* pDataBin = (CMyDataBin*)pData;
                CBCGPGridRow* pSub = CreateNewRow();
                ASSERT_VALID(pSub);
                pSub->GetItem(0)->SetValue((LPCTSTR)pData->m_strName);
                pSub->GetItem(1)->SetValue(pDataBin->m_Status?_T("ON"):_T("OFF"));
                pSub->SetData((DWORD_PTR)pData);
                pRoot->AddSubItem(pSub, FALSE);
            }
        }
    }
}

void CMyDataGridCtrl::AddRowString(CBCGPGridRow* pRoot)
{
    int nSize = g_MngPort.m_pPort->m_aUnit.GetSize();
    ASSERT(nSize>0);
    nSize = g_MngPort.m_pPort->m_aUnit[0]->m_aFactory.GetSize();
    for(int i=0;i<nSize;i++)
    {
        CMyFactory* pFactory = g_MngPort.m_pPort->m_aUnit[0]->m_aFactory[i];
        ASSERT(pFactory);
        CMyData* pData = pFactory->m_pData;
        if(pData)
        {
            CRuntimeClass* pRuntimeClass = pData->GetRuntimeClass();
            if(pRuntimeClass->IsDerivedFrom(RUNTIME_CLASS(CMyDataString)))
            {
                CMyDataString* pDataStr = (CMyDataString*)pData;
                CBCGPGridRow* pSub = CreateNewRow();
                ASSERT_VALID(pSub);
                pSub->GetItem(0)->SetValue((LPCTSTR)pData->m_strName);
                pSub->GetItem(1)->SetValue((LPCTSTR)pDataStr->m_strValue);
                pSub->SetData((DWORD_PTR)pData);
                pRoot->AddSubItem(pSub, FALSE);
            }
        }
    }
}

void CMyDataGridCtrl::AddRowOperate(CBCGPGridRow* pRoot)
{
//     CBCGPGridRow* pSub = CreateNewRow();
//     ASSERT_VALID(pSub);
//     pSub->GetItem(0)->SetValue(_T("遥控1"));
//     CButtonItem* pButton = new CButtonItem (_T("遥控1!"), IDC_BUTTON_OPERATESTART);
//     pSub->ReplaceItem(1, pButton);
//     pRoot->AddSubItem (pSub, FALSE);
//     
//     pSub = CreateNewRow();
//     ASSERT_VALID(pSub);
//     pSub->GetItem(0)->SetValue(_T("遥控2"));
//     pButton = new CButtonItem (_T("遥控2!"), IDC_BUTTON_OPERATESTART+1);
//     pSub->ReplaceItem(1, pButton);
//     pRoot->AddSubItem (pSub, FALSE);
//     
//     pSub = CreateNewRow();
//     ASSERT_VALID(pSub);
//     pSub->GetItem(0)->SetValue(_T("浏览文件夹"));
//     pSub->ReplaceItem (1, new CFolderItem (_T("c:\\")));
//     pRoot->AddSubItem (pSub, FALSE);

    m_aOperate.RemoveAll();
    int nSize = g_MngPort.m_pPort->m_aUnit.GetSize();
    ASSERT(nSize>0);
    int nBottonIndex = 0;
    nSize = g_MngPort.m_pPort->m_aUnit[0]->m_aFactory.GetSize();
    for(int i=0;i<nSize;i++)
    {
        CMyFactory* pFactory = g_MngPort.m_pPort->m_aUnit[0]->m_aFactory[i];
        ASSERT(pFactory);
        CMyData* pData = pFactory->m_pData;
        if(pData)
        {
            CRuntimeClass* pRuntimeClass = pData->GetRuntimeClass();
            if(pRuntimeClass->IsDerivedFrom(RUNTIME_CLASS(CMyDataOperate)))
            {
                CMyDataOperate* pDataOperate = (CMyDataOperate*)pData;
                m_aOperate.Add(pDataOperate);
                CBCGPGridRow* pSub = CreateNewRow();
                ASSERT_VALID(pSub);
                pSub->GetItem(0)->SetValue((LPCTSTR)pData->m_strName);
                CButtonItem* pButton = new CButtonItem (pData->m_strName, IDC_BUTTON_OPERATESTART+nBottonIndex);
                nBottonIndex++;
                pSub->ReplaceItem(1, pButton);
                pSub->SetData((DWORD_PTR)pData);
                pRoot->AddSubItem(pSub, FALSE);
            }
        }
    }
}

void CMyDataGridCtrl::OnTimer(UINT_PTR nIDEvent) 
{
    CBCGPGridCtrl::OnTimer(nIDEvent);
//     CMyFactory* pFactory = g_MngPort.m_pPort->m_aUnit[0]->m_aFactory[0];
//     ASSERT(pFactory);
//     CMyData* pData = pFactory->m_pData;
//     CBCGPGridRow* pSub = FindRowByData((DWORD_PTR)pData);
//     static float fData = 5;
//     fData += 1;
//     CString strVlue;
//     strVlue.Format(_T("%.2f"), fData);
//     pSub->GetItem(1)->SetValue((LPCTSTR)strVlue);

    int nSize = g_MngPort.m_pPort->m_aUnit.GetSize();
    ASSERT(nSize>0);
    int nBottonIndex = 0;
    nSize = g_MngPort.m_pPort->m_aUnit[0]->m_aFactory.GetSize();
    for(int i=0;i<nSize;i++)
    {
        CMyFactory* pFactory = g_MngPort.m_pPort->m_aUnit[0]->m_aFactory[i];
        ASSERT(pFactory);
        CMyData* pData = pFactory->m_pData;
        if(pData)
        {
            CRuntimeClass* pRuntimeClass = pData->GetRuntimeClass();
            if(pRuntimeClass->IsDerivedFrom(RUNTIME_CLASS(CMyDataVector)))
            {
                if(m_aUpdateID[i]!=pData->m_dwUpdateID)             // 有更新
                {
                    m_aUpdateID[i] = pData->m_dwUpdateID;
                    CMyDataVector* pDataVec = (CMyDataVector*)pData;
                    CBCGPGridRow* pSub = FindRowByData((DWORD_PTR)pData);
                    ASSERT(pSub);
                    CString strVlue;
                    CString strFormat;
                    strFormat.Format(_T("%%.%df"), pDataVec->m_Format&0xf);
                    if(pDataVec->m_nDisplayType==0)
                    {
                        if(pDataVec->m_vec.m_fX>0)
                        {
                            strFormat = strFormat + _T(" + ") + strFormat + _T("i");
                        }
                        else
                        {
                            strFormat = strFormat + _T(" - ") + strFormat + _T("i");
                        }
                        strVlue.Format(strFormat, pDataVec->m_vec.m_fR, fabs(pDataVec->m_vec.m_fX));
                    }
                    else
                    {
                        strVlue = strFormat;
                        strFormat.Format(_T("%%.%df"), pDataVec->m_AngFormat&0xf);
                        strFormat = strVlue + _T(" ∠") + strFormat;
                        float fA, fDegree;
                        pDataVec->m_vec.GetPolar(fA, fDegree);
                        strVlue.Format(strFormat, fA, bcg_rad2deg(fDegree));
                    }
                    pSub->GetItem(1)->SetValue((LPCTSTR)strVlue);
                }
            }
            else if(pRuntimeClass->IsDerivedFrom(RUNTIME_CLASS(CMyDataFloat)))
            {
                if(m_aUpdateID[i]!=pData->m_dwUpdateID)             // 有更新
                {
                    m_aUpdateID[i] = pData->m_dwUpdateID;
                    CBCGPGridRow* pSub = FindRowByData((DWORD_PTR)pData);
                    ASSERT(pSub);
                    CString strVlue;
                    CString strFormat;
                    strFormat.Format(_T("%%.%df"), ((CMyDataFloat*)pData)->m_Format&0xf);
                    strVlue.Format(strFormat, ((CMyDataFloat*)pData)->m_fData);
                    pSub->GetItem(1)->SetValue((LPCTSTR)strVlue);
                }
            }
            if(pRuntimeClass->IsDerivedFrom(RUNTIME_CLASS(CMyDataBin)))
            {
                if(m_aUpdateID[i]!=pData->m_dwUpdateID)             // 有更新
                {
                    m_aUpdateID[i] = pData->m_dwUpdateID;
                    CBCGPGridRow* pSub = FindRowByData((DWORD_PTR)pData);
                    pSub->GetItem(1)->SetValue(((CMyDataBin*)pData)->m_Status?_T("ON"):_T("OFF"));
                }
            }
            if(pRuntimeClass->IsDerivedFrom(RUNTIME_CLASS(CMyDataString)))
            {
                if(m_aUpdateID[i]!=pData->m_dwUpdateID)             // 有更新
                {
                    m_aUpdateID[i] = pData->m_dwUpdateID;
                    CBCGPGridRow* pSub = FindRowByData((DWORD_PTR)pData);
                    pSub->GetItem(1)->SetValue((LPCTSTR)((CMyDataString*)pData)->m_strValue);
                }
            }
        }
    }

}

// =================================================================================
CMyDlgDataView::CMyDlgDataView(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CMyDlgDataView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDlgDataView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    EnableLayout ();
}


void CMyDlgDataView::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlgDataView)
	DDX_Control(pDX, IDC_DATAVIEW, m_wndLocationFloat);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyDlgDataView, CBCGPDialog)
	//{{AFX_MSG_MAP(CMyDlgDataView)
// 	ON_WM_SIZE()
	//}}AFX_MSG_MAP
//    ON_MESSAGE(WM_INITDIALOG, HandleInitDialog)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlgDataView message handlers

BOOL CMyDlgDataView::OnInitDialog() 
{
	CBCGPDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

    CWaitCursor wait;

    // Create grid tree:
    CRect rectGrid;
    m_wndLocationFloat.GetClientRect (&rectGrid);
    m_wndLocationFloat.MapWindowPoints (this, &rectGrid);
    
    m_wndGridFloat.Create (WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rectGrid, this, IDC_DATAVIEW);
    
    // Set grid colors
    CBCGPGridColors colors;
    colors.m_LeftOffsetColors.m_clrBackground = globalData.clrWindow;
    m_wndGridFloat.SetColorTheme (colors);

    CBCGPGridColors theme;
    CBCGPVisualManager::GetInstance ()->OnSetGridColorTheme(&m_wndGridFloat, theme);
    //     m_wndGridFloat.SendMessage(BCGM_ONSETCONTROLVMMODE, TRUE);
    m_wndGridFloat.SetColorTheme(theme);

    CBCGPStaticLayout* pLayout = (CBCGPStaticLayout*)GetLayout();
    if(pLayout != NULL)
    {
        pLayout->AddAnchor(IDC_DATAVIEW, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeBoth);
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

