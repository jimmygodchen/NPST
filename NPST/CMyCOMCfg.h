#if !defined(AFX_CMYCOMCFG_H__CB7D5FE2_091C_4948_AB39_FE86A34E8AE9__INCLUDED_)
#define AFX_CMYCOMCFG_H__CB7D5FE2_091C_4948_AB39_FE86A34E8AE9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CMyCOMCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyCOMCfg dialog

#include "CMyEnumSCI.h"

class CMyCOMCfg : public CDialog
{
// Construction
public:
	CMyCOMCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMyCOMCfg)
	enum { IDD = IDD_DLG_COMCFG };
	CIPAddressCtrl	m_ctrTCPIPClient;
	CIPAddressCtrl	m_ctrTCPIPServer;
	CIPAddressCtrl	m_ctrUDPIPSrc;
	CIPAddressCtrl	m_ctrUDPIPDest;
	int		m_nComBaud;
	int		m_nComPort;
	int		m_nUDPPortDest;
	int		m_nUDPPortSrc;
	int		m_nTCPPortServer;
	int		m_nDeviceAddr;
	int		m_nCycleTime;
	int		m_nComMode;
	int		m_nTCPPortClient;
	int		m_nTimeout;
	//}}AFX_DATA

public:
	PortInfo m_PortInfo;

    CMyEnumSCI m_EnumSCI;

public:
	void ComOption2Ctr(void);
	void Ctr2ComOption(void);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyCOMCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMyCOMCfg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMYCOMCFG_H__CB7D5FE2_091C_4948_AB39_FE86A34E8AE9__INCLUDED_)
