#if !defined(AFX_CMYUDPDLG_H__95BA49C8_1059_4121_A734_98321466CBA2__INCLUDED_)
#define AFX_CMYUDPDLG_H__95BA49C8_1059_4121_A734_98321466CBA2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CMyUDPDlg.h : header file
//
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CMyUDPDlg dialog

class CMyUDPDlg : public CBCGPPropertyPage
{
	DECLARE_DYNCREATE(CMyUDPDlg)

// Construction
public:
	CMyUDPDlg();
	~CMyUDPDlg();

// Dialog Data
	//{{AFX_DATA(CMyUDPDlg)
	enum { IDD = IDD_PORT_UDP };
	CIPAddressCtrl	m_wndIPSrc;
	CIPAddressCtrl	m_wndIPDest;
	int		m_nPortDest;
	int		m_nPortSrc;
    DWORD m_dwIPDest;
    DWORD m_dwIPSrc;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMyUDPDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMyUDPDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMYUDPDLG_H__95BA49C8_1059_4121_A734_98321466CBA2__INCLUDED_)
