//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef __CMYCONFIG_H
#define __CMYCONFIG_H

//---------------------------------------------- CMyConfig -----------------------
class CMyConfig:public CMyObj
{
public:
    CMyConfig(CString strName);

public:
    CString m_strPortName;
    CString m_strUnitName;

public:
    virtual void Serialize(CArchive& ar);
};

#endif/*__CMYCONFIG_H*/


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------

