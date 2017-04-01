//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------


#ifndef __CMYUDP_H
#define __CMYUDP_H

typedef union MYIPADDRESS
{
    struct
    {
        BYTE Field0;
        BYTE Field1;
        BYTE Field2;
        BYTE Field3;
    }byteIPAddr;
    DWORD dwIPAddr;
}tIPADDRESS;

//---------------------------------------------- CMyUDP ----------------------
class CMyUDP:public CMyPort
{
public:
    DECLARE_SERIAL(CMyUDP);
    CMyUDP();
    ~CMyUDP();

public:
    DWORD m_dwIPSrc;
    DWORD m_dwIPDest;
    int m_nPortSrc;
    int m_nPortDest;

protected:
    SOCKET m_hSocket;
    struct sockaddr_in m_sadSrc;
    struct sockaddr_in m_sadDest;
    BYTE m_RxData[16384];
    int m_nRxLen;

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

#endif/*__CMYUDP_H*/

//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------



