// WaveFormDoc.h : interface of the CWaveFormDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WAVEFORMDOC_H__CA491CD1_41EA_4742_9A8C_399FFACB1EB9__INCLUDED_)
#define AFX_WAVEFORMDOC_H__CA491CD1_41EA_4742_9A8C_399FFACB1EB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//-----------------------------------------------------------------------------
class CWaveFormDoc : public CDocument
{
protected: // create from serialization only
	CWaveFormDoc();
	DECLARE_DYNCREATE(CWaveFormDoc)

// Attributes
public:
	BOOL m_bFileOK;
    CMyWaveInfo m_Wave;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWaveFormDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWaveFormDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWaveFormDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAVEFORMDOC_H__CA491CD1_41EA_4742_9A8C_399FFACB1EB9__INCLUDED_)
