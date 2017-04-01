//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef __CMYDATAVECTOR_H
#define __CMYDATAVECTOR_H

//---------------------------------------------- CMyDataVector -----------------
class CLASS_EXPORT CMyDataVector:public CMyDataFloat
{
public:
    DECLARE_SERIAL(CMyDataVector);
    CMyDataVector();

public:
//     CString m_strUnitage;           // ���ݵ�λ(��"kV","kA","Hz"��);
//     BYTE m_Format;                  // ���ݸ�ʽ(��0:"%.0f",2:"%.2f"��);
//     float m_fData;                  // ��ǰ����ֵ;
    CMyVector m_vec;
    int m_nDisplayType;                 // ��ʾ��ʽ: 0 - R+jX, 1 - A��
    BYTE m_AngFormat;

public:
    virtual void Initialize(CString strName, CString strUnitage, BYTE Format, BYTE AngFormat = 0, int nDisplayType = 0);

public:
    virtual void RefreshData(CMyVector Vec);
};

#endif/*__CMYDATAVECTOR_H*/


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------

