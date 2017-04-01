// IEC103AnalysisDoc.h : interface of the CIEC103AnalysisDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IEC103ANALYSISDOC_H__558EBA6E_BEB7_441A_8E48_6092B04DAB40__INCLUDED_)
#define AFX_IEC103ANALYSISDOC_H__558EBA6E_BEB7_441A_8E48_6092B04DAB40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CIEC103AnalysisDoc : public CRichEditDoc
{
protected: // create from serialization only
	CIEC103AnalysisDoc();
	DECLARE_DYNCREATE(CIEC103AnalysisDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIEC103AnalysisDoc)
	public:
	virtual BOOL OnNewDocument();
// 	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL
	virtual CRichEditCntrItem* CreateClientItem(REOBJECT* preo) const;

// Implementation
public:
	virtual ~CIEC103AnalysisDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CIEC103AnalysisDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IEC103ANALYSISDOC_H__558EBA6E_BEB7_441A_8E48_6092B04DAB40__INCLUDED_)
