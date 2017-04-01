// CMyDlgRTWave.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Pub.h"
#include "CMyDlgRTWave.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDlgRTWave dialog


CMyDlgRTWave::CMyDlgRTWave(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CMyDlgRTWave::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDlgRTWave)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    EnableVisualManagerStyle();
    EnableLayout();
//     SetWhiteBackground();
    m_dwUpdateID = 0;
    m_pSerAI = NULL;
    m_bRemoveDC = TRUE;
}


void CMyDlgRTWave::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlgRTWave)
		// NOTE: the ClassWizard will add DDX and DDV calls here
    DDX_Control(pDX, IDC_CHART, m_wndChart);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyDlgRTWave, CBCGPDialog)
	//{{AFX_MSG_MAP(CMyDlgRTWave)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
    ON_COMMAND_RANGE(ID_MENUITEM_CH0, ID_MENUITEM_CH20, OnCHSet)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlgRTWave message handlers

BOOL CMyDlgRTWave::OnInitDialog() 
{
	CBCGPDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    ASSERT(m_pRTWave);
     CWaitCursor wait;

     CBCGPStaticLayout* pLayout = (CBCGPStaticLayout*)GetLayout();
     if(pLayout != NULL)
     {
         pLayout->AddAnchor(IDC_CHART, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeBoth);
         pLayout->AddAnchor(IDCANCEL, CBCGPStaticLayout::e_MoveTypeBoth, CBCGPStaticLayout::e_SizeTypeNone);
    }

    GetParentFrame()->RecalcLayout();
    
    CBCGPChartVisualObject* pChart = m_wndChart.GetChart();
    ASSERT_VALID(pChart);

    CBCGPChartAxis* pXAxis = pChart->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
    ASSERT_VALID(pXAxis);
    pXAxis->m_axisNameFormat.m_textFormat = CBCGPTextFormat(
        _T("Arial"), 12., FW_REGULAR, CBCGPTextFormat::BCGP_FONT_STYLE_NORMAL);

    AddWave();

    SetTimer(1, 100, NULL);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CMyDlgRTWave::AddWave(void)
{
    CBCGPChartVisualObject* pChart = m_wndChart.GetChart();
    ASSERT_VALID(pChart);
    int nChNum = m_pRTWave->GetChNum();
    m_pSerAI = new CBCGPChartSeries*[nChNum];
    ASSERT(m_pSerAI);
    for(int i=0;i<nChNum;++i)
    {
        tRTWAVECHINFO ChInfo = m_pRTWave->GetChInfo(i);
        m_pSerAI[i] = pChart->CreateSeries(ChInfo.pszChName);
        ASSERT_VALID(m_pSerAI[i]);
        m_pSerAI[i]->SetCurveType(BCGPChartFormatSeries::CCT_LINE);
    }
    int nDotNum = m_pRTWave->GetDotNum();
    for(i=0;i<nChNum;i++)
    {
        const float* pAI = m_pRTWave->GetBuff(i);
        float fDC = 0;
        int j;
        if(m_bRemoveDC)
        {
            for(j=0;j<nDotNum;++j)
            {
                fDC += pAI[j];
            }
            fDC = fDC/nDotNum;
        }
        for(j=0;j<nDotNum;++j)
        {
            m_pSerAI[i]->AddDataPoint(pAI[j] - fDC, j);
        }
    }
    ShowWave();
}

void CMyDlgRTWave::ShowWave(void)
{
    CBCGPChartVisualObject* pChart = m_wndChart.GetChart();
    ASSERT_VALID(pChart);
    int nChNum = m_pRTWave->GetChNum();
    for(int i=0;i<nChNum;i++)
    {
        tRTWAVECHINFO ChInfo = m_pRTWave->GetChInfo(i);
        pChart->ShowSeries(ChInfo.bVisible, i);
    }
//     pChart->SetZoomScrollConfig(BCGPChartMouseConfig::ZSO_NONE);
    pChart->SetAutoDisplayRange(TRUE, TRUE);

//     CBCGPChartAxis* pXAxis = pChart->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
//     ASSERT_VALID(pXAxis);
//     pXAxis->ShowScrollBar(m_bZoom);
//     pXAxis->SetMaxZoomInFactor(20); // allow more details on X axis
    
    // X Axis should be always at the diagram bottom along with its labels
//     pXAxis->m_crossType = CBCGPChartAxis::CT_FIXED_DEFAULT_POS;             // 坐标轴放到最下方
//     pXAxis->m_axisLabelType = CBCGPChartAxis::ALT_LOW;                      // 坐标轴标签放到最下方

    pChart->SetDirty(TRUE, TRUE);
//     pChart->Redraw();
}

void CMyDlgRTWave::OnDestroy() 
{
    CBCGPDialog::OnDestroy();

    // TODO: Add your message handler code here
    KillTimer(1);
    if(m_pSerAI)
    {
        delete [] m_pSerAI;
        m_pSerAI = NULL;
    }
}

void CMyDlgRTWave::OnTimer(UINT nIDEvent) 
{
    // TODO: Add your message handler code here and/or call default
    if(nIDEvent==1)
    {
        if(m_dwUpdateID==m_pRTWave->m_dwUpdateID)
        {
            m_pRTWave->SetOperateCode();
        }
        else
        {
            m_dwUpdateID = m_pRTWave->m_dwUpdateID;
            Refresh();
        }
    }

    CBCGPDialog::OnTimer(nIDEvent);
}

void CMyDlgRTWave::Refresh(void)
{
    CBCGPChartVisualObject* pChart = m_wndChart.GetChart();
    ASSERT_VALID(pChart);
    int nChNum = m_pRTWave->GetChNum();
    ASSERT(m_pSerAI);
    int nDotNum = m_pRTWave->GetDotNum();
    for(int i=0;i<nChNum;i++)
    {
        tRTWAVECHINFO ChInfo = m_pRTWave->GetChInfo(i);
        if(ChInfo.bVisible==FALSE) continue;
        const float* pAI = m_pRTWave->GetBuff(i);
        float fDC = 0;
        int j;
        if(m_bRemoveDC)
        {
            for(j=0;j<nDotNum;++j)
            {
                fDC += pAI[j];
            }
            fDC = fDC/nDotNum;
        }
        for(j=0;j<nDotNum;++j)
        {
            m_pSerAI[i]->SetDataPointValue(j, pAI[j] - fDC, CBCGPChartData::CI_Y);
//            pChart->SetChartData(pAI[j], i, j, CBCGPChartData::CI_Y);
        }
    }
    ShowWave();
}

BOOL CMyDlgRTWave::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
    int i;
    if(pMsg->message==WM_RBUTTONUP)
    {
        CPoint curPoint;
        GetCursorPos(&curPoint);
//         ClientToScreen (&curPoint);
        CMenu Popup;
        if(!Popup.LoadMenu(IDR_MENU_POPUP))
        {
            ASSERT(FALSE);
        }
        CMenu* pMenu = Popup.GetSubMenu(0);
        int nSize = pMenu->GetMenuItemCount();
        for(i=nSize-1;i>=0;i--) pMenu->DeleteMenu(i, MF_BYPOSITION);

        nSize = m_pRTWave->GetChNum();
        UINT nFlag = MF_BYCOMMAND;
        if(m_bRemoveDC) nFlag = MF_BYCOMMAND|MF_CHECKED;
        else nFlag = MF_BYCOMMAND|MF_UNCHECKED;
        pMenu->AppendMenu(nFlag, ID_MENUITEM_CH0, _T("去除直流分量"));
        for(i=0;i<nSize;i++)
        {
            tRTWAVECHINFO ChInfo = m_pRTWave->GetChInfo(i);
            UINT nFlag = MF_BYCOMMAND;
            if(ChInfo.bVisible) nFlag = MF_BYCOMMAND|MF_CHECKED;
            else nFlag = MF_BYCOMMAND|MF_UNCHECKED;
            pMenu->AppendMenu(nFlag, ID_MENUITEM_CH0+i+1, ChInfo.pszChName);
        }

        pMenu->TrackPopupMenu(TPM_LEFTALIGN, curPoint.x, curPoint.y, this);
        Popup.DestroyMenu();
    }

    return CBCGPDialog::PreTranslateMessage(pMsg);
}

void CMyDlgRTWave::OnCHSet(UINT nID)
{
    if(nID==ID_MENUITEM_CH0)
    {
        m_bRemoveDC = !m_bRemoveDC;
    }
    else
    {
        nID = nID - ID_MENUITEM_CH0 - 1;
        int nSize = m_pRTWave->GetChNum();
        ASSERT(nID<nSize);
        tRTWAVECHINFO ChInfo = m_pRTWave->GetChInfo(nID);
        m_pRTWave->SetChVisible(nID, !ChInfo.bVisible);
    }
}



