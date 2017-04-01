#if !defined(AFX_CMYDEBUG_H__FEA1F76B_324D_4DB7_9B39_DEA2413261B2__INCLUDED_)
#define AFX_CMYDEBUG_H__FEA1F76B_324D_4DB7_9B39_DEA2413261B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CMyDebug.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyDebug dialog

class CMyDebug : public CBCGPDialog //CDialog
{
// Construction
public:
	CMyDebug(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMyDebug)
	enum { IDD = IDD_DLG_DEBUG };
	CBCGPListCtrl	m_listSet;
	//}}AFX_DATA

public:
	CWaveFormDoc* m_pDoc;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDebug)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMyDebug)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMYDEBUG_H__FEA1F76B_324D_4DB7_9B39_DEA2413261B2__INCLUDED_)
