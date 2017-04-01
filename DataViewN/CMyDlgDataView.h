#if !defined(AFX_CMYDLGDATAVIEW_H__47135C9D_C514_4074_AB38_CEDFE3A7C5EB__INCLUDED_)
#define AFX_CMYDLGDATAVIEW_H__47135C9D_C514_4074_AB38_CEDFE3A7C5EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CMyDlgDataView.h : header file
//

#include "resource.h"


/////////////////////////////////////////////////////////////////////////////
// CMyDataGridCtrl sample class

class CMyDataGridCtrl: public CBCGPGridCtrl
{
public:
    CMyDataGridCtrl();
    ~CMyDataGridCtrl();

public:
    CBCGPGridRow* CreateNewRow(void);

public:
    void InitUpdateID(void);
    void AddRowFloat(CBCGPGridRow* pRoot);
    void AddRowBI(CBCGPGridRow* pRoot);
    void AddRowString(CBCGPGridRow* pRoot);
    void AddRowOperate(CBCGPGridRow* pRoot);

protected:
    CPtrArray m_aOperate;
    CArray<DWORD, DWORD&> m_aUpdateID;
//    CMyDataOperate* GetOperate(int nIndex);

    // Generated message map functions
protected:
    //{{AFX_MSG(CCellTypesGridCtrl)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnDestroy();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    //}}AFX_MSG
    afx_msg void OnOperate(UINT nID);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CMyDlgDataView dialog

class CMyDlgDataView : public CBCGPDialog// CDialog
{
// Construction
public:
	CMyDlgDataView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMyDlgDataView)
	enum { IDD = IDD_DLG_DATAVIEW };
	CStatic	m_wndLocationFloat;
	//}}AFX_DATA

public:
    CMyDataGridCtrl m_wndGridFloat;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDlgDataView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMyDlgDataView)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMYDLGDATAVIEW_H__47135C9D_C514_4074_AB38_CEDFE3A7C5EB__INCLUDED_)
