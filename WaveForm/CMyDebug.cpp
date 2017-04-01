// CMyDebug.cpp : implementation file
//

#include "stdafx.h"
#include "WaveForm.h"
#include "WaveFormDoc.h"
#include "CMyDebug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDebug dialog


CMyDebug::CMyDebug(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CMyDebug::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDebug)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pDoc = NULL;
}

void CMyDebug::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDebug)
	DDX_Control(pDX, IDC_LIST_SET, m_listSet);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyDebug, CBCGPDialog)
	//{{AFX_MSG_MAP(CMyDebug)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDebug message handlers

BOOL CMyDebug::OnInitDialog() 
{
	CBCGPDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	ASSERT_VALID(m_pDoc);

// 	DWORD dwExtendedStyle = m_listSet.GetExtendedStyle();
// 	m_listSet.SetExtendedStyle(dwExtendedStyle|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
// 	m_listSet.InsertColumn(0,"序号",LVCFMT_CENTER,35);
// 	m_listSet.InsertColumn(1,"属性",LVCFMT_LEFT,120);
// 	m_listSet.InsertColumn(2,"值",LVCFMT_LEFT,80);
// 
// 	int nItemIndex = 0;
// 	CString strItem = _T("");
// 	WFRSETTING* pWFRSet = &m_pDoc->m_WaveForm.Setting;
// 	for(int i=0;i<8;i++,nItemIndex++)
// 	{
// 		strItem.Format("%d",nItemIndex+1);
// 		m_listSet.InsertItem(nItemIndex,strItem);
// 		strItem.Format("通道ID%d(BIID%d))",nItemIndex+1,nItemIndex+1);
// 		m_listSet.SetItemText(nItemIndex,1,strItem);
// 		strItem.Format("%d",pWFRSet->wBIID[nItemIndex]);
// 		m_listSet.SetItemText(nItemIndex,2,strItem);
// 	}
// 	for(i=0;i<3;i++,nItemIndex++)
// 	{
// 		strItem.Format("%d",nItemIndex+1);
// 		m_listSet.InsertItem(nItemIndex,strItem);
// 		strItem.Format("通道ID%d(AIID%d))",nItemIndex+1,nItemIndex-7);
// 		m_listSet.SetItemText(nItemIndex,1,strItem);
// 		strItem.Format("%d",pWFRSet->wAIID[nItemIndex-8]);
// 		m_listSet.SetItemText(nItemIndex,2,strItem);
// 	}
// 
// 	strItem.Format("%d",nItemIndex+1);
// 	m_listSet.InsertItem(nItemIndex,strItem);
// 	m_listSet.SetItemText(nItemIndex,1,"采样间隔");
// 	char* pchSI[7] =
// 	{
// 		"10ms","20ms","50ms","100ms","1s","1m","Err"
// 	};
// 	int nSampleInteval = pWFRSet->wSampleInteval;
// 	if(nSampleInteval>6) nSampleInteval = 6;
// 	strItem = pchSI[nSampleInteval];
// 	m_listSet.SetItemText(nItemIndex++,2,strItem);
// 
// 	strItem.Format("%d",nItemIndex+1);
// 	m_listSet.InsertItem(nItemIndex,strItem);
// 	m_listSet.SetItemText(nItemIndex,1,"触发源ID");
// 	strItem.Format("%d",pWFRSet->wTrigSource);
// 	m_listSet.SetItemText(nItemIndex++,2,strItem);
// 
// 	strItem.Format("%d",nItemIndex+1);
// 	m_listSet.InsertItem(nItemIndex,strItem);
// 	m_listSet.SetItemText(nItemIndex,1,"触发方式");
// 	char* pchTripType[6] =
// 	{
// 		"上升沿","下降沿","边沿","高电平","低电平","Err"
// 	};
// 	int nTripType = pWFRSet->wTrigType;
// 	if(nTripType>5) nTripType = 5;
// 	strItem = pchTripType[nTripType];
// 	m_listSet.SetItemText(nItemIndex++,2,strItem);
// 
// 	strItem.Format("%d",nItemIndex+1);
// 	m_listSet.InsertItem(nItemIndex,strItem);
// 	m_listSet.SetItemText(nItemIndex,1,"模拟量触发门槛");
// 	strItem.Format("%.2f",pWFRSet->wTrigThreshold*0.01f);
// 	m_listSet.SetItemText(nItemIndex++,2,strItem);
// 
// 	strItem.Format("%d",nItemIndex+1);
// 	m_listSet.InsertItem(nItemIndex,strItem);
// 	m_listSet.SetItemText(nItemIndex,1,"示波器设置模式");
// 	char* pchOSCMode[3] =
// 	{
// 		"Basic","Advanced","Err"
// 	};
// 	int nOSCMode = pWFRSet->wOSCMode;
// 	if(nOSCMode>2) nOSCMode = 2;
// 	strItem = pchOSCMode[nOSCMode];
// 	m_listSet.SetItemText(nItemIndex++,2,strItem);
// 
// 	strItem.Format("%d",nItemIndex+1);
// 	m_listSet.InsertItem(nItemIndex,strItem);
// 	m_listSet.SetItemText(nItemIndex,1,"触发模式");
// 	char* pchTripMode[3] =
// 	{
// 		"单次","自动触发","Err"
// 	};
// 	int nTripMode = pWFRSet->wTrigMode;
// 	if(nTripMode>2) nTripMode = 2;
// 	strItem = pchTripMode[nTripMode];
// 	m_listSet.SetItemText(nItemIndex++,2,strItem);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
