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

//---------------------------------------------- CMyDataBin ----------------
IMPLEMENT_SERIAL(CMyDataBin,CMyData,0)

CMyDataBin::CMyDataBin():CMyData()
{
    m_Status = 0;
}

// void CMyDataBin::Initialize(CString strName)
// {
//     m_strName = strName;
// }

void CMyDataBin::RefreshData(BYTE Status)
{
    if(m_Status!=Status)
    {
        m_Status = Status;
        IncrementUpdateID();
    }
}

//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------



