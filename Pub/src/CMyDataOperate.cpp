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

//---------------------------------------------- CMyDataOperate ---------------
IMPLEMENT_SERIAL(CMyDataOperate,CMyData,0)

CMyDataOperate::CMyDataOperate():CMyData()
{
    m_OperateCode = 0;
}

BOOL CMyDataOperate::ExeOperate(void)
{
    if(MyMessageBox(" «∑Ò÷¥––"+GetFullName()+"?","«Î—°‘Ò",MB_YESNO|MB_ICONQUESTION)==IDYES)
    {
        m_OperateCode = 0xff;
        IncrementUpdateID();
        return TRUE;
    }
    return FALSE;
}

void CMyDataOperate::EndOperate(void)
{
    m_OperateCode = 0;
    IncrementUpdateID();
}

void CMyDataOperate::SetOperateCode(BYTE OperateCode)
{
    m_OperateCode = OperateCode;
    IncrementUpdateID();
}

//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------



