// OutputBar.cpp : implementation of the COutputBar class
//

#include "stdafx.h"
#include "IEC103Analysis.h"
#include "OutputBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int nBorderSize = 1;

#define LINE_LIMIT		3000				// CRichView显示最大行数

/////////////////////////////////////////////////////////////////////////////
// COutputBar

BEGIN_MESSAGE_MAP(COutputBar, CBCGPDockingControlBar)
	//{{AFX_MSG_MAP(COutputBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
    ON_MESSAGE(WM_EVENTMSG, OnEventMsg)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// COutputBar construction/destruction

COutputBar::COutputBar()
{
	// TODO: add one-time construction code here

}

COutputBar::~COutputBar()
{
}

/////////////////////////////////////////////////////////////////////////////
// COutputBar message handlers


static int GetTwipSize (CString str)
{
    LPCTSTR lpszText = str;
    
    while (*lpszText == ' ' || *lpszText == '\t')
        lpszText++;
    
    if (lpszText[0] == NULL)
        return -1; // no text in control
    
    double d = _tcstod(lpszText, (LPTSTR*)&lpszText);
    while (*lpszText == ' ' || *lpszText == '\t')
        lpszText++;
    
    if (*lpszText != NULL)
        return -2;   // not terminated properly
    
    return (d<0.) ? 0 : (int)(d*20.);
}

int COutputBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rectDummy;
	rectDummy.SetRectEmpty ();

    if(!m_wndEdit.Create(WS_CHILD|WS_BORDER|WS_VISIBLE | WS_HSCROLL | WS_VSCROLL
        |ES_MULTILINE|ES_SELECTIONBAR |ES_AUTOHSCROLL|ES_AUTOVSCROLL | ES_WANTRETURN,
        rectDummy,this,1))
    {
        TRACE0("Failed to create output tab window\n");
        return -1;      // fail to create
    }

    CHARFORMATA cf;
    m_wndEdit.SetRedraw(FALSE);
    
    cf.cbSize = sizeof(CHARFORMAT);
    cf.dwMask = CFM_BOLD|CFM_SIZE|CFM_FACE|CFM_COLOR;
    cf.crTextColor = RGB(255,0,0);
    lstrcpyn(cf.szFaceName,"宋体",5);
    cf.yHeight = GetTwipSize("10");
    cf.dwEffects = 0;
    m_wndEdit.SetWordCharFormat(cf);
    m_wndEdit.SetRedraw(TRUE);
    m_wndEdit.RedrawWindow();

// 	// Create tabs window:
// 	if (!m_wndTabs.Create (CBCGPTabWnd::STYLE_FLAT, rectDummy, this, 1))
// 	{
// 		TRACE0("Failed to create output tab window\n");
// 		return -1;      // fail to create
// 	}
// 
// 	// Create list windows.
// 	// TODO: create your own window here:
// 	const DWORD dwViewStyle =	
// 		LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;
// 	
// 	if (!m_wndList1.Create (dwViewStyle, rectDummy, &m_wndTabs, 2) ||
// 		!m_wndList2.Create (dwViewStyle, rectDummy, &m_wndTabs, 3) ||
// 		!m_wndList3.Create (dwViewStyle, rectDummy, &m_wndTabs, 4))
// 	{
// 		TRACE0("Failed to create output view\n");
// 		return -1;      // fail to create
// 	}
// 
// 	// Attach list windows to tab:
// 	m_wndTabs.AddTab (&m_wndList1, _T("Output 1"), -1);
// 	m_wndTabs.AddTab (&m_wndList2, _T("Output 2"), -1);
// 	m_wndTabs.AddTab (&m_wndList3, _T("Output 3"), -1);

	return 0;
}

void COutputBar::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);

	// Tab control should cover a whole client area:
// 	m_wndTabs.SetWindowPos (NULL, -1, -1, cx, cy,
// 		SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
    m_wndEdit.SetWindowPos (NULL, -1, -1, cx, cy,
        SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void COutputBar::ShowCommData(CString str, COLORREF cr)
{
    m_wndEdit.SetRedraw(FALSE);
    
    int nTextLength = m_wndEdit.GetWindowTextLength();
    int nLineCnt = m_wndEdit.GetLineCount();
    if(nLineCnt>LINE_LIMIT)
    {
        m_wndEdit.SetSel(0, nTextLength);
        m_wndEdit.Clear();
    }
    nTextLength = m_wndEdit.GetWindowTextLength();
    
    m_wndEdit.SetSel(nTextLength, nTextLength);
    
//     m_wndEdit.OnColorPick(cr);

    CHARFORMATA cf;
//     m_wndEdit.SetRedraw(FALSE);
    
    cf.cbSize = sizeof(CHARFORMAT);
    cf.dwMask = CFM_BOLD|CFM_SIZE|CFM_FACE|CFM_COLOR;
    cf.crTextColor = cr;
    lstrcpyn(cf.szFaceName,"宋体",5);
    cf.yHeight = GetTwipSize("10");
    cf.dwEffects = 0;
    m_wndEdit.SetWordCharFormat(cf);

//     CHARFORMATA cf;
// //     m_wndEdit.SetRedraw(FALSE);
//     
// //     cf.cbSize = sizeof(CHARFORMAT);
//     cf.dwMask = CFM_COLOR;
//     cf.crTextColor = cr;
// //     lstrcpyn(cf.szFaceName,"宋体",5);
// //     cf.yHeight = GetTwipSize("10");
// //     cf.dwEffects = 0;
//     m_wndEdit.SetWordCharFormat(cf);

    m_wndEdit.ReplaceSel(str);
    
    m_wndEdit.SetRedraw(TRUE);
    m_wndEdit.RedrawWindow();
}

LONG COutputBar::OnEventMsg(WPARAM wParm, LPARAM lParam)
{
    EVTMSG EventMsg;
    while(g_MngEvent.GetMsg(EventMsg))
    {
        CString str;
        str.Format("%d-%02d-%02d %02d:%02d:%02d,%03d ",
            EventMsg.wYear, EventMsg.Mon, EventMsg.Day, EventMsg.Hour, EventMsg.Min, EventMsg.Sec, EventMsg.wMs);
        str += EventMsg.strContent + "\r\n";
        ShowCommData(str, EventMsg.clrColor);
    }
    return 0;
}
