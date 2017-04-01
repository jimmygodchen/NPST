// IEC103AnalysisView.h : interface of the CIEC103AnalysisView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IEC103ANALYSISVIEW_H__3B629577_88A2_42C0_AAA5_8C6BCB78EEFA__INCLUDED_)
#define AFX_IEC103ANALYSISVIEW_H__3B629577_88A2_42C0_AAA5_8C6BCB78EEFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// #include "SerialPort.h"

//-----------------------------------------------------------------------------------------------------
class CIEC103AnalysisCntrItem;

class CIEC103AnalysisView : public CRichEditView
{
protected: // create from serialization only
    CIEC103AnalysisView();
    DECLARE_DYNCREATE(CIEC103AnalysisView)

// Attributes
public:
    CIEC103AnalysisDoc* GetDocument();

public:
    void ShowCommData(CString str, COLORREF cr);

// Operations
public:
	BOOL ShowContextMenu (CPoint pt);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIEC103AnalysisView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CIEC103AnalysisView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CIEC103AnalysisView)
	afx_msg void OnDestroy();
// 	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
    afx_msg void OnContextMenu(CWnd*, CPoint point);
    afx_msg void OnFilePrintPreview();
    afx_msg void OnCopyright(){};
    afx_msg void OnClearCnt();
    afx_msg void OnClearTXT();
    afx_msg void OnCOMCfg();
    afx_msg void OnUpdateCOMCfg(CCmdUI* pCmdUI);
    afx_msg void OnUnitCfg();
    afx_msg void OnUpdateUnitCfg(CCmdUI* pCmdUI);
    afx_msg void OnCOMOperate(UINT nID);
    afx_msg void OnUpdateCOMOperate(CCmdUI* pCmdUI);
    afx_msg LONG OnPortMsg(WPARAM wParm, LPARAM lParam);

    afx_msg void OnViewUnitData();
    afx_msg void OnUpdateViewUnitData(CCmdUI* pCmdUI);

    afx_msg void OnComSel(){};

	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in IEC103AnalysisView.cpp
inline CIEC103AnalysisDoc* CIEC103AnalysisView::GetDocument()
   { return (CIEC103AnalysisDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IEC103ANALYSISVIEW_H__3B629577_88A2_42C0_AAA5_8C6BCB78EEFA__INCLUDED_)
