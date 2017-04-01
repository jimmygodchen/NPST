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

//---------------------------------------------- CMyWaveInfo ------------------
CMyWaveInfo::CMyWaveInfo()
{
    m_pDataAD = NULL;
    m_pDataDI = NULL;
    m_NumChannelAD = 0;
    m_NumChannelDI = 0;
    m_wDotPerChannel = 0;
}

CMyWaveInfo::~CMyWaveInfo()
{
    Destroy();
}

void CMyWaveInfo::Create(BYTE NumChannelAD,BYTE NumChannelDI,WORD wDotPerChannel,WORD wFrequency)
{
    ASSERT(NumChannelAD>0 || NumChannelDI>0);
    ASSERT(wDotPerChannel>0);

    Destroy();
    m_NumChannelAD = NumChannelAD;
    m_NumChannelDI = NumChannelDI;
    m_wDotPerChannel = wDotPerChannel;
    m_wFrequency = wFrequency;
    int i;
    m_pDataAD = new float[m_wDotPerChannel*m_NumChannelAD];
    for(i=0;i<m_NumChannelAD*m_wDotPerChannel;i++)
    {
        m_pDataAD[i] = 0.0f;
    }
    m_pDataDI = new BYTE[m_wDotPerChannel*m_NumChannelDI];
    for(i=0;i<m_NumChannelDI*m_wDotPerChannel;i++)
    {
        m_pDataDI[i] = 0;
    }
    m_astrNameAD.SetSize(m_NumChannelAD);
    m_astrUnitageAD.SetSize(m_NumChannelAD);
    m_astrNameDI.SetSize(m_NumChannelDI);
}

void CMyWaveInfo::Destroy(void)
{
    if(m_pDataAD) delete[] m_pDataAD;
    m_pDataAD = NULL;

    if(m_pDataDI) delete[] m_pDataDI;
    m_pDataDI = NULL;
    m_NumChannelAD = 0;
    m_NumChannelDI = 0;
    m_wDotPerChannel = 0;
}

void CMyWaveInfo::SetTime(time_t timeStart,WORD wMilliSecond)
{
    CTime time = timeStart;
    SetTime(time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond(),wMilliSecond);
}

void CMyWaveInfo::SetTime(WORD wYear,WORD wMonth,WORD wDay,WORD wHour,WORD wMinute,WORD wSecond,WORD wMilliSecond)
{
    m_wYear = wYear;
    m_wMonth = wMonth;
    m_wDay = wDay;
    m_wHour = wHour;
    m_wMinute = wMinute;
    m_wSecond = wSecond;
    m_wMilliSecond = wMilliSecond;
}

void CMyWaveInfo::SetChannelInfoAD(BYTE ChannelNo,CString strName,CString strUnitage,float fFullScale)
{
    if(ChannelNo>=m_NumChannelAD) return;
    m_astrNameAD[ChannelNo] = strName;
    m_astrUnitageAD[ChannelNo] = strUnitage;
// 	m_fFullScaleAD[ChannelNo] = fFullScale;
}

void CMyWaveInfo::SetChannelInfoDI(BYTE ChannelNo,CString strName,CString strStatus0,CString strStatus1)
{
    if(ChannelNo>=m_NumChannelDI) return;
    m_astrNameDI[ChannelNo] = strName;
//     m_strStatus0DI[ChannelNo] = strStatus0;
//     m_strStatus1DI[ChannelNo] = strStatus1;
}

void CMyWaveInfo::LoadFromFile(CString strFileName)
{
    if(strFileName.IsEmpty()) return;
    Destroy();
//     CMemFile file;
//     if(MyClientCommandRcvFile(g_strSCADADAT_WAVE+strFileName,&file,NULL))
    CFile file;
    if(file.Open(strFileName,CFile::modeRead/*|CFile::modeCreate*/))
    {
//         file.Seek(0,CFile::begin);
        CArchive ar(&file,CArchive::load);
//         CString strID;
//         ar >> strID;
//         if(strID!="WAVE-FORMAT-1.0")
//         {
//             MyMessageBox("录波文件格式不匹配,不能装入!","出错",MB_OK|MB_ICONWARNING);
//             return;
//         }
//         ar >> m_wYear;
//         ar >> m_wMonth;
//         ar >> m_wDay;
//         ar >> m_wHour;
//         ar >> m_wMinute;
//         ar >> m_wSecond;
//         ar >> m_wMilliSecond;
//         ar >> m_NumChannelAD;
//         ar >> m_NumChannelDI;
//         ar >> m_wDotPerChannel;
//         ar >> m_wFrequency;
//         if(!IsWaveValid())
//         {
//             MyMessageBox("录波配置信息不正确,不能装入!","出错",MB_OK|MB_ICONWARNING);
//             Destroy();
//             return;
//         }
//         Create(m_NumChannelAD,m_NumChannelDI,m_wDotPerChannel,m_wFrequency);
//         int i,j;
//         for(i=0;i<m_NumChannelAD;i++)
//         {
//             ar >> m_astrNameAD[i];
//             ar >> m_astrUnitageAD[i];
// //          ar >> m_fFullScaleAD[i];
//         }
//         for(i=0;i<m_NumChannelDI;i++)
//         {
//             ar >> m_astrNameDI[i];
// //          ar >> m_strStatus0DI[i];
// //          ar >> m_strStatus1DI[i];
//         }
// 
// //         for(i=0;i<m_wDotPerChannel;i++)
// //         {
// //             float* pDataAD = m_pDataAD + m_wDotPerChannel * i;
// //             BYTE* pDataDI = m_pDataDI + m_wDotPerChannel * i;
// //             for(j=0;j<m_NumChannelAD;j++) ar >> pDataAD[j];
// //             for(j=0;j<m_NumChannelDI;j++) ar >> pDataDI[j];
// //         }
//         for(i=0;i<m_NumChannelAD;++i)
//         {
//             float* pDataAD = m_pDataAD + m_wDotPerChannel * i;
//             for(j=0;j<m_wDotPerChannel;++j) ar >> pDataAD[j];
//         }
//         for(i=0;i<m_NumChannelDI;++i)
//         {
//             BYTE* pDataDI = m_pDataDI + m_wDotPerChannel * i;
//             for(j=0;j<m_wDotPerChannel;++j) ar >> pDataDI[j];
//         }
        Serialize(ar);
        ar.Close();
        file.Close();
    }
}

void CMyWaveInfo::StoreToFile(CString strUnitName,CString strFileName)
{
    CString strWaveDir = g_strSysPath+"\\Wave\\"+strUnitName;
    _mkdir(strWaveDir);
    if(!IsWaveValid()) return;
    if(strFileName.IsEmpty()) return;
    strFileName = strWaveDir+"\\"+strFileName;
    CFile file;
    if(file.Open(strFileName,CFile::modeWrite|CFile::modeCreate))
    {
        CArchive ar(&file,CArchive::store);
//         CString strID = "WAVE-FORMAT-1.0";
//         ar << strID;
//         ar << m_wYear;
//         ar << m_wMonth;
//         ar << m_wDay;
//         ar << m_wHour;
//         ar << m_wMinute;
//         ar << m_wSecond;
//         ar << m_wMilliSecond;
//         ar << m_NumChannelAD;
//         ar << m_NumChannelDI;
//         ar << m_wDotPerChannel;
//         ar << m_wFrequency;
//         int i,j;
//         for(i=0;i<m_NumChannelAD;i++)
//         {
//             ar << m_astrNameAD[i];
//             ar << m_astrUnitageAD[i];
// //             ar << m_fFullScaleAD[i];
//         }
//         for(i=0;i<m_NumChannelDI;i++)
//         {
//             ar << m_astrNameDI[i];
// //             ar << m_strStatus0DI[i];
// //             ar << m_strStatus1DI[i];
//         }
// //         for(i=0;i<m_wDotPerChannel;i++)
// //         {
// //             float* pDataAD = m_pDataAD + m_wDotPerChannel * i;
// //             BYTE* pDataDI = m_pDataDI + m_wDotPerChannel * i;
// //             for(j=0;j<m_NumChannelAD;+j) ar << pDataAD[j];
// //             for(j=0;j<m_NumChannelDI;+j) ar << pDataDI[j];
// //         }
//         for(i=0;i<m_NumChannelAD;++i)
//         {
//             float* pDataAD = m_pDataAD + m_wDotPerChannel * i;
//             for(j=0;j<m_wDotPerChannel;++j) ar << pDataAD[j];
//         }
//         for(i=0;i<m_NumChannelDI;++i)
//         {
//             BYTE* pDataDI = m_pDataDI + m_wDotPerChannel * i;
//             for(j=0;j<m_wDotPerChannel;++j) ar << pDataDI[j];
//         }
        Serialize(ar);
        ar.Close();
        file.Close();
    }
//     else
//     {
//         CString strMessage = "故障录波文件\""+strFileName+"\"创建失败!";
//         g_pMngEvent->AddEvent("系统错误","(系统)",strMessage);
//     }
}

CString CMyWaveInfo::GetFileName(void)
{
    if(!IsWaveValid()) return CString("");
    CString strFileName;
    strFileName.Format("%04d%02d%02d_%02d%02d%02d.www",m_wYear,m_wMonth,m_wDay,m_wHour,m_wMinute,m_wSecond);
    return strFileName;
}

BOOL CMyWaveInfo::IsWaveValid(void)
{
    if(m_NumChannelAD==0 && m_NumChannelDI==0) return FALSE;
    if(m_wDotPerChannel==0) return FALSE;
    if(m_wYear<2000 || m_wYear>2200) return FALSE;
    if(m_wMonth<1 || m_wMonth>12) return FALSE;
    if(m_wDay<1 || m_wDay>31) return FALSE;
    if(m_wHour<0 || m_wHour>23) return FALSE;
    if(m_wMinute<0 || m_wMinute>59) return FALSE;
    if(m_wSecond<0 || m_wSecond>59) return FALSE;
    if(m_wMilliSecond<0 || m_wMilliSecond>999) return FALSE;
    return TRUE;
}

BOOL CMyWaveInfo::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // TODO: add storing code here
        CString strID = "WAVE-FORMAT-1.0";
        ar << strID;
        ar << m_wYear;
        ar << m_wMonth;
        ar << m_wDay;
        ar << m_wHour;
        ar << m_wMinute;
        ar << m_wSecond;
        ar << m_wMilliSecond;
        ar << m_NumChannelAD;
        ar << m_NumChannelDI;
        ar << m_wDotPerChannel;
        ar << m_wFrequency;
        int i,j;
        for(i=0;i<m_NumChannelAD;i++)
        {
            ar << m_astrNameAD[i];
            ar << m_astrUnitageAD[i];
            //             ar << m_fFullScaleAD[i];
        }
        for(i=0;i<m_NumChannelDI;i++)
        {
            ar << m_astrNameDI[i];
            //             ar << m_strStatus0DI[i];
            //             ar << m_strStatus1DI[i];
        }
        for(i=0;i<m_NumChannelAD;++i)
        {
            float* pDataAD = m_pDataAD + m_wDotPerChannel * i;
            for(j=0;j<m_wDotPerChannel;++j) ar << pDataAD[j];
        }
        for(i=0;i<m_NumChannelDI;++i)
        {
            BYTE* pDataDI = m_pDataDI + m_wDotPerChannel * i;
            for(j=0;j<m_wDotPerChannel;++j) ar << pDataDI[j];
        }

    }
    else
    {
        // TODO: add loading code here

        CString strID;
        ar >> strID;
        if(strID!="WAVE-FORMAT-1.0")
        {
            MyMessageBox("录波文件格式不匹配,不能装入!","出错",MB_OK|MB_ICONWARNING);
            return FALSE;
        }
        ar >> m_wYear;
        ar >> m_wMonth;
        ar >> m_wDay;
        ar >> m_wHour;
        ar >> m_wMinute;
        ar >> m_wSecond;
        ar >> m_wMilliSecond;
        ar >> m_NumChannelAD;
        ar >> m_NumChannelDI;
        ar >> m_wDotPerChannel;
        ar >> m_wFrequency;
        if(!IsWaveValid())
        {
            MyMessageBox("录波配置信息不正确,不能装入!","出错",MB_OK|MB_ICONWARNING);
            Destroy();
            return FALSE;
        }
        Create(m_NumChannelAD,m_NumChannelDI,m_wDotPerChannel,m_wFrequency);
        int i,j;
        for(i=0;i<m_NumChannelAD;i++)
        {
            ar >> m_astrNameAD[i];
            ar >> m_astrUnitageAD[i];
            //          ar >> m_fFullScaleAD[i];
        }
        for(i=0;i<m_NumChannelDI;i++)
        {
            ar >> m_astrNameDI[i];
            //          ar >> m_strStatus0DI[i];
            //          ar >> m_strStatus1DI[i];
        }
        
        //         for(i=0;i<m_wDotPerChannel;i++)
        //         {
        //             float* pDataAD = m_pDataAD + m_wDotPerChannel * i;
        //             BYTE* pDataDI = m_pDataDI + m_wDotPerChannel * i;
        //             for(j=0;j<m_NumChannelAD;j++) ar >> pDataAD[j];
        //             for(j=0;j<m_NumChannelDI;j++) ar >> pDataDI[j];
        //         }
        for(i=0;i<m_NumChannelAD;++i)
        {
            float* pDataAD = m_pDataAD + m_wDotPerChannel * i;
            for(j=0;j<m_wDotPerChannel;++j) ar >> pDataAD[j];
        }
        for(i=0;i<m_NumChannelDI;++i)
        {
            BYTE* pDataDI = m_pDataDI + m_wDotPerChannel * i;
            for(j=0;j<m_wDotPerChannel;++j) ar >> pDataDI[j];
        }
    }
    return TRUE;
}

//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------



