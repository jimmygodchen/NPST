// WaveFormDoc.cpp : implementation of the CWaveFormDoc class
//

#include "stdafx.h"
#include "WaveForm.h"

#include "WaveFormDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWaveFormDoc

IMPLEMENT_DYNCREATE(CWaveFormDoc, CDocument)

BEGIN_MESSAGE_MAP(CWaveFormDoc, CDocument)
	//{{AFX_MSG_MAP(CWaveFormDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWaveFormDoc construction/destruction

CWaveFormDoc::CWaveFormDoc()
{
	// TODO: add one-time construction code here
	m_bFileOK = FALSE;
}

CWaveFormDoc::~CWaveFormDoc()
{
}

BOOL CWaveFormDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CWaveFormDoc serialization

void CWaveFormDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
        m_bFileOK = m_Wave.Serialize(ar);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CWaveFormDoc diagnostics

#ifdef _DEBUG
void CWaveFormDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWaveFormDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWaveFormDoc commands
