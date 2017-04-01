//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef __CMYDATAVIEWN_H
#define __CMYDATAVIEWN_H

//---------------------------------------------- CMyDataViewN ----------------------
class CMyDataViewN:public CMyDataView
{
public:
    DECLARE_SERIAL(CMyDataViewN);
    CMyDataViewN();
    ~CMyDataViewN();
    
public:
    virtual void OnViewData(void);

};

#endif/*__CMYDATAVIEWN_H*/


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------

