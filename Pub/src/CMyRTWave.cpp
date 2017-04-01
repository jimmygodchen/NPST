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
#include "resource.h"
#include "Pub.h"
#include "CMyDlgRTWave.h"

//---------------------------------------------- CMyRTWave -----------
IMPLEMENT_SERIAL(CMyRTWave, CMyDataOperate, 0)

CMyRTWave::CMyRTWave():CMyDataOperate()
{
    m_nDotPerWave = 0;
    m_pfRTWave = NULL;
}

CMyRTWave::~CMyRTWave()
{
    if(m_pfRTWave)
    {
        delete [] m_pfRTWave;
        m_pfRTWave = NULL;
    }
}

// void CMyRTWave::Serialize(CArchive& ar)
// {
//     CMyDataOperate::Serialize(ar);
//     if(ar.IsStoring())
//     {
//         ar << m_nDotPerWave;
//     }
//     else
//     {
//         ar >> m_nDotPerWave;
//     }
// }

void CMyRTWave::Initialize(CString strName, const CMyRTWaveChInfoArray& arRTWaveChInfo, int nDotPerWave)
{
    CMyDataOperate::Initialize(strName);
    m_arRTWaveChInfo.RemoveAll();
    int nChNum = arRTWaveChInfo.GetSize();
    for(int i=0;i<nChNum;i++)
    {
        m_arRTWaveChInfo.Add(arRTWaveChInfo[i]);
    }
    m_nDotPerWave = nDotPerWave;

    m_pfRTWave = new float[nChNum*m_nDotPerWave];
    memset(m_pfRTWave, 0, sizeof(float)*nChNum*m_nDotPerWave);
}

int CMyRTWave::GetChNum(void)
{
    return m_arRTWaveChInfo.GetSize();
}

void CMyRTWave::RefreshData(int nChIndex, const float* pfData)
{
    int nChNum = m_arRTWaveChInfo.GetSize();
    ASSERT(nChIndex<nChNum);
    if(m_arRTWaveChInfo[nChIndex].bVisible)
    {
        int nStart = nChIndex*m_nDotPerWave;
        for(int i=0;i<m_nDotPerWave;i++)
        {
            m_pfRTWave[nStart+i] = pfData[i];
        }
    }
}

const tRTWAVECHINFO& CMyRTWave::GetChInfo(int nChIndex)
{
    int nChNum = m_arRTWaveChInfo.GetSize();
    ASSERT(nChIndex<nChNum);
    return m_arRTWaveChInfo[nChIndex];
}

BOOL CMyRTWave::ExeOperate(void)
{
    m_OperateCode = 0xff;
    IncrementUpdateID();
    CMyDlgRTWave dlg;
    dlg.m_pRTWave = this;
    MyDoModal(&dlg, PublicDLL.hModule);
    return TRUE;
}

void CMyRTWave::SetChVisible(int nChIndex, BOOL bVisible)
{
    int nChNum = m_arRTWaveChInfo.GetSize();
    ASSERT(nChIndex<nChNum);
    m_arRTWaveChInfo[nChIndex].bVisible = bVisible;
}

int CMyRTWave::GetDotNum(void)
{
    return m_nDotPerWave;
}

const float* CMyRTWave::GetBuff(int nChIndex)
{
    return m_pfRTWave + nChIndex*m_nDotPerWave;
}




//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------



