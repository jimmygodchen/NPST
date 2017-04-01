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


//---------------------------------------------- CMyData Static ---------------
CStringArray CMyData::s_aType;
CStringArray CMyData::s_aBaseType;
CMapStringToPtr CMyData::s_mapTypeToClass;

void CMyData::RegisterClass(CString strType,CRuntimeClass* pRuntimeClass,BOOL bBaseType)
{
    strType.TrimLeft();
    strType.TrimRight();
    if(strType.IsEmpty()) return;
    if(pRuntimeClass->IsDerivedFrom(RUNTIME_CLASS(CMyData)))
    {
        POSITION pos = s_mapTypeToClass.GetStartPosition();
        while(pos)
        {
            CString strTypeTemp;
            void* pClassTemp;
            s_mapTypeToClass.GetNextAssoc(pos,strTypeTemp,pClassTemp);
            if(strTypeTemp==strType || pClassTemp==pRuntimeClass) break;
        }
        if(pos==NULL)
        {
            s_mapTypeToClass[strType] = pRuntimeClass;
            s_aType.Add(strType);
            if(bBaseType) s_aBaseType.Add(strType);
        }
    }
}

CString CMyData::GetType(CRuntimeClass* pRuntimeClass)
{
    POSITION pos = s_mapTypeToClass.GetStartPosition();
    while(pos)
    {
        CString strType;
        void* pClassTemp;
        s_mapTypeToClass.GetNextAssoc(pos,strType,pClassTemp);
        if(pClassTemp==pRuntimeClass) return strType;
    }
    return "";
}

CString CMyData::GetBaseType(CString strType)
{
    CRuntimeClass* pClass = NULL;
    CMyData::s_mapTypeToClass.Lookup(strType,(void*&)pClass);
    if(pClass)
    {
        CRuntimeClass* pBaseClass = GetBaseClass(pClass);
        if(pBaseClass) return GetType(pBaseClass);
    }
    return "";
}

CRuntimeClass* CMyData::GetBaseClass(CRuntimeClass* pRuntimeClass)
{
    ASSERT(pRuntimeClass->IsDerivedFrom(RUNTIME_CLASS(CMyData)));
    CRuntimeClass* pBaseClass = RUNTIME_CLASS(CMyData);
    int nSize = s_aBaseType.GetSize();
    for(int i=0;i<nSize;i++)
    {
        CRuntimeClass* pClassTemp = NULL;
        if(s_mapTypeToClass.Lookup(s_aBaseType[i],(void*&)pClassTemp))
        {
            if(pRuntimeClass->IsDerivedFrom(pClassTemp) && pClassTemp->IsDerivedFrom(pBaseClass)) pBaseClass = pClassTemp;
        }
    }
    return pBaseClass;
}


//---------------------------------------------- CMyData ----------------------
IMPLEMENT_SERIAL(CMyData,CMyObj,0)

CMyData::CMyData():CMyObj()
{
    m_pParentUnit = NULL;
//     m_SaveDataMode = SAVEDATAMODE_NONE;
    m_dwUpdateID = 0;
}


void CMyData::IncrementUpdateID(void)
{
    m_dwUpdateID++;
//     g_pMngData->AddUpdateData(this);
}

CString CMyData::GetFullName(void)
{
    ASSERT(m_pParentUnit);
    return "<"+m_pParentUnit->m_strName+"><"+m_strName+">";
}

CString CMyData::GetFieldAndName(void)
{
    return m_strField+":"+m_strName;
}

void CMyData::Initialize(CString strName)
{
    m_strName = strName;
}

//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------



