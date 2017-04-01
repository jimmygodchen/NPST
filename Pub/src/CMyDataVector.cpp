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

//---------------------------------------------- CMyDataVector -----------------
IMPLEMENT_SERIAL(CMyDataVector, CMyDataFloat, 0)

CMyDataVector::CMyDataVector():CMyDataFloat(), m_vec()
{
    m_nDisplayType = 0;
    m_AngFormat = 0;
}

void CMyDataVector::Initialize(CString strName, CString strUnitage, BYTE Format, BYTE AngFormat, int nDisplayType)
{
    CMyDataFloat::Initialize(strName, strUnitage, Format);
    m_nDisplayType = nDisplayType;
    m_AngFormat = AngFormat;
}


void CMyDataVector::RefreshData(CMyVector Vec)
{
    if(m_vec!=Vec)
    {
        m_vec = Vec;
        IncrementUpdateID();
    }
}


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------



