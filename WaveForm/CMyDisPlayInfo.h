#if !defined(AFX_CMYDISPLAYINFO_H__B58B996F_D095_43D4_9142_C70EFE1C7621__INCLUDED_)
#define AFX_CMYDISPLAYINFO_H__B58B996F_D095_43D4_9142_C70EFE1C7621__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CMyDisPlayInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyDisPlayInfo dialog

class CMyDisPlayInfo : public CBCGPDialog// CDialog
{
// Construction
public:
	CMyDisPlayInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMyDisPlayInfo)
	enum { IDD = IDD_DLG_DISPLAYINFO };
    CBCGPListCtrl	m_listSet;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

public:
    CWaveFormDoc* m_pDoc;
    CMyCHDisplayInfoArray m_aCHDisplalyInfo;
//     CToolTipCtrl* m_pToolTip;
    CBCGPToolTipCtrl m_ToolTip;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDisPlayInfo)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMyDisPlayInfo)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkListSet(NMHDR* pNMHDR, LRESULT* pResult);
// 	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
// 	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMYDISPLAYINFO_H__B58B996F_D095_43D4_9142_C70EFE1C7621__INCLUDED_)
