// IEC103Analysis.h : main header file for the IEC103ANALYSIS application
//

#if !defined(AFX_IEC103ANALYSIS_H__F02D8995_3E57_41E6_BDFE_FA6261E53B86__INCLUDED_)
#define AFX_IEC103ANALYSIS_H__F02D8995_3E57_41E6_BDFE_FA6261E53B86__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CIEC103AnalysisApp:
// See IEC103Analysis.cpp for the implementation of this class
//

class CIEC103AnalysisApp : public CWinApp,
					  public CBCGPWorkspace
{
public:
	CIEC103AnalysisApp();

	// Override from CBCGPWorkspace
	virtual void PreLoadState ();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIEC103AnalysisApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CIEC103AnalysisApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


extern CIEC103AnalysisApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IEC103ANALYSIS_H__F02D8995_3E57_41E6_BDFE_FA6261E53B86__INCLUDED_)
