//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef __CMYSCI_H
#define __CMYSCI_H

//---------------------------------------------- CMySCI ----------------------
class CMySCI:public CMyPort
{
public:
    DECLARE_SERIAL(CMySCI);
    CMySCI();
    ~CMySCI();

public:
    int m_nCom;                // Com¿Ú±àºÅ
    int m_nBaud;               // ²¨ÌØÂÊÐòºÅ

protected:
    HANDLE m_hFile;
//     CMyEnumSCI m_EnumSCI;

public:
    virtual BOOL OnAttrib(CBCGPPropertySheet& sheet);
    virtual void Serialize(CArchive& ar);
    virtual BOOL OpenCom(void);
    virtual void CloseCom(void);
    virtual void ClearCom(void);
    virtual int ReadCom(BYTE* pRXData,int nRXLength);
    virtual int WriteCom(BYTE* pTXData,int nTXLength);

};

extern const int g_cnBaud[12];

#endif/*__CMYSCI_H*/


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------

