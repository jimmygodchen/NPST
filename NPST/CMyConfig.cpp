//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "CMyConfig.h"

//---------------------------------------------- CMyConfig -----------------------
CMyConfig::CMyConfig(CString strName):CMyObj()
{
    m_strName = strName;
}

void CMyConfig::Serialize(CArchive& ar)
{
    CMyObj::Serialize(ar);
    if(ar.IsStoring())
    {
        ar << m_strPortName;
        ar << m_strUnitName;
    }
    else
    {
        ar >> m_strPortName;
        ar >> m_strUnitName;
    }
}

//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------



