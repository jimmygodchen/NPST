#if !defined(AFX_CMYDLGRTWAVE_H__507756DA_D800_4506_B249_5004F11D1DF7__INCLUDED_)
#define AFX_CMYDLGRTWAVE_H__507756DA_D800_4506_B249_5004F11D1DF7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CMyDlgRTWave.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyDlgRTWave dialog

class CMyDlgRTWave : public CBCGPDialog
{
// Construction
public:
	CMyDlgRTWave(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMyDlgRTWave)
	enum { IDD = IDD_DLG_RTWAVE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
    CBCGPChartCtrl	m_wndChart;

public:
    CMyRTWave* m_pRTWave;
    CBCGPChartSeries** m_pSerAI;
    DWORD m_dwUpdateID;
    BOOL m_bRemoveDC;

public:
    void AddWave(void);
    void ShowWave(void);
    void Refresh(void);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDlgRTWave)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMyDlgRTWave)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
    afx_msg void OnCHSet(UINT nID);
//     afx_msg void OnUpdateCH(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMYDLGRTWAVE_H__507756DA_D800_4506_B249_5004F11D1DF7__INCLUDED_)
