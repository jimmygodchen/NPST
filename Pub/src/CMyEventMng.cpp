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

//---------------------------------------------- CMyEventMng -----------------------
IMPLEMENT_SERIAL(CMyEventMng,CMyObj,0)

CMyEventMng::CMyEventMng():CMyObj()
{
    m_pwndMsg = NULL;
}

CMyEventMng::~CMyEventMng()
{
}

void CMyEventMng::SndMsg(const EVTMSG& EventMsg)
{
    if(m_pwndMsg)
    {
        m_critical.Lock();
        m_aEvent.Add((EVTMSG&)EventMsg);
        m_critical.Unlock();
        //         ::SendMessage(m_pwndMsg->m_hWnd, WM_PORTMSG, (WPARAM)0, (LPARAM)m_nID);
        ::PostMessage(m_pwndMsg->m_hWnd, WM_EVENTMSG, (WPARAM)0, (LPARAM)0);
    }
}

BOOL CMyEventMng::GetMsg(EVTMSG& EventMsg)
{
    m_critical.Lock();
    int nSize = m_aEvent.GetSize();
    m_critical.Unlock();
    if(nSize>0)
    {
        m_critical.Lock();
        EventMsg = m_aEvent[0];
        m_aEvent.RemoveAt(0);
        m_critical.Unlock();
        return TRUE;
    }
    return FALSE;
}

void CMyEventMng::Empty(void)
{
    m_critical.Lock();
    int nSize = m_aEvent.GetSize();
    m_critical.Unlock();
    if(nSize>0)
    {
        m_critical.Lock();
        m_aEvent.RemoveAll();
        m_critical.Unlock();
    }
}


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------



