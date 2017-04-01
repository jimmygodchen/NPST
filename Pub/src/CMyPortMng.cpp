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

//---------------------------------------------- CMyPortMng -----------------------
IMPLEMENT_SERIAL(CMyPortMng,CMyObj,0)

CMyPortMng::CMyPortMng():CMyObj()
{
    m_pPort = NULL;
}

CMyPortMng::~CMyPortMng()
{
    if(m_pPort)
    {
        delete m_pPort;
        m_pPort = NULL;
    }
}

void CMyPortMng::OpenAllPorts(void)
{
    ASSERT(m_pPort);
    int nSizeUnit = m_pPort->m_aUnit.GetSize();
    for(int j=0;j<nSizeUnit;j++)
    {
        CMyUnit* pUnit = m_pPort->m_aUnit[j];
        pUnit->OnPortOpen();
    }
    m_pPort->StartComLoop();
}

void CMyPortMng::CloseAllPorts(void)
{
    ASSERT(m_pPort);
    m_pPort->StopComLoop();
    int nSizeUnit = m_pPort->m_aUnit.GetSize();
    for(int j=0;j<nSizeUnit;j++)
    {
        CMyUnit* pUnit = m_pPort->m_aUnit[j];
        pUnit->OnPortClose();
    }
}

CMyPort* CMyPortMng::GetPort(int nPortID)
{
    if(m_pPort && m_pPort->m_nID==nPortID)
    {
        return m_pPort;
    }
    return NULL;
}


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------



