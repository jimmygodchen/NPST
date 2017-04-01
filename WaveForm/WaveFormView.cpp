// WaveFormView.cpp : implementation of the CWaveFormView class
//

#include "stdafx.h"
#include "WaveForm.h"

#include "WaveFormDoc.h"
#include "WaveFormView.h"
#include "CMyDebug.h"
#include "CMyDisPlayInfo.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWaveFormView

// const short BICNT = 8;
// const short AICNT = 3;

// static const CBCGPSize m_szMarker(3, 3);

#define BILINE      1                                            // 0:开关量为线型; 1: 开关量为粗细线条

IMPLEMENT_DYNCREATE(CWaveFormView, CFormView)

BEGIN_MESSAGE_MAP(CWaveFormView, CFormView)
	//{{AFX_MSG_MAP(CWaveFormView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	ON_WM_CONTEXTMENU()
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_MESSAGE(WM_INITDIALOG, HandleInitDialog)
	ON_REGISTERED_MESSAGE(BCGM_ON_CHART_MOUSE_DOWN, OnMouseDown)
	ON_REGISTERED_MESSAGE(BCGM_ON_CHART_MOUSE_UP, OnMouseUp)
	ON_REGISTERED_MESSAGE(BCGM_ON_CHART_MOUSE_TRACK, OnMouseTrack)
	ON_REGISTERED_MESSAGE(BCGM_ON_CHART_AFTER_DRAW, OnAfterDraw)
// 	ON_REGISTERED_MESSAGE(BCGM_ON_CHART_AFTER_RECALC_LAYOUT, OnAfterRecalcLayout)
	ON_COMMAND(IDC_BUTTON_ZOOM,OnZoom)
	ON_UPDATE_COMMAND_UI(IDC_BUTTON_ZOOM,OnUpdateZoom)
	ON_COMMAND(IDC_BUTTON_CURSOR,OnCursor)
	ON_UPDATE_COMMAND_UI(IDC_BUTTON_CURSOR,OnUpdateCursor)
// 	ON_COMMAND(IDC_BUTTON_TRIG,OnDrawTrig)
// 	ON_UPDATE_COMMAND_UI(IDC_BUTTON_TRIG,OnUpdateDrawTrig)
	ON_COMMAND(IDC_COMBO_ZOOMTYPE, OnZoomTypeSel)
// 	ON_CBN_SELENDOK(IDC_COMBO_ZOOMTYPE, OnZoomTypeSel)
//     ON_UPDATE_COMMAND_UI(IDC_COMBO_ZOOMTYPE,OnUpdateZoomType)
	ON_COMMAND(IDC_BUTTON_REST, OnRest)
// 	ON_COMMAND(IDC_BUTTON_DEBUG,OnDebug)
    ON_COMMAND(IDC_BUTTON_DISPLAYSET, OnDislaySet)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWaveFormView construction/destruction

CWaveFormView::CWaveFormView()
	: CFormView(CWaveFormView::IDD)
{
	//{{AFX_DATA_INIT(CWaveFormView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	EnableVisualManagerStyle();

	// TODO: add construction code here
	EnableLayout();
	SetWhiteBackground();
	m_bZoom = FALSE;
	m_strInfo = _T("");
	m_strTripInfo = _T("");
	m_strUnitX = _T("");
	m_bCursor = FALSE;
	m_nZoomType = 0;		// 水平放大
// 	m_bDrawTrig = FALSE;

// 	m_XLine1 = 0;
// 	m_XLine2 = 0;
	m_XLineCursor = 0;
// 	m_nCursorSel = -1;
// 	m_nDataIndex1 = 0;
// 	m_nDataIndex2 = 0;
// 	m_pText = NULL;
	m_fKTime = 1;

// 	for(int i=0;i<BICNT+AICNT;i++)
// 	{
// 		m_strCHName[i] = _T("");
// 	}

    m_pCoursorInfo = NULL;
    SetCursorInfoStyle();
    m_pSerBI = NULL;
    m_pAxisYSub = NULL;
    m_pSerAI = NULL;
// 
//     m_pMemDC = new CDC;
//     m_pBmp = new CBitmap;
//     m_bFlag = FALSE;
}

CWaveFormView::~CWaveFormView()
{
//     delete m_pMemDC; //删除内存设备环境
//     delete m_pBmp; //删除CBitmap的指针
    if(m_pSerBI) delete[] m_pSerBI;
    if(m_pAxisYSub) delete[] m_pAxisYSub;
    if(m_pSerAI) delete[] m_pSerAI;
}

void CWaveFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWaveFormView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_CHART, m_wndChart);
	DDX_Text(pDX, IDC_STATIC_INFO, m_strInfo);
	//}}AFX_DATA_MAP
}

BOOL CWaveFormView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CWaveFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	ResizeParentToFit();

	CBCGPRibbonBar* pRibbon = ((CMainFrame*) GetTopLevelFrame ())->GetRibbonBar ();
	ASSERT_VALID (pRibbon);

	CBCGPRibbonComboBox* pDataTypeCombo = DYNAMIC_DOWNCAST(CBCGPRibbonComboBox, pRibbon->FindByID (IDC_COMBO_ZOOMTYPE));
	if (pDataTypeCombo != NULL && !pDataTypeCombo->HasFocus ())
	{
		pDataTypeCombo->SelectItem(m_nZoomType);
	}

	GetParentFrame()->RecalcLayout();

	CBCGPChartVisualObject* pChart = m_wndChart.GetChart();
	ASSERT_VALID(pChart);
//     pChart->SetColors((CBCGPChartTheme::/*ChartTheme::*/CT_FLAT_2014_1));

// 	pChart->SetChartTitle(_T("Chart Title"));
// 	pChart->EnableMouseTrackingMode(
// 		BCGPChartHitInfo::HIT_DATA_POINT |
// 		BCGPChartHitInfo::HIT_DATA_LABEL |
// 		BCGPChartHitInfo::HIT_AXIS |
// 		BCGPChartHitInfo::HIT_AXIS_NAME |
// 		BCGPChartHitInfo::HIT_CHART_AREA |
// 		BCGPChartHitInfo::HIT_LEGEND |
// 		BCGPChartHitInfo::HIT_TITLE |
// 		BCGPChartHitInfo::HIT_DIAGRAM);
    // 	pChart->SetHitTestDataPointPrecision(m_szMarker);
    pChart->EnableMouseTrackingMode(
        BCGPChartHitInfo::HIT_DATA_POINT |
        BCGPChartHitInfo::HIT_DIAGRAM);

    CBCGPChartAxis* pXAxis = pChart->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
    ASSERT_VALID(pXAxis);
    pXAxis->m_axisNameFormat.m_textFormat = CBCGPTextFormat(
        _T("Arial"), 12., FW_REGULAR, CBCGPTextFormat::BCGP_FONT_STYLE_NORMAL);

//     CBCGPChartAxis* pYAxis = pChart->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS);
//     ASSERT_VALID(pYAxis);

//     m_pCoursorInfo = new CBCGPChartTextObject(pChart, "Cursor Info", 80, 35, m_brCoursorInfoText, m_brCoursorInfoFill, m_brCoursorInfoBorder);
//     m_pCoursorInfo->SetCoordinates(80, 35, 160, 65, CBCGPChartObject::CM_PIXELS_FIXED_SIZE);
// 
//     m_pCoursorInfo->m_format.m_textFormat = CBCGPTextFormat(
//         _T("Arial"), 12., FW_REGULAR, CBCGPTextFormat::BCGP_FONT_STYLE_ITALIC);
// 
//     m_pCoursorInfo->m_format.SetContentPadding(CBCGPSize(5., 5.));
//     m_pCoursorInfo->SetRoundedShape();
//     m_pCoursorInfo->SetShadow();
//     m_pCoursorInfo->SetVisible(FALSE);
// 
//     pChart->AddChartObject(m_pCoursorInfo);

    CWaveFormDoc* pDoc = GetDocument(); // non-debug version is inline
    ASSERT(pDoc);
    if(!pDoc->m_bFileOK) return;

    CString strFileName = pDoc->GetPathName();           // 获取文件全路径
    int nPos = strFileName.ReverseFind(_T('.'));
    m_strCfgFileName = strFileName.Left(nPos) + _T(".cfg");

    LoadCFGFile(m_strCfgFileName);

    m_strTripInfo.Format("起始时间:%d-%02d-%02d %02d:%02d:%02d.%03d",pDoc->m_Wave.m_wYear,pDoc->m_Wave.m_wMonth,pDoc->m_Wave.m_wDay,
        pDoc->m_Wave.m_wHour,pDoc->m_Wave.m_wMinute,pDoc->m_Wave.m_wSecond,pDoc->m_Wave.m_wMilliSecond);

    m_strInfo = /*_T("光标信息:  ") +*/ m_strTripInfo;
    UpdateData(FALSE);

    m_fKTime = 1.0f/pDoc->m_Wave.m_wFrequency;
    m_strUnitX = _T("s");

    AddAI();
    AddBI();

//  // Create line attributes:
//  m_brLine1.SetColor(CBCGPColor::Red);
//  m_brLine2.SetColor(CBCGPColor::Blue);
    m_brLineCursor.SetColor(CBCGPColor::DarkViolet);
//  m_brLineTrig.SetColor(CBCGPColor::Green);
    m_strokeStyle.SetDashStyle(CBCGPStrokeStyle::BCGP_DASH_STYLE_DASH);

    OnUpdateChart();
}

void CWaveFormView::AddBI(void)
{
    CBCGPChartVisualObject* pChart = m_wndChart.GetChart();
    ASSERT_VALID(pChart);
    CWaveFormDoc* pDoc = GetDocument(); // non-debug version is inline
    ASSERT(pDoc);
    int nBINO = pDoc->m_Wave.m_NumChannelDI;
    int nAINO = pDoc->m_Wave.m_NumChannelAD;
    
    CBCGPChartAxis* pYAxis = pChart->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS);
    ASSERT_VALID(pYAxis);
    m_pSerBI = new CBCGPChartSeries*[nBINO];
    m_pAxisYSub = new CBCGPChartAxis*[nBINO];
    ASSERT(m_pSerBI);
    ASSERT(m_pAxisYSub);
    for(int i=0;i<nBINO;++i)
    {
        if(!m_aDisplayInfo[i+nAINO].bVisible) continue;
#if BILINE==0
        // 开关量为线型
        m_pSerBI[i] = pChart->CreateSeries(pDoc->m_Wave.m_astrNameDI[i]);
        ASSERT_VALID(m_pSerBI[i]);
#else
        // 开关量为粗细线条
        m_pSerBI[i] = pChart->CreateSeries(pDoc->m_Wave.m_astrNameDI[i], CBCGPColor(), BCGP_CT_SIMPLE, BCGPChartArea);
        ASSERT_VALID(m_pSerBI[i]);
        m_pSerBI[i]->SetSeriesLineWidth(2);
//         BCGPChartFormatSeries style = pSerBI[i]->GetSeriesFormat();
//         style.SetSeriesLineWidth(2);
//         pSerBI[i]->SetSeriesFormat(style);
#endif
        m_pSerBI[i]->SetCurveType(BCGPChartFormatSeries::CCT_STEP);
        m_pSerBI[i]->SetColorIndex(i+nAINO);
        
        m_pAxisYSub[i] = (CBCGPChartAxisY*) pYAxis->Split(2+(float)i/10.0f,2);            // 分割(2+i/10)%,间隙2
        ASSERT(m_pAxisYSub[i]);
        m_pAxisYSub[i]->SetFixedDisplayRange(0, 1.0f);
        m_pAxisYSub[i]->m_strAxisName = pDoc->m_Wave.m_astrNameDI[i];
        //         pAxisYSub[i]->m_bDisplayAxisName = TRUE;
        //         pAxisYSub[i]->m_bVisible = FALSE;
        m_pSerBI[i]->SetRelatedAxis(m_pAxisYSub[i], CBCGPChartSeries::AI_Y);
        //      pSerBI[i]->m_bIncludeSeriesToLegend = FALSE;
        m_pAxisYSub[i]->EnableZoom(FALSE);                // Y轴不允许缩放
    }
    
    int nDotNum = pDoc->m_Wave.m_wDotPerChannel;
    
    for(i=0;i<nBINO;i++)
    {
        if(!m_aDisplayInfo[i+nAINO].bVisible) continue;
        BYTE* pBI = pDoc->m_Wave.m_pDataDI + i*nDotNum;
        for(int j=0;j<nDotNum;++j)
        {
            float fBI = pBI[j]?0.7f:0.1f;
            m_pSerBI[i]->AddDataPoint(fBI,(float)j*m_fKTime);
        }
    }
}


void CWaveFormView::AddAI(void)
{
    CBCGPChartVisualObject* pChart = m_wndChart.GetChart();
    ASSERT_VALID(pChart);
    CWaveFormDoc* pDoc = GetDocument(); // non-debug version is inline
    ASSERT(pDoc);
    int nAINO = pDoc->m_Wave.m_NumChannelAD;
    //     CBCGPChartSeries** pSerAI = new CBCGPChartSeries*[nAINO];
    m_pSerAI = new CBCGPChartSeries*[nAINO];
    ASSERT(m_pSerAI);
    for(int i=0;i<nAINO;++i)
    {
        m_pSerAI[i] = pChart->CreateSeries(pDoc->m_Wave.m_astrNameAD[i]);
        ASSERT_VALID(m_pSerAI[i]);
        m_pSerAI[i]->SetCurveType(BCGPChartFormatSeries::CCT_LINE);
    }
    int nDotNum = pDoc->m_Wave.m_wDotPerChannel;
    for(i=0;i<nAINO;i++)
    {
        float* pAI = pDoc->m_Wave.m_pDataAD + i*nDotNum;
        for(int j=0;j<nDotNum;++j)
        {
            float fAI = pAI[j];
            m_pSerAI[i]->AddDataPoint(fAI,(float)j*m_fKTime);
        }
    }
    for(i=0;i<nAINO;i++)
    {
        pChart->ShowSeries(m_aDisplayInfo[i].bVisible, i);
    }
}

void CWaveFormView::OnUpdateChart() 
{
    CBCGPChartVisualObject* pChart = m_wndChart.GetChart();
    ASSERT_VALID(pChart);
    pChart->ShowAxisIntervalInterlacing(BCGP_CHART_X_PRIMARY_AXIS);
    //  pChart->ShowAxisIntervalInterlacing(BCGP_CHART_Y_PRIMARY_AXIS);

    CString strName = _T("时间(") + m_strUnitX + _T(")");
    pChart->SetAxisName(BCGP_CHART_X_PRIMARY_AXIS, strName);
    pChart->ShowAxisName(BCGP_CHART_X_PRIMARY_AXIS, TRUE);

//    pChart->ShowAxisName(BCGP_CHART_Y_PRIMARY_AXIS, TRUE);

//     pChart->ShowAxis(BCGP_CHART_X_PRIMARY_AXIS, FALSE);

//  pChart->RemoveAllChartObjects();

    if(m_bZoom)
    {
        pChart->SetZoomScrollConfig(BCGPChartMouseConfig::ZSO_SELECT,
            (BCGPChartFormatSelection::SelectionType)m_nZoomType);
    }
    else
    {
        pChart->SetZoomScrollConfig(BCGPChartMouseConfig::ZSO_NONE);
//      pChart->SetAutoDisplayRange(TRUE, TRUE);
    }

    CBCGPChartAxis* pXAxis = pChart->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
    ASSERT_VALID(pXAxis);
    pXAxis->ShowScrollBar(m_bZoom);
    pXAxis->SetMaxZoomInFactor(20); // allow more details on X axis

    // X Axis should be always at the diagram bottom along with its labels
    pXAxis->m_crossType = CBCGPChartAxis::CT_FIXED_DEFAULT_POS;             // 坐标轴放到最下方
    pXAxis->m_axisLabelType = CBCGPChartAxis::ALT_LOW;                      // 坐标轴标签放到最下方
    pChart->EnableResizeAxes(TRUE);

    CBCGPChartAxis* pYAxis = pChart->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS);
    ASSERT_VALID(pYAxis);
    pYAxis->ShowScrollBar(m_bZoom);
    pYAxis->SetMaxZoomInFactor(10); // allow more details on X axis

    pChart->SetDirty(TRUE, TRUE);
//     pChart->Redraw();
}

void CWaveFormView::SetCursorInfoStyle(void)
{
// 	m_brCoursorInfoText = CBCGPBrush(CBCGPColor::SlateBlue/*SteelBlue*/);
// 	m_brCoursorInfoBorder = CBCGPBrush(CBCGPColor::SteelBlue, .4);
// 	m_brCoursorInfoFill = CBCGPBrush(CBCGPColor::LightSteelBlue, CBCGPColor::White, CBCGPBrush::BCGP_GRADIENT_RADIAL_TOP, .4);
// 	
// 	if(m_pCoursorInfo != NULL)
// 	{
// 		m_pCoursorInfo->m_format.m_brFillColor = m_brCoursorInfoFill;
// 		m_pCoursorInfo->m_format.m_brTextColor = m_brCoursorInfoText;
// 		m_pCoursorInfo->m_format.m_outlineFormat.m_brLineColor = m_brCoursorInfoBorder;
// 	}
}

LRESULT CWaveFormView::OnMouseDown(WPARAM /*wp*/, LPARAM lp)
{
    if(!m_bCursor)
    {
//      m_nCursorSel = -1;
        return 0;
    }

// 	CBCGPChartVisualObject* pChart = m_wndChart.GetChart();
// 	ASSERT_VALID(pChart);
// 	
// 	BCGPChartHitInfo* pHitInfo = (BCGPChartHitInfo*)lp;
// 	CBCGPPoint pt = pHitInfo->m_ptHit;
// 	
// 	CBCGPChartAxis* pXAxis = pChart->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
// 	ASSERT_VALID(pXAxis);
// 	
// 	// Get X Position on the chart
// 	double dblXMarker = pXAxis->ValueFromPoint(pt);
// 	
// 	// left marker index
// 	int nXValue = (int) floor(dblXMarker/m_fKTime);
// 	BOOL bRedraw = FALSE;
// 	
// 	CBCGPChartSeries* pSeries = pChart->GetSeries(0);
// 	ASSERT_VALID(pSeries);
// 	
// 	const CBCGPChartDataPoint* pDP = pSeries->GetDataPointAt(nXValue);
// 
// 	if(pDP)
// 	{
// 		CBCGPPoint pt = pSeries->GetDataPointScreenPoint(nXValue);
// 		if(fabs(m_XLine1-pt.x)<=fabs(m_XLine2-pt.x))
// 		{
// 			m_nCursorSel = 1;
// 		}
// 		else
// 		{
// 			m_nCursorSel = 2;
// 		}
// 		bRedraw = TRUE;
// 	}

    return 0;
}

LRESULT CWaveFormView::OnMouseUp(WPARAM /*wp*/, LPARAM lp)
{
//     m_nCursorSel = -1;
    return 0;
}

LRESULT CWaveFormView::OnMouseTrack(WPARAM /*wp*/, LPARAM lp)
{
//     m_pCoursorInfo->SetVisible(FALSE);
    if(!m_bCursor)
    {
        m_strInfo = /*_T("光标信息:  ") +*/ m_strTripInfo;
        UpdateData(FALSE);
        return 0;
    }

    CWaveFormDoc* pDoc = GetDocument(); // non-debug version is inline
    ASSERT(pDoc);

    CBCGPChartVisualObject* pChart = m_wndChart.GetChart();
    ASSERT_VALID(pChart);

    BCGPChartHitInfo* pHitInfo = (BCGPChartHitInfo*)lp;
    CBCGPPoint pt = pHitInfo->m_ptHit;

    CBCGPChartAxis* pXAxis = pChart->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
    ASSERT_VALID(pXAxis);

    // Get X Position on the chart
    double dblXMarker = pXAxis->ValueFromPoint(pt);

    // left marker index
    int nXValue = (int) floor(dblXMarker/m_fKTime);

    CBCGPChartSeries* pSeries = NULL;
//     int nSizeSeries = pChart->GetSeriesCount();
//     int nAI = pDoc->m_Wave.m_NumChannelAD;
//     int nSize = min(nAI, nSizeSeries);
    int nAI = pDoc->m_Wave.m_NumChannelAD;
    for(int i=0;i<nAI; ++i)
    {
        if(m_aDisplayInfo[i].bVisible)
        {
            pSeries = pChart->GetSeries(i);
            break;
        }
    }
    if(pSeries==NULL) return 0;
//     ASSERT_VALID(pSeries);

    const CBCGPChartDataPoint* pDP1 = pSeries->GetDataPointAt(nXValue);
    const CBCGPChartDataPoint* pDP2 = pSeries->GetDataPointAt(nXValue + 1);
    if(pDP1 != NULL && pDP2 != NULL/* && m_nCursorSel!=-1*/)
    {
//         m_pCoursorInfo->SetVisible(TRUE);
//         m_pCoursorInfo->SetCoordinates(pt.x+10, pt.y+10, 165, 80, CBCGPChartObject::CM_PIXELS_FIXED_SIZE);
        CBCGPPoint pt1 = pSeries->GetDataPointScreenPoint(nXValue);
        CBCGPPoint pt2 = pSeries->GetDataPointScreenPoint(nXValue+1);
        CBCGPPoint ptMarker;

        int nDataIndex;
        if(fabs(pt.x-pt1.x)<fabs(pt.x-pt2.x))
        {
            ptMarker = pt1;
            nDataIndex = nXValue;
        }
        else
        {
            ptMarker = pt2;
            nDataIndex = nXValue+1;
        }
        if(nDataIndex<0) nDataIndex = 0;
        if(nDataIndex>=pDoc->m_Wave.m_wDotPerChannel) nDataIndex = pDoc->m_Wave.m_wDotPerChannel-1;
        pt1 = pSeries->GetDataPointScreenPoint(nDataIndex);
        m_XLineCursor = pt1.x;
//         if(m_nCursorSel==1)
//         {
//             m_nDataIndex1 = nDataIndex;
//             m_XLine1 = pt1.x;
//         }
//         else if(m_nCursorSel==2)
//         {
//             m_nDataIndex2 = nDataIndex;
//             m_XLine2 = pt1.x;
//         }
    }

    ShowCursorInfo();

    pChart->SetDirty();
    pChart->Redraw();

    return 0;
}

LRESULT CWaveFormView::OnAfterDraw(WPARAM /*wp*/, LPARAM lp)
{
	CBCGPGraphicsManager* pGM = (CBCGPGraphicsManager*) lp;
	ASSERT_VALID(pGM);
	
	CBCGPChartVisualObject* pChart = m_wndChart.GetChart();
	ASSERT_VALID(pChart);
    CBCGPRect rectDiagram = pChart->GetDiagramArea();

    // Draw vertical line:
    if(m_bCursor)
    {
        if(m_XLineCursor>=rectDiagram.left && m_XLineCursor<=rectDiagram.right)
            pGM->DrawLine(m_XLineCursor, rectDiagram.top, m_XLineCursor, rectDiagram.bottom, m_brLineCursor, 1., &m_strokeStyle);
// 		if(m_XLine1>=rectDiagram.left && m_XLine1<=rectDiagram.right)
// 			pGM->DrawLine(m_XLine1, rectDiagram.top, m_XLine1, rectDiagram.bottom, m_brLine1, 1., &m_strokeStyle);
// 		if(m_XLine2>=rectDiagram.left && m_XLine2<=rectDiagram.right)
// 			pGM->DrawLine(m_XLine2, rectDiagram.top, m_XLine2, rectDiagram.bottom, m_brLine2, 1., &m_strokeStyle);
    }
// 	if(m_bDrawTrig)
// 	{
// 		CBCGPRect rectDiagram = pChart->GetDiagramArea();
// 
// 		CBCGPChartAxis* pXAxis = pChart->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
// 		ASSERT_VALID(pXAxis);
// 
// 		// Get X Position on the chart
// 
// 		CWaveFormDoc* pDoc = GetDocument(); // non-debug version is inline
// 		ASSERT(pDoc);
// 		long lDotTrig = pDoc->m_WaveForm.wTrig;
// 		long lDotTrail = pDoc->m_WaveForm.wDataTrail;
// 		lDotTrig = (lDotTrig + WFR_DOTNUM - lDotTrail - 1)%WFR_DOTNUM;
// 
// 		double dbLineTrig = pXAxis->PointFromValue(lDotTrig*m_fKTime,FALSE);
// 		
// 		pGM->DrawLine(dbLineTrig, rectDiagram.top, dbLineTrig, rectDiagram.bottom, m_brLineTrig, 1., &m_strokeStyle);
// 	}
	return 0;
}

// LRESULT CWaveFormView::OnAfterRecalcLayout(WPARAM, LPARAM)
// {
// // 	m_XLine1 = 0;
// // 	m_XLine2 = 0;
// // 	m_nCursorSel = -1;
// // 	m_nDataIndex1 = 0;
// // 	m_nDataIndex2 = 0;
// 
// 	return 0;
// }

void CWaveFormView::ShowCursorInfo(void)
{
    if(!m_bCursor)
    {
        return;
    }

    CBCGPChartVisualObject* pChart = m_wndChart.GetChart();
    ASSERT_VALID(pChart);

    CBCGPChartAxis* pXAxis = pChart->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
    ASSERT_VALID(pXAxis);

    CWaveFormDoc* pDoc = GetDocument(); // non-debug version is inline
    ASSERT(pDoc);
// 	int nTrail = pDoc->m_WaveForm.wDataTrail;
// 	CBCGPPoint pt1 = CBCGPPoint(m_XLine1,0,0);
// 	CBCGPPoint pt2 = CBCGPPoint(m_XLine2,0,0);
    CBCGPPoint ptCursor = CBCGPPoint(m_XLineCursor,0,0);
// 
// 	double dblX1 = pXAxis->ValueFromPoint(pt1);
// 	double dblX2 = pXAxis->ValueFromPoint(pt2);
    double dblXCursor = pXAxis->ValueFromPoint(ptCursor);
// 
// 	int nXValue1 = (int) floor(dblX1/m_fKTime+0.5);
// 	int nXValue2 = (int) floor(dblX2/m_fKTime+0.5);
    int nXValueCursor = (int) floor(dblXCursor/m_fKTime+0.5);
// 
// 	float fT1 = (float)fabs(nXValue1)*m_fKTime;
// 	float fT2 = (float)fabs(nXValue2)*m_fKTime;
    float fTCursor = (float)fabs(nXValueCursor)*m_fKTime;
// 	float fDifT = (float)fabs(nXValue1-nXValue2)*m_fKTime;

// 	ASSERT_VALID(m_pCoursorInfo);

//     m_pCoursorInfo->m_strText.Format("T: %fS",fTCursor);

// 	m_strInfo = _T("光标信息:\r\n") + m_strTripInfo + strCursorInfo;

    CString strCursorInfo = _T("\r\n");

    CTime time = CTime(pDoc->m_Wave.m_wYear, pDoc->m_Wave.m_wMonth, pDoc->m_Wave.m_wDay, pDoc->m_Wave.m_wHour,pDoc->m_Wave.m_wMinute,
        pDoc->m_Wave.m_wSecond);
    float fMs = fTCursor + pDoc->m_Wave.m_wMilliSecond*0.001f;
    int nS = floor(fMs);
    time += nS;
    int nMs = (fMs - nS) * 1000;
    CString str;
    str.Format(_T("光标时间:%d-%02d-%02d %02d:%02d:%02d.%03d"), time.GetYear(), time.GetMonth(), time.GetDay(),
        time.GetHour(), time.GetMinute(), time.GetSecond(), nMs);
    strCursorInfo += str;

    strCursorInfo += _T("\r\n");
    int nAINO = pDoc->m_Wave.m_NumChannelAD;
    int nAIDot = pDoc->m_Wave.m_wDotPerChannel;
//     float* pData = new float[nAINO];
    for(int i=0;i<nAINO;++i)
    {
        if(!m_aDisplayInfo[i].bVisible) continue;
        float* pDataAI = pDoc->m_Wave.m_pDataAD + i*nAIDot;
        float fData = pDataAI[nXValueCursor];
        str.Format(_T("%s: %7.2f %s      "), pDoc->m_Wave.m_astrNameAD[i], fData, pDoc->m_Wave.m_astrUnitageAD[i]);
        strCursorInfo += str;
    }

    m_strInfo = m_strTripInfo + strCursorInfo;

    UpdateData(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CWaveFormView printing

void CWaveFormView::OnFilePrintPreview() 
{
	BCGPPrintPreview (this);
}

void CWaveFormView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
    // TODO: Add your specialized code here and/or call the base class
    m_wndChart.DoPrint(pDC,pInfo);
//     pDC->TextOut(0,2500,"jimmy");
//     OnDraw(pDC);
    //     CFormView::OnPrint(pDC, pInfo);
}

BOOL CWaveFormView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CWaveFormView::OnBeginPrinting(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CWaveFormView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CWaveFormView diagnostics

#ifdef _DEBUG
void CWaveFormView::AssertValid() const
{
	CFormView::AssertValid();
}

void CWaveFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CWaveFormDoc* CWaveFormView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWaveFormDoc)));
	return (CWaveFormDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWaveFormView message handlers

void CWaveFormView::OnContextMenu(CWnd*, CPoint point)
{
// 	theApp.ShowPopupMenu (IDR_CONTEXT_MENU, point, this);
}

void CWaveFormView::OnZoom()
{
	m_bZoom = !m_bZoom;
	OnUpdateChart();
	m_wndChart.SetFocus();
}

void CWaveFormView::OnRest()
{
	CBCGPChartVisualObject* pChart = m_wndChart.GetChart();
	ASSERT_VALID(pChart);
	pChart->SetAutoDisplayRange(TRUE, TRUE);
	m_wndChart.SetFocus();
}

void CWaveFormView::OnUpdateZoom(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bZoom);
}

void CWaveFormView::OnDebug()
{
	CMyDebug* pDlg = new CMyDebug;
	if(pDlg)
	{
		CWaveFormDoc* pDoc = GetDocument(); // non-debug version is inline
		ASSERT(pDoc);
		pDlg->m_pDoc = pDoc;
		pDlg->DoModal();
		delete pDlg;
	}
}

void CWaveFormView::OnCursor()
{
    m_bCursor = !m_bCursor;
    CBCGPChartVisualObject* pChart = m_wndChart.GetChart();
    ASSERT_VALID(pChart);
    pChart->Redraw();
//     OnUpdateChart();
    m_wndChart.SetFocus();
}

void CWaveFormView::OnDislaySet()
{
    CBCGPChartVisualObject* pChart = m_wndChart.GetChart();
    ASSERT_VALID(pChart);
    CWaveFormDoc* pDoc = GetDocument();
    ASSERT(pDoc);
    int nBINO = pDoc->m_Wave.m_NumChannelDI;
    int nAINO = pDoc->m_Wave.m_NumChannelAD;

    CArray<BOOL,BOOL&> aVisible;
    aVisible.SetSize(nBINO);
    for(int i=0;i<nBINO;++i)
    {
        aVisible[i] = m_aDisplayInfo[i+nAINO].bVisible;
    }

    CMyDisPlayInfo dlg;
    dlg.m_pDoc = pDoc;
    dlg.m_aCHDisplalyInfo.SetSize(nAINO+nBINO);
    for(i=0;i<nAINO+nBINO;++i)
    {
        dlg.m_aCHDisplalyInfo[i].bVisible = m_aDisplayInfo[i].bVisible;
    }
    if(dlg.DoModal()==IDOK)
    {
        for(i=0;i<nAINO+nBINO;++i)
        {
            m_aDisplayInfo[i].bVisible = dlg.m_aCHDisplalyInfo[i].bVisible;
        }
        StoreCFGFile(m_strCfgFileName);

        for(i=0;i<nBINO;++i)
        {
            if(!aVisible[i]) continue;
            pChart->RemoveCustomAxis(m_pAxisYSub[i], TRUE);
        }

        if(m_pAxisYSub) delete[] m_pAxisYSub;
        if(m_pSerBI) delete[] m_pSerBI;
        m_pAxisYSub = NULL;
        m_pSerBI = NULL;

        AddBI();

        for(i=0;i<nAINO;++i)
        {
            pChart->ShowSeries(m_aDisplayInfo[i].bVisible, i);
        }

        OnUpdateChart();
        m_wndChart.SetFocus();
    }
}

void CWaveFormView::OnUpdateCursor(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bCursor);
}

void CWaveFormView::OnDrawTrig()
{
// 	m_bDrawTrig = !m_bDrawTrig;
// 	CBCGPChartVisualObject* pChart = m_wndChart.GetChart();
// 	ASSERT_VALID(pChart);
// 	pChart->Redraw();
// 	m_wndChart.SetFocus();
}

void CWaveFormView::OnUpdateDrawTrig(CCmdUI* pCmdUI)
{
// 	pCmdUI->SetCheck(m_bDrawTrig);
}

void CWaveFormView::OnZoomTypeSel() 
{
	int nSize = -1;
	
	CBCGPRibbonBar* pRibbon = ((CMainFrame*) GetTopLevelFrame ())->GetRibbonBar ();
	ASSERT_VALID (pRibbon);
	
	CBCGPRibbonComboBox* pZoomTypeCombo = DYNAMIC_DOWNCAST(CBCGPRibbonComboBox, pRibbon->FindByID (IDC_COMBO_ZOOMTYPE));
	if(pZoomTypeCombo != NULL)
	{
		nSize = (pZoomTypeCombo->GetCurSel());
		m_nZoomType = nSize;
	}

	OnUpdateChart();
	m_wndChart.SetFocus();
}

// void CWaveFormView::OnUpdateZoomType(CCmdUI* pCmdUI)
// {
// //     pCmdUI->SetCheck(m_bDrawTrig);
//     CBCGPRibbonBar* pRibbon = ((CMainFrame*) GetTopLevelFrame ())->GetRibbonBar ();
//     ASSERT_VALID (pRibbon);
//     
//     CBCGPRibbonComboBox* pDataTypeCombo = DYNAMIC_DOWNCAST(CBCGPRibbonComboBox, pRibbon->FindByID (IDC_COMBO_ZOOMTYPE));
//     if (pDataTypeCombo != NULL && !pDataTypeCombo->HasFocus ())
//     {
//         pDataTypeCombo->SelectItem(m_nZoomType);
// 	}
// }

LRESULT CWaveFormView::HandleInitDialog(WPARAM wParam, LPARAM lParam)
{
    LRESULT lRes = CBCGPFormView::HandleInitDialog (wParam, lParam);

    if (GetLayout() != NULL)
    {
        UpdateData(FALSE);
// 		SetupLayout();
        CBCGPStaticLayout* pLayout = (CBCGPStaticLayout*)GetLayout();
        if (pLayout != NULL/* && GetCtrl() != NULL*/)
        {
            pLayout->AddAnchor(IDC_STATIC_FRAME, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeHorz);
            pLayout->AddAnchor(IDC_STATIC_INFO, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeHorz);
            pLayout->AddAnchor(m_wndChart.GetDlgCtrlID(), CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeBoth);
        }
    }

    return lRes;
}


// void CWaveFormView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
// {
// 	// TODO: Add your specialized code here and/or call the base class
// 	
// 	CFormView::OnPrepareDC(pDC, pInfo);
//     pDC->SetMapMode(MM_ANISOTROPIC); //转换坐标映射方式
//     CSize size = CSize(800, 560);
//     pDC->SetWindowExt(size); //确定窗口大小
//     //得到实际设备每逻辑英寸的象素数量
//     int xLogPixPerInch = pDC->GetDeviceCaps(LOGPIXELSX);
//     int yLogPixPerInch = pDC->GetDeviceCaps(LOGPIXELSY);
//     //得到设备坐标和逻辑坐标的比例
//     long xExt = (long)size.cx * xLogPixPerInch/96 ;
//     long yExt = (long)size.cy * yLogPixPerInch/96 ;
//     pDC->SetViewportExt((int)xExt, (int)yExt); //确定视口大小
// }

void CWaveFormView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class
    CBCGPRibbonBar* pRibbon = ((CMainFrame*) GetTopLevelFrame ())->GetRibbonBar ();
    ASSERT_VALID (pRibbon);
    
    CBCGPRibbonComboBox* pDataTypeCombo = DYNAMIC_DOWNCAST(CBCGPRibbonComboBox, pRibbon->FindByID (IDC_COMBO_ZOOMTYPE));
    if (pDataTypeCombo != NULL && !pDataTypeCombo->HasFocus ())
    {
        pDataTypeCombo->SelectItem(m_nZoomType);
	}
	CFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CWaveFormView::LoadCFGFile(CString strFileName)
{
    CWaveFormDoc* pDoc = GetDocument(); // non-debug version is inline
    ASSERT(pDoc);
    BOOL bErr = FALSE;
    if(strFileName.IsEmpty()) bErr = TRUE;
    CFile file;
    if(file.Open(strFileName,CFile::modeRead))
    {
        CArchive ar(&file,CArchive::load);
        if(!SerializeCFG(ar)) bErr = TRUE;
        ar.Close();
        file.Close();
    }
    else bErr = TRUE;

    if(bErr)
    {
        int nAINO = pDoc->m_Wave.m_NumChannelAD;
        int nBINO = pDoc->m_Wave.m_NumChannelDI;
        m_aDisplayInfo.RemoveAll();
        m_aDisplayInfo.SetSize(nAINO+nBINO);
        for(int i=0;i<nAINO+nBINO;++i)
        {
            m_aDisplayInfo[i].bVisible = TRUE;
        }
    }
}

void CWaveFormView::StoreCFGFile(CString strFileName)
{
    if(strFileName.IsEmpty()) return;
    CFile file;
    if(file.Open(strFileName,CFile::modeWrite|CFile::modeCreate))
    {
        CArchive ar(&file,CArchive::store);
        SerializeCFG(ar);
        ar.Close();
        file.Close();
    }
}

BOOL CWaveFormView::SerializeCFG(CArchive& ar)
{
    CWaveFormDoc* pDoc = GetDocument(); // non-debug version is inline
    ASSERT(pDoc);

    CString strTitle = pDoc->GetTitle();
    int nAINO = pDoc->m_Wave.m_NumChannelAD;
    int nBINO = pDoc->m_Wave.m_NumChannelDI;
    int i;

    if (ar.IsStoring())
    {
        ar << strTitle;
        ar << nAINO;
        ar << nBINO;
        for(i=0;i<nAINO;i++)
        {
            ar << m_aDisplayInfo[i].bVisible;
//             ar << m_aDisplayInfo[i].nColorIndex;
        }
        for(i=0;i<nBINO;i++)
        {
            ar << m_aDisplayInfo[i+nAINO].bVisible;
//             ar << m_aDisplayInfo[i+nAINO].nColorIndex;
        }
    }
    else
    {
        CString str;
        int nAINOR;
        int nBINOR;

        ar >> str;
        if(str!=strTitle) return FALSE;

        ar >> nAINOR;
        if(nAINOR!=nAINO) return FALSE;

        ar >> nBINOR;
        if(nBINOR!=nBINO) return FALSE;

        m_aDisplayInfo.RemoveAll();
        m_aDisplayInfo.SetSize(nAINO+nBINO);

        for(i=0;i<nAINO;i++)
        {
            ar >> m_aDisplayInfo[i].bVisible;
//             ar >> m_aDisplayInfo[i].nColorIndex;
        }
        for(i=0;i<nBINO;i++)
        {
            ar >> m_aDisplayInfo[i+nAINO].bVisible;
//             ar >> m_aDisplayInfo[i].nColorIndex;
        }
    }
    return TRUE;
}


