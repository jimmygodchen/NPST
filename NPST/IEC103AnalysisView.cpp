// IEC103AnalysisView.cpp : implementation of the CIEC103AnalysisView class
//

#include "stdafx.h"
#include <mmsystem.h>
#include "MainFrm.h"
#include "CMyConfig.h"
#include "IEC103Analysis.h"

#include "IEC103AnalysisDoc.h"
#include "CntrItem.h"
#include "IEC103AnalysisView.h"

// #include "CMyCOMCfg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIEC103AnalysisView

#define LINE_LIMIT		3000				// CRichView显示最大行数

IMPLEMENT_DYNCREATE(CIEC103AnalysisView, CRichEditView)

BEGIN_MESSAGE_MAP(CIEC103AnalysisView, CRichEditView)
	//{{AFX_MSG_MAP(CIEC103AnalysisView)
	ON_WM_DESTROY()
// 	ON_WM_TIMER()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
	ON_WM_CONTEXTMENU()
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)

	ON_COMMAND(IDC_BUTTON_CLEARCNT,OnClearCnt)
	ON_COMMAND(IDC_BUTTON_CLEARTEXT,OnClearTXT)
	ON_COMMAND(IDC_BUTTON_COMCFG,OnCOMCfg)
	ON_UPDATE_COMMAND_UI(IDC_BUTTON_COMCFG,OnUpdateCOMCfg)
    ON_COMMAND(IDC_BUTTON_UNITSEL,OnUnitCfg)
    ON_UPDATE_COMMAND_UI(IDC_BUTTON_UNITSEL,OnUpdateUnitCfg)

    ON_COMMAND(IDC_BUTTON_COPYRIGHT,OnCopyright)

    ON_COMMAND(IDC_COMBO_COMSEL, OnComSel)
    ON_CBN_SELENDOK(IDC_COMBO_COMSEL, OnComSel)
    ON_UPDATE_COMMAND_UI(IDC_COMBO_COMSEL, OnUpdateCOMCfg)

    ON_COMMAND(IDC_COMBO_UNITSEL, OnComSel)
    ON_CBN_SELENDOK(IDC_COMBO_UNITSEL, OnComSel)
    ON_UPDATE_COMMAND_UI(IDC_COMBO_UNITSEL, OnUpdateUnitCfg)

    ON_COMMAND_RANGE(IDC_BUTTON_PLAY,IDC_BUTTON_STOP, OnCOMOperate)
    ON_UPDATE_COMMAND_UI_RANGE(IDC_BUTTON_PLAY,IDC_BUTTON_STOP, OnUpdateCOMOperate)

    ON_COMMAND(IDC_BUTTON_VIEWUNITDATA, OnViewUnitData)
    ON_UPDATE_COMMAND_UI(IDC_BUTTON_VIEWUNITDATA, OnUpdateViewUnitData)

    ON_MESSAGE(WM_PORTMSG, OnPortMsg)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIEC103AnalysisView construction/destruction

CIEC103AnalysisView::CIEC103AnalysisView()
{
    // TODO: add construction code here
}

CIEC103AnalysisView::~CIEC103AnalysisView()
{
}

BOOL CIEC103AnalysisView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

// 	return CRichEditView::PreCreateWindow(cs);
	BOOL bRes = CRichEditView::PreCreateWindow(cs);
	cs.style |= ES_SELECTIONBAR;
	return bRes;
}

static int GetTwipSize (CString str)
{
	LPCTSTR lpszText = str;
	
	while (*lpszText == ' ' || *lpszText == '\t')
		lpszText++;
	
	if (lpszText[0] == NULL)
		return -1; // no text in control
	
	double d = _tcstod(lpszText, (LPTSTR*)&lpszText);
	while (*lpszText == ' ' || *lpszText == '\t')
		lpszText++;
	
	if (*lpszText != NULL)
		return -2;   // not terminated properly
	
	return (d<0.) ? 0 : (int)(d*20.);
}

void CIEC103AnalysisView::OnInitialUpdate()
{
    CRichEditView::OnInitialUpdate();

    CMyConfig Cfg(_T("NPST"));
    Cfg.Load();

    // Set the printing margins (720 twips = 1/2 inch).
    SetMargins(CRect(720, 720, 720, 720));

    CBCGPRibbonBar* pRibbon = ((CMainFrame*) GetTopLevelFrame ())->GetRibbonBar ();
    ASSERT_VALID (pRibbon);
    
    CBCGPRibbonComboBox* pComSelCombo = DYNAMIC_DOWNCAST (CBCGPRibbonComboBox, pRibbon->FindByID (IDC_COMBO_COMSEL));
    if(pComSelCombo != NULL && !pComSelCombo->HasFocus ())
    {
        int nSize = CMyPort::s_aType.GetSize();
        int nIndex = -1;
        for(int i=0;i<nSize;i++)
        {
            CString strType = CMyPort::s_aType[i];
            pComSelCombo->AddItem(strType);
            if(!Cfg.m_strPortName.IsEmpty() && strType==Cfg.m_strPortName)
            {
                nIndex = i;
            }
        }
        pComSelCombo->SelectItem(nIndex);
    }

    CBCGPRibbonComboBox* pUnitSelCombo = DYNAMIC_DOWNCAST (CBCGPRibbonComboBox, pRibbon->FindByID (IDC_COMBO_UNITSEL));
    if(pUnitSelCombo != NULL && !pUnitSelCombo->HasFocus ())
    {
        int nSize = CMyUnit::s_aType.GetSize();
        int nIndex = -1;
        for(int i=0;i<nSize;i++)
        {
            CString strType = CMyUnit::s_aType[i];
            CString strOEMType;
            if(DeviceType2OEMType(strType,strOEMType))
            {
                pUnitSelCombo->AddItem(strOEMType);
            }
            else
            {
                pUnitSelCombo->AddItem(strType);
            }
            if(!Cfg.m_strUnitName.IsEmpty() && strType==Cfg.m_strUnitName)
            {
                nIndex = i;
            }
        }
        pUnitSelCombo->SelectItem(nIndex);
    }

    CHARFORMATA cf;
    CRichEditCtrl& wndRichEdit = GetRichEditCtrl();

    wndRichEdit.SetRedraw(FALSE);

    cf.cbSize = sizeof(CHARFORMAT);
    cf.dwMask = CFM_BOLD|CFM_SIZE|CFM_FACE|CFM_COLOR;
    cf.crTextColor = RGB(255,0,0);
    lstrcpyn(cf.szFaceName,"宋体",5);
    cf.yHeight = GetTwipSize("10");
    cf.dwEffects = 0;
    wndRichEdit.SetWordCharFormat(cf);
    wndRichEdit.SetRedraw(TRUE);
    wndRichEdit.RedrawWindow();
}

/////////////////////////////////////////////////////////////////////////////
// CIEC103AnalysisView printing

void CIEC103AnalysisView::OnFilePrintPreview() 
{
	BCGPPrintPreview (this);
}

BOOL CIEC103AnalysisView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CIEC103AnalysisView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used.
    CRichEditView::OnDestroy();
    COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
    if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
    {
        pActiveItem->Deactivate();
        ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
    }

    CMyConfig Cfg(_T("NPST"));
    int nSize, nType = -1;

    CBCGPRibbonBar* pRibbon = ((CMainFrame*) GetTopLevelFrame ())->GetRibbonBar ();
    ASSERT_VALID (pRibbon);
    
    CBCGPRibbonComboBox* pComSelCombo = DYNAMIC_DOWNCAST (CBCGPRibbonComboBox, pRibbon->FindByID (IDC_COMBO_COMSEL));
    if(pComSelCombo != NULL)
    {
        nType = pComSelCombo->GetCurSel();
    }
    
    nSize = CMyPort::s_aType.GetSize();
    ASSERT(nSize>0);
    if(nType<nSize && nType>=0)
    {
        Cfg.m_strPortName = CMyPort::s_aType[nType];
    }

    CBCGPRibbonComboBox* pUnitSelCombo = DYNAMIC_DOWNCAST (CBCGPRibbonComboBox, pRibbon->FindByID (IDC_COMBO_UNITSEL));
    if(pUnitSelCombo != NULL)
    {
        nType = pUnitSelCombo->GetCurSel();
    }

    nSize = CMyUnit::s_aType.GetSize();
    ASSERT(nSize>0);
    if(nType<nSize && nType>=0)
    {
        Cfg.m_strUnitName = CMyUnit::s_aType[nType];
    }
    Cfg.Store();

    if(g_MngPort.m_pPort)
    {
        g_MngPort.CloseAllPorts();
        delete g_MngPort.m_pPort;
        g_MngPort.m_pPort = NULL;
    }
}


/////////////////////////////////////////////////////////////////////////////
// CIEC103AnalysisView diagnostics

#ifdef _DEBUG
void CIEC103AnalysisView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CIEC103AnalysisView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CIEC103AnalysisDoc* CIEC103AnalysisView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIEC103AnalysisDoc)));
	return (CIEC103AnalysisDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIEC103AnalysisView message handlers

void CIEC103AnalysisView::OnContextMenu(CWnd*, CPoint point)
{
	theApp.ShowPopupMenu (IDR_CONTEXT_MENU, point, this);
}

void CIEC103AnalysisView::OnClearCnt()
{
// 	m_lRxCnt = 0;
// 	m_lTxCnt = 0;
// 	CMainFrame *pFrame=(CMainFrame*)GetParent();
// 	CBCGPRibbonStatusBarPane* pPanel = (CBCGPRibbonStatusBarPane*)pFrame->m_wndStatusBar.GetElement(0);
// 
// 	CString str;
// 	str.Format("RX:%ld,TX:%ld",m_lRxCnt,m_lTxCnt);
// 	pPanel->SetText(str);
// 	pPanel->Redraw();
}

void CIEC103AnalysisView::OnClearTXT()
{
    CRichEditCtrl& wndRichEdit = GetRichEditCtrl();

    wndRichEdit.SetRedraw(FALSE);

    int nTextLength = wndRichEdit.GetWindowTextLength();
    wndRichEdit.SetSel(0, nTextLength);
    wndRichEdit.Clear();

    wndRichEdit.SetRedraw(TRUE);
    wndRichEdit.RedrawWindow();
}

void CIEC103AnalysisView::OnCOMCfg()
{
    CMyPort* pPort = NULL;

    int nComType = -1;
    CString strType = _T("");

    CBCGPRibbonBar* pRibbon = ((CMainFrame*) GetTopLevelFrame ())->GetRibbonBar ();
    ASSERT_VALID (pRibbon);
    
    CBCGPRibbonComboBox* pComSelCombo = DYNAMIC_DOWNCAST(CBCGPRibbonComboBox, pRibbon->FindByID (IDC_COMBO_COMSEL));
    if(pComSelCombo != NULL)
    {
        nComType = pComSelCombo->GetCurSel();
    }
    int nSize = CMyPort::s_aType.GetSize();
    ASSERT(nSize>0);
    if(nComType>=nSize || nComType<0) nComType = 0;
    strType = CMyPort::s_aType[nComType];

    CRuntimeClass* pRuntimeClass = (CRuntimeClass*)CMyPort::s_mapTypeToClass[strType];

    ASSERT(pRuntimeClass->IsDerivedFrom(RUNTIME_CLASS(CMyPort)));
    pPort = (CMyPort*)(pRuntimeClass->CreateObject());

    ASSERT(pPort);
    pPort->m_strName = strType;
    pPort->Load();
    pPort->OnAttrib();
    pPort->Store();

    delete pPort;
//     pPort = NULL;
}

void CIEC103AnalysisView::OnUpdateCOMCfg(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(g_MngPort.m_pPort==NULL);
}

void CIEC103AnalysisView::OnUnitCfg()
{
    CMyUnit* pUnit = NULL;

    int nUnitType = -1;
    CString strType = _T("");
    
    CBCGPRibbonBar* pRibbon = ((CMainFrame*) GetTopLevelFrame ())->GetRibbonBar ();
    ASSERT_VALID (pRibbon);
    
    CBCGPRibbonComboBox* pUnitSelCombo = DYNAMIC_DOWNCAST(CBCGPRibbonComboBox, pRibbon->FindByID (IDC_COMBO_UNITSEL));
    if(pUnitSelCombo != NULL)
    {
        nUnitType = pUnitSelCombo->GetCurSel();
    }
    int nSize = CMyUnit::s_aType.GetSize();
    ASSERT(nSize>0);
    if(nUnitType>=nSize || nUnitType<0) nUnitType = 0;
    strType = CMyUnit::s_aType[nUnitType];
    
    CRuntimeClass* pRuntimeClass = (CRuntimeClass*)CMyUnit::s_mapTypeToClass[strType];
    
    ASSERT(pRuntimeClass->IsDerivedFrom(RUNTIME_CLASS(CMyUnit)));
    pUnit = (CMyUnit*)(pRuntimeClass->CreateObject());
    
    ASSERT(pUnit);
    pUnit->m_strName = strType;
    pUnit->Load();
    pUnit->OnAttrib();
    pUnit->Store();

    delete pUnit;
}

void CIEC103AnalysisView::OnUpdateUnitCfg(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(g_MngPort.m_pPort==NULL);
}

void CIEC103AnalysisView::OnCOMOperate(UINT nID)
{
    switch(nID)
    {
    case IDC_BUTTON_PLAY:
        {
            CBCGPRibbonBar* pRibbon = ((CMainFrame*) GetTopLevelFrame ())->GetRibbonBar ();
            ASSERT_VALID (pRibbon);
            
            int nType = -1;
            CString strType = _T("");

            CBCGPRibbonComboBox* pCombo = DYNAMIC_DOWNCAST(CBCGPRibbonComboBox, pRibbon->FindByID (IDC_COMBO_UNITSEL));
            if(pCombo != NULL)
            {
                nType = pCombo->GetCurSel();
            }
            int nSize = CMyUnit::s_aType.GetSize();
            ASSERT(nSize>0);
            if(nType<0)
            {
                MessageBox(_T("请选择测试单元！"), "提示", MB_OK|MB_ICONWARNING);
                return;
            }
            if(nType>=nSize || nType<0) nType = 0;
            strType = CMyUnit::s_aType[nType];

            CRuntimeClass* pRuntimeClass = (CRuntimeClass*)CMyUnit::s_mapTypeToClass[strType];
            
            ASSERT(pRuntimeClass->IsDerivedFrom(RUNTIME_CLASS(CMyUnit)));
            CMyUnit* pUnit = (CMyUnit*)(pRuntimeClass->CreateObject());
            
            ASSERT(pUnit);
            pUnit->m_strName = strType;

            nType = 0;
            strType = _T("");

            pCombo = DYNAMIC_DOWNCAST(CBCGPRibbonComboBox, pRibbon->FindByID (IDC_COMBO_COMSEL));
            if(pCombo != NULL)
            {
                nType = pCombo->GetCurSel();
            }
            nSize = CMyPort::s_aType.GetSize();
            ASSERT(nSize>0);
            if(nType<0)
            {
                MessageBox(_T("请选择通讯端口！"), "提示", MB_OK|MB_ICONWARNING);
                return;
            }
            if(nType>=nSize || nType<0) nType = 0;
            strType = CMyPort::s_aType[nType];

            pRuntimeClass = (CRuntimeClass*)CMyPort::s_mapTypeToClass[strType];
            
            ASSERT(pRuntimeClass->IsDerivedFrom(RUNTIME_CLASS(CMyPort)));
            CMyPort* pPort = (CMyPort*)(pRuntimeClass->CreateObject());

            ASSERT(pPort);
            pPort->m_strName = strType;
            pPort->m_nID = 0;
            pPort->Load();
            pPort->m_pwndMsg = this;
            pPort->OnCreate();

            g_MngEvent.Empty();
//             g_MngEvent.m_pwndMsg = &((CMainFrame*) GetTopLevelFrame ())->m_wndOutput;
            g_MngEvent.m_pwndMsg = &((CMainFrame*)AfxGetMainWnd())->m_wndOutput;

            pUnit->m_pParentPort = pPort;
            pUnit->Load();
            pUnit->OnCreate();
            pPort->m_aUnit.Add(pUnit);

            g_MngPort.m_pPort = pPort;
            g_MngPort.OpenAllPorts();
        }
        break;
    case IDC_BUTTON_STOP:
        {
            if(g_MngPort.m_pPort)
            {
                g_MngPort.CloseAllPorts();
                delete g_MngPort.m_pPort;
                g_MngPort.m_pPort = NULL;
            }
        }
        break;
    }
}

void CIEC103AnalysisView::OnUpdateCOMOperate(CCmdUI* pCmdUI)
{
    BOOL bEnale[2] = { TRUE,FALSE};
    if(g_MngPort.m_pPort==NULL)
    {
        bEnale[0] = TRUE;
        bEnale[1] = FALSE;
    }
    else
    {
        bEnale[0] = FALSE;
        bEnale[1] = TRUE;
    }

    UINT nID = pCmdUI->m_nID-IDC_BUTTON_PLAY;
    pCmdUI->Enable(bEnale[nID]);
}


void CIEC103AnalysisView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
// 	CRichEditView::OnRButtonUp(nFlags, point);
	long nStartChar, nEndChar;
	GetRichEditCtrl().GetSel(nStartChar, nEndChar);
	if (nEndChar - nStartChar <= 1)
	{
		SendMessage (WM_LBUTTONDOWN, nFlags, MAKELPARAM (point.x, point.y));
	}
	
	CPoint ptScreen = point;
	ClientToScreen (&ptScreen);
	
	if (!ShowContextMenu (ptScreen))
	{
		Default ();
	}
}

BOOL CIEC103AnalysisView::ShowContextMenu (CPoint point)
{
	if (DYNAMIC_DOWNCAST (CBCGPFrameWnd, GetParentFrame ()) == NULL)
	{
		// Maybe, server mode, show the regular menu!
		return FALSE;
	}
	
	CRichEditCntrItem* pItem = GetSelectedItem();
	if (pItem == NULL || !pItem->IsInPlaceActive())
	{
		theApp.ShowPopupMenu (IDR_CONTEXT_MENU, point, this);
		return TRUE;
	}
	
	return FALSE;
}

void CIEC103AnalysisView::ShowCommData(CString str, COLORREF cr)
{
    CRichEditCtrl& wndRichEdit = GetRichEditCtrl();
    wndRichEdit.SetRedraw(FALSE);
    
    int nTextLength = wndRichEdit.GetWindowTextLength();
    int nLineCnt = wndRichEdit.GetLineCount();
    if(nLineCnt>LINE_LIMIT)
    {
        wndRichEdit.SetSel(0, nTextLength);
        wndRichEdit.Clear();
    }
    nTextLength = wndRichEdit.GetWindowTextLength();
    
    wndRichEdit.SetSel(nTextLength, nTextLength);

    OnColorPick(cr);
    
    wndRichEdit.ReplaceSel(str);
    
    wndRichEdit.SetRedraw(TRUE);
    wndRichEdit.RedrawWindow();
}

LONG CIEC103AnalysisView::OnPortMsg(WPARAM wParm, LPARAM lParam)
{
    int nPortID = (int)lParam;
    CMyPort* pPort = g_MngPort.GetPort(nPortID);
    if(pPort)
    {
        PORTMSG PortMsg;
        while(pPort->GetMsg(PortMsg))
        {
            ShowCommData(PortMsg.strContent, PortMsg.clrColor);
        }
    }

    return 0;
}

void CIEC103AnalysisView::OnViewUnitData()
{
    if(g_pDataView)
    {
        g_pDataView->OnViewData();
    }
}

void CIEC103AnalysisView::OnUpdateViewUnitData(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(g_MngPort.m_pPort!=NULL);
}


