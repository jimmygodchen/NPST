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

//---------------------------------------------- CMyDataFloat -----------------
IMPLEMENT_SERIAL(CMyDataFloat,CMyData,0)

CMyDataFloat::CMyDataFloat():CMyData()
{
    m_strUnitage = _T("A");
    m_Format = 0x02;
    m_fData = 0;
}

void CMyDataFloat::Initialize(CString strName,CString strUnitage,BYTE Format)
{
    m_strName = strName;
    m_strUnitage = strUnitage;
    m_Format = min(Format,4);
}

void CMyDataFloat::RefreshData(float fData)
{
    if(m_fData!=fData)
    {
        m_fData = fData;
        IncrementUpdateID();
    }
}


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------



