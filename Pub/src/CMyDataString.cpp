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


//---------------------------------------------- CMyDataString ----------------------
IMPLEMENT_SERIAL(CMyDataString, CMyData,0)

CMyDataString::CMyDataString():CMyData()
{
}

void CMyDataString::RefreshData(CString str)
{
    if(m_strValue!=str)
    {
        m_strValue = str;
        IncrementUpdateID();
    }
}


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------



