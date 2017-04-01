// WaveForm.h : main header file for the WAVEFORM application
//

#if !defined(AFX_WAVEFORM_H__AEC22E8B_A9ED_4FB4_B223_26194A14254A__INCLUDED_)
#define AFX_WAVEFORM_H__AEC22E8B_A9ED_4FB4_B223_26194A14254A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CWaveFormApp:
// See WaveForm.cpp for the implementation of this class
//

class CWaveFormApp : public CWinApp,
					  public CBCGPWorkspace
{
public:
	CWaveFormApp();

	// Override from CBCGPWorkspace
	virtual void PreLoadState ();

public:
// 	HINSTANCE    m_hinstBCGCBRes;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWaveFormApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL SaveAllModified();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CWaveFormApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


extern CWaveFormApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAVEFORM_H__AEC22E8B_A9ED_4FB4_B223_26194A14254A__INCLUDED_)
