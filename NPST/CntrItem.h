// CntrItem.h : interface of the CIEC103AnalysisCntrItem class
//

#if !defined(AFX_CNTRITEM_H__3145A0BF_CD4D_4517_A709_305109CEBBE0__INCLUDED_)
#define AFX_CNTRITEM_H__3145A0BF_CD4D_4517_A709_305109CEBBE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CIEC103AnalysisDoc;
class CIEC103AnalysisView;

class CIEC103AnalysisCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CIEC103AnalysisCntrItem)

// Constructors
public:
	CIEC103AnalysisCntrItem(REOBJECT* preo = NULL, CIEC103AnalysisDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CIEC103AnalysisDoc* GetDocument()
		{ return (CIEC103AnalysisDoc*)CRichEditCntrItem::GetDocument(); }
	CIEC103AnalysisView* GetActiveView()
		{ return (CIEC103AnalysisView*)CRichEditCntrItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIEC103AnalysisCntrItem)
	public:
	protected:
	//}}AFX_VIRTUAL

	virtual BOOL OnShowControlBars(CFrameWnd* pFrameWnd, BOOL bShow);

// Implementation
public:
	~CIEC103AnalysisCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__3145A0BF_CD4D_4517_A709_305109CEBBE0__INCLUDED_)
