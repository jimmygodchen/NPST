//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#include "StdAfx.h"
#include "Pub.h"

//---------------------------------------------- CMyPort Static ---------------
CStringArray CMyPort::s_aType;
CMapStringToPtr CMyPort::s_mapTypeToClass;

void CMyPort::RegisterClass(CString strType, CRuntimeClass* pRuntimeClass)
{
    strType.TrimLeft();
    strType.TrimRight();

    ASSERT(!strType.IsEmpty());

    //     if(strType.IsEmpty()) return;
    if(pRuntimeClass->IsDerivedFrom(RUNTIME_CLASS(CMyPort)))
    {
        s_mapTypeToClass[strType] = pRuntimeClass;
        for(int i=0;i<s_aType.GetSize();i++) if(strType==s_aType[i]) break;
        if(i==s_aType.GetSize()) s_aType.Add(strType);
    }
}

static UINT ComLoop(LPVOID pParam)
{
    CMyWorkThread* pWorkThread = (CMyWorkThread*)pParam;
    CMyPort* pPort = (CMyPort*)(pWorkThread->m_pParam);
    ASSERT(pPort);
    ASSERT(pPort->IsKindOf(RUNTIME_CLASS(CMyPort)));
    ASSERT(pPort->m_pWorkThread==pWorkThread);
    pPort->ComLoop();
    TRACE("Thread <ComLoop:"+pPort->m_strName+"> End!\n");
    return 0;
}

//---------------------------------------------- CMyPort -----------------------
IMPLEMENT_SERIAL(CMyPort,CMyObj,0)

CMyPort::CMyPort():CMyObj()
{
    m_wDelayWriteCom = 20;
    m_nComUnitNo = -1;
    m_pWorkThread = NULL;
    m_bAutoSndMsg = TRUE;
    m_pwndMsg = NULL;
}

CMyPort::~CMyPort()
{
    int i;
    m_pwndMsg = NULL;

//     PORTMSG PortMsg;
//     while(GetMsg(PortMsg));

    m_critical.Lock();
    int nSize = m_aMsg.GetSize();
    m_critical.Unlock();
    while(nSize>0)
    {
        m_critical.Lock();
        PORTMSG* pPortMsg = (PORTMSG*)m_aMsg[0];
        m_aMsg.RemoveAt(0);
        m_critical.Unlock();
        delete pPortMsg;
        m_critical.Lock();
        nSize = m_aMsg.GetSize();
        m_critical.Unlock();
    }

    nSize = m_aUnit.GetSize();
    for(i=0;i<nSize;i++) delete m_aUnit[i];
    m_aUnit.RemoveAll();
}


void CMyPort::StartComLoop(void)
{
    ASSERT(m_pWorkThread==NULL);
    m_pWorkThread = new CMyWorkThread;
    m_pWorkThread->Run(::ComLoop,this,THREAD_PRIORITY_NORMAL);
}

void CMyPort::StopComLoop(void)
{
    ASSERT(m_pWorkThread);
    m_pWorkThread->Exit();
    delete m_pWorkThread;
    m_pWorkThread = NULL;
}

void CMyPort::ComLoop(void)
{
    int nUnitSize = m_aUnit.GetSize();
    if(nUnitSize==0) return;

    ASSERT(m_pWorkThread);
    m_pWorkThread->InternalRun();
    
    if(!OpenCom())
    {
        CloseCom();
        m_pWorkThread->InternalReset();
        MessageBox(NULL, _T("打开端口失败！"), _T("告警"), MB_ICONSTOP);
        return;
    }
    COMCONTROL cc;
    cc.pTXBuffer = new BYTE[COMBUFFSIZE];
    cc.pRXBuffer = new BYTE[COMBUFFSIZE];
    cc.pPort = this;
    m_nComUnitNo = 0;
    while(!m_pWorkThread->InternalIsExiting())
    {
        CMyUnit* pUnit = m_aUnit[m_nComUnitNo];
        pUnit->ExchangeComData(&cc);
        m_nComUnitNo++;
        m_nComUnitNo %= nUnitSize;
        Sleep(1);
    }
    delete[] cc.pTXBuffer;
    delete[] cc.pRXBuffer;
    CloseCom();
    m_pWorkThread->InternalReset();
}

void CMyPort::SndMsg(const PORTMSG& PortMsg)
{
    if(m_pwndMsg)
    {
        PORTMSG* pPortMsg = new PORTMSG;
        ASSERT(pPortMsg);
        *pPortMsg = PortMsg;
        m_critical.Lock();
        m_aMsg.Add(pPortMsg);
        m_critical.Unlock();
//         ::SendMessage(m_pwndMsg->m_hWnd, WM_PORTMSG, (WPARAM)0, (LPARAM)m_nID);
        ::PostMessage(m_pwndMsg->m_hWnd, WM_PORTMSG, (WPARAM)0, (LPARAM)m_nID);
    }
}

BOOL CMyPort::GetMsg(PORTMSG& PortMsg)
{
    m_critical.Lock();
    int nSize = m_aMsg.GetSize();
    m_critical.Unlock();
    if(nSize>0)
    {
        m_critical.Lock();
        PORTMSG* pPortMsg = (PORTMSG*)m_aMsg[0];
        m_aMsg.RemoveAt(0);
        m_critical.Unlock();
        PortMsg = *pPortMsg;
        delete pPortMsg;
        return TRUE;
    }
    return FALSE;
    
}

void CMyPort::AddComReportRX(BYTE* pData, int nCount)
{
    if(m_pwndMsg && m_bAutoSndMsg && nCount>0)
    {
        PORTMSG PortMsg;
        PortMsg.clrColor = RGB(0,0,0x80);
        CString strContent = _T("");
        for(int i=0;i<nCount;i++)
        {
            CString strTmp;
//             strTmp.Format("0x%02X ", pData[i]);
            strTmp.Format("%02X ", pData[i]);
            strContent += strTmp;
        }
        PortMsg.strContent = _T("RX: ") + strContent;
        CTime timeNow = CTime::GetCurrentTime();
        if(timeNow.GetYear()>2000)
        {
            PortMsg.strContent += _T("    --[") + timeNow.Format("%Y-%m-%d %H:%M:%S") + _T("]\r\n");
        }
        SndMsg(PortMsg);
    }
}

void CMyPort::AddComReportTX(BYTE* pData, int nCount)
{
    if(m_pwndMsg && m_bAutoSndMsg && nCount>0)
    {
        PORTMSG PortMsg;
        PortMsg.clrColor = RGB(0x80,0,0);
        CString strContent = _T("");
        for(int i=0;i<nCount;i++)
        {
            CString strTmp;
//             strTmp.Format("0x%02X ", pData[i]);
            strTmp.Format("%02X ", pData[i]);
            strContent += strTmp;
        }
        PortMsg.strContent = _T("TX: ") + strContent;
        CTime timeNow = CTime::GetCurrentTime();
        if(timeNow.GetYear()>2000)
        {
            PortMsg.strContent += _T("    --[") + timeNow.Format("%Y-%m-%d %H:%M:%S") + _T("]\r\n");
        }
        SndMsg(PortMsg);
    }
}

//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------



