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

//---------------------------------------------- CMyUnit Static ---------------
CStringArray CMyUnit::s_aType;
CMapStringToPtr CMyUnit::s_mapTypeToClass;

void CMyUnit::RegisterClass(CString strType,CRuntimeClass* pRuntimeClass)
{
    strType.TrimLeft();
    strType.TrimRight();

    ASSERT(!strType.IsEmpty());

    if(pRuntimeClass->IsDerivedFrom(RUNTIME_CLASS(CMyUnit)))
    {
        s_mapTypeToClass[strType] = pRuntimeClass;
        for(int i=0;i<s_aType.GetSize();i++) if(strType==s_aType[i]) break;
        if(i==s_aType.GetSize()) s_aType.Add(strType);
    }
}


//---------------------------------------------- CMyUnit ----------------------
IMPLEMENT_SERIAL(CMyUnit,CMyObj,0)

CMyUnit::CMyUnit():CMyObj()
{
    m_pParentPort = NULL;
}

CMyUnit::~CMyUnit()
{
    int nSize = m_aFactory.GetSize();
    for(int i=0;i<nSize;i++) delete m_aFactory[i];
    m_aFactory.RemoveAll();
}

CMyFactory* CMyUnit::AddDataFactory(CRuntimeClass* pRuntimeClass,CString strField,BOOL bCreate)
{
    if(pRuntimeClass==NULL) return NULL;
    if(!pRuntimeClass->IsDerivedFrom(RUNTIME_CLASS(CMyData))) return NULL;
    CString strType = CMyData::GetType(pRuntimeClass);
    if(strType.IsEmpty()) return NULL;      // 该数据类型没有注册;
    if(strField.IsEmpty()) return NULL;     // 数据字段不能为空;
    // 查找重复字段:
    int nSize = m_aFactory.GetSize();
    for(int i=0;i<nSize;i++)
    {
        if(m_aFactory[i]->m_strField==strField) break;
    }
    if(i==nSize)                            // 未发现重复字段,可创建;
    {
        CMyFactory* pFactory = new CMyFactory;
        pFactory->m_strType = strType;
        pFactory->m_strField = strField;
        if(bCreate)
        {
            pFactory->CreateData();
            if(pFactory->m_pData)
            {
                pFactory->m_pData->m_pParentUnit = this;
                if(!OnCreateData(pFactory->m_pData)) pFactory->DeleteData();
            }
        }
        m_aFactory.Add(pFactory);
        return pFactory;
    }
    return NULL;
}

CMyData* CMyUnit::GetData(CString strField)
{
    int nSize = m_aFactory.GetSize();
    for(int i=0;i<nSize;i++)
    {
        if(m_aFactory[i]->m_strField==strField) return m_aFactory[i]->m_pData;
    }
    return NULL;
}

void CMyUnit::AddEvent(CString strEvent)
{
    CTime timeNow = CTime::GetCurrentTime();
    if(timeNow.GetYear()<2000) return;
    WORD wTime[7];
    wTime[0] = WORD(timeNow.GetYear()-2000);
    wTime[1] = WORD(timeNow.GetMonth());
    wTime[2] = WORD(timeNow.GetDay());
    wTime[3] = WORD(timeNow.GetHour());
    wTime[4] = WORD(timeNow.GetMinute());
    wTime[5] = WORD(timeNow.GetSecond());
    
    EVTMSG EventMsg;
    EventMsg.wYear = timeNow.GetYear();
    EventMsg.Mon = timeNow.GetMonth();
    EventMsg.Day = timeNow.GetDay();
    EventMsg.Hour = timeNow.GetHour();
    EventMsg.Min = timeNow.GetMinute();
    EventMsg.Sec = timeNow.GetSecond();
    EventMsg.wMs = 0;
    EventMsg.strContent = strEvent;
    EventMsg.clrColor = RGB(255,0,0);
    g_MngEvent.SndMsg(EventMsg);
}

//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------



