//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef __CMYDATAFLOAT_H
#define __CMYDATAFLOAT_H

//---------------------------------------------- CMyDataFloat -----------------
class CLASS_EXPORT CMyDataFloat:public CMyData
{
public:
    DECLARE_SERIAL(CMyDataFloat);
    CMyDataFloat();

public:
    CString m_strUnitage;           // ���ݵ�λ(��"kV","kA","Hz"��);
    BYTE m_Format;                  // ���ݸ�ʽ(��0:"%.0f",2:"%.2f"��);
    float m_fData;                  // ��ǰ����ֵ;

public:
    virtual void Initialize(CString strName, CString strUnitage, BYTE Format);

public:
    virtual void RefreshData(float fData);

};

#endif/*__CMYDATAFLOAT_H*/


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------

