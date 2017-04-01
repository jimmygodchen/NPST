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

//---------------------------------------------- CMyFactory -------------------
IMPLEMENT_SERIAL(CMyFactory,CMyObj,0)

CMyFactory::CMyFactory():CMyObj()
{
    m_pData = NULL;
}

CMyFactory::~CMyFactory()
{
    if(m_pData) delete m_pData;
}

void CMyFactory::DeleteData(void)
{
    if(m_pData) delete m_pData;
    m_pData = NULL;
}

CMyData* CMyFactory::CreateData(void)
{
    if(m_pData==NULL)
    {
        CRuntimeClass* pRuntimeClass = NULL;
        CMyData::s_mapTypeToClass.Lookup(m_strType,(void*&)pRuntimeClass);
        if(pRuntimeClass==NULL) return NULL;
        m_pData = (CMyData*)(pRuntimeClass->CreateObject());
        if(m_pData==NULL)
        {
            MyAbortSystem("系统内存不够,创建数据<"+m_strType+">失败!");
            return NULL;
        }
        m_pData->m_strField = m_strField;
        m_pData->m_strName = m_strField;
    }
    return m_pData;
}

//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------



