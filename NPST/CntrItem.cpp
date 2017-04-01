// CntrItem.cpp : implementation of the CIEC103AnalysisCntrItem class
//

#include "stdafx.h"
#include "IEC103Analysis.h"

#include "IEC103AnalysisDoc.h"
#include "IEC103AnalysisView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIEC103AnalysisCntrItem implementation

IMPLEMENT_SERIAL(CIEC103AnalysisCntrItem, CRichEditCntrItem, 0)

CIEC103AnalysisCntrItem::CIEC103AnalysisCntrItem(REOBJECT* preo, CIEC103AnalysisDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: add one-time construction code here
	
}

CIEC103AnalysisCntrItem::~CIEC103AnalysisCntrItem()
{
	// TODO: add cleanup code here
	
}

BOOL CIEC103AnalysisCntrItem::OnShowControlBars(CFrameWnd* pFrameWnd, BOOL bShow)
{
	CBCGPMDIFrameWnd* pMainFrame = DYNAMIC_DOWNCAST (CBCGPMDIFrameWnd, pFrameWnd);
	if (pMainFrame != NULL)
	{
		return pMainFrame->OnShowControlBars (bShow);
	}
	else	// Maybe, SDI frame...
	{
		CBCGPFrameWnd* pFrame = DYNAMIC_DOWNCAST (CBCGPFrameWnd, pFrameWnd);
		if (pFrame != NULL)
		{
			return pFrame->OnShowControlBars (bShow);
		}
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CIEC103AnalysisCntrItem diagnostics

#ifdef _DEBUG
void CIEC103AnalysisCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CIEC103AnalysisCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
