#if !defined(AFX_CMYPORTSCIDLG_H__FBDAA5ED_0E9F_4AD1_835E_8EF3900F2F5E__INCLUDED_)
#define AFX_CMYPORTSCIDLG_H__FBDAA5ED_0E9F_4AD1_835E_8EF3900F2F5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CMyPortSCIDlg.h : header file
//

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CMyPortSCIDlg dialog

class CMyPortSCIDlg : public CBCGPPropertyPage
{
	DECLARE_DYNCREATE(CMyPortSCIDlg)

// Construction
public:
	CMyPortSCIDlg();
	~CMyPortSCIDlg();

// Dialog Data
	//{{AFX_DATA(CMyPortSCIDlg)
	enum { IDD = IDD_PORT_SCI };
	CComboBox	m_wndBaud;
	CComboBox	m_wndPort;
	int		m_nBaud;
	int		m_nCom;
	//}}AFX_DATA

public:
    CMyEnumSCI* m_pEnumSCI;


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMyPortSCIDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMyPortSCIDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMYPORTSCIDLG_H__FBDAA5ED_0E9F_4AD1_835E_8EF3900F2F5E__INCLUDED_)
