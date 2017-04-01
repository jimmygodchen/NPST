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

//---------------------------------------------- CMyDataView Static ---------------
CPtrArray CMyDataView::s_aClass;

void CMyDataView::RegisterClass(CRuntimeClass* pRuntimeClass)
{
    int nSize = s_aClass.GetSize();
    if(nSize>0) return;

    if(pRuntimeClass->IsDerivedFrom(RUNTIME_CLASS(CMyDataView)))
    {
        s_aClass.Add(pRuntimeClass);
    }
}

//---------------------------------------------- CMyDataView -----------------------
IMPLEMENT_SERIAL(CMyDataView,CMyObj,0)

CMyDataView::CMyDataView():CMyObj()
{
}

CMyDataView::~CMyDataView()
{
}

//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------



