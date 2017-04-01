// WaveFormView.h : interface of the CWaveFormView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WAVEFORMVIEW_H__06135C54_7FB8_46FF_9F8E_AD253ED4E977__INCLUDED_)
#define AFX_WAVEFORMVIEW_H__06135C54_7FB8_46FF_9F8E_AD253ED4E977__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct
{
     int nColorIndex;
     BOOL bVisible;
}tCHDISPALYINFO;                    // 通道显示信息

typedef CArray<tCHDISPALYINFO, tCHDISPALYINFO&> CMyCHDisplayInfoArray;

#define CFormView CBCGPFormView

class CWaveFormView : public CFormView
{
protected: // create from serialization only
	CWaveFormView();
	DECLARE_DYNCREATE(CWaveFormView)

public:
	//{{AFX_DATA(CWaveFormView)
	enum{ IDD = IDD_WAVEFORM_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	CBCGPChartCtrl	m_wndChart;
	CString	m_strInfo;
	CString m_strTripInfo;
	CString m_strUnitX;				// X轴单位(时间)
	float m_fKTime;					// 时间系数
	BOOL m_bZoom;
	BOOL m_bCursor;
// 	BOOL m_bDrawTrig;

	int m_nZoomType;

// 	float m_fData[300];
// 	float m_fDataMax;
// 	int m_nDataIndex1;
// 	int m_nDataIndex2;

//     CTime m_timeS;					// 起始时间
//     int m_nMsS;						// 起始时间ms部分

    CBCGPChartSeries** m_pSerAI;
    CBCGPChartSeries** m_pSerBI;
    CBCGPChartAxis** m_pAxisYSub;

    CMyCHDisplayInfoArray m_aDisplayInfo;
    CString m_strCfgFileName;

public:
    void ShowCursorInfo(void);
    void SetCursorInfoStyle(void);
    void LoadCFGFile(CString strFileName);
    void StoreCFGFile(CString strFileName);
    BOOL SerializeCFG(CArchive& ar);

public:
    void AddBI(void);
    void AddAI(void);

// Attributes
public:
	CWaveFormDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWaveFormView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWaveFormView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
// 	CBCGPPointsArray	m_arMarkers;
// 	double				m_XLine;
// 	CBCGPBrush			m_brLine;
// 	double				m_XLine1;
// 	double				m_XLine2;
	double				m_XLineCursor;
// 	CBCGPBrush			m_brLine1;
// 	CBCGPBrush			m_brLine2;
	CBCGPBrush			m_brLineCursor;
// 	int					m_nCursorSel;
	CBCGPStrokeStyle	m_strokeStyle;

// 	CBCGPBrush			m_brLineTrig;
// 	CBCGPStrokeStyle	m_strokeStyle;
// 	CString				m_strCHName[11];			// 图表上显示通道名称

	CBCGPChartTextObject*	m_pCoursorInfo;
	CBCGPBrush				m_brCoursorInfoText;
	CBCGPBrush				m_brCoursorInfoFill;
	CBCGPBrush				m_brCoursorInfoBorder;

// Generated message map functions
protected:
	//{{AFX_MSG(CWaveFormView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	afx_msg void OnUpdateChart();
	//}}AFX_MSG
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	afx_msg void OnFilePrintPreview();
	afx_msg LRESULT HandleInitDialog(WPARAM, LPARAM);
	afx_msg LRESULT OnMouseDown(WPARAM wp, LPARAM lp);
	afx_msg LRESULT OnMouseUp(WPARAM wp, LPARAM lp);
	afx_msg LRESULT OnMouseTrack(WPARAM wp, LPARAM lp);
	afx_msg LRESULT OnAfterDraw(WPARAM wp, LPARAM lp);
// 	afx_msg LRESULT OnAfterRecalcLayout(WPARAM wp, LPARAM lp);
	afx_msg void OnZoom();
	afx_msg void OnUpdateZoom(CCmdUI* pCmdUI);
	afx_msg void OnCursor();
	afx_msg void OnUpdateCursor(CCmdUI* pCmdUI);
	afx_msg void OnDrawTrig();
	afx_msg void OnUpdateDrawTrig(CCmdUI* pCmdUI);
	afx_msg void OnZoomTypeSel();
//     afx_msg void OnUpdateZoomType(CCmdUI* pCmdUI);
	afx_msg void OnRest();
	afx_msg void OnDebug();
    afx_msg void OnDislaySet();
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in WaveFormView.cpp
inline CWaveFormDoc* CWaveFormView::GetDocument()
   { return (CWaveFormDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAVEFORMVIEW_H__06135C54_7FB8_46FF_9F8E_AD253ED4E977__INCLUDED_)
