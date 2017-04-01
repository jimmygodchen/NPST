// IEC103AnalysisDoc.cpp : implementation of the CIEC103AnalysisDoc class
//

#include "stdafx.h"
#include "IEC103Analysis.h"

#include "IEC103AnalysisDoc.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIEC103AnalysisDoc

IMPLEMENT_DYNCREATE(CIEC103AnalysisDoc, CRichEditDoc)

BEGIN_MESSAGE_MAP(CIEC103AnalysisDoc, CRichEditDoc)
	//{{AFX_MSG_MAP(CIEC103AnalysisDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, CRichEditDoc::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, CRichEditDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, CRichEditDoc::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIEC103AnalysisDoc construction/destruction

CIEC103AnalysisDoc::CIEC103AnalysisDoc()
{
	// TODO: add one-time construction code here

}

CIEC103AnalysisDoc::~CIEC103AnalysisDoc()
{
}

BOOL CIEC103AnalysisDoc::OnNewDocument()
{
	if (!CRichEditDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

CRichEditCntrItem* CIEC103AnalysisDoc::CreateClientItem(REOBJECT* preo) const
{
	// cast away constness of this
	return new CIEC103AnalysisCntrItem(preo, (CIEC103AnalysisDoc*) this);
}



/////////////////////////////////////////////////////////////////////////////
// CIEC103AnalysisDoc serialization

// void CIEC103AnalysisDoc::Serialize(CArchive& ar)
// {
// 	if (ar.IsStoring())
// 	{
// 		// TODO: add storing code here
// 	}
// 	else
// 	{
// 		// TODO: add loading code here
// 	}
// 
// 	// Calling the base class CRichEditDoc enables serialization
// 	//  of the container document's COleClientItem objects.
// 	// TODO: set CRichEditDoc::m_bRTF = FALSE if you are serializing as text
// 	CRichEditDoc::Serialize(ar);
// }

/////////////////////////////////////////////////////////////////////////////
// CIEC103AnalysisDoc diagnostics

#ifdef _DEBUG
void CIEC103AnalysisDoc::AssertValid() const
{
	CRichEditDoc::AssertValid();
}

void CIEC103AnalysisDoc::Dump(CDumpContext& dc) const
{
	CRichEditDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIEC103AnalysisDoc commands
