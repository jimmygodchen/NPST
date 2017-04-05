//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------
#ifndef _CMYUNITMODBUS_H
#define _CMYUNITMODBUS_H

enum COMERR
{
    COMERR_NoErr = 0,
    COMERR_Nodata,
    COMERR_Timeout,
    COMERR_AddrErr,
    COMERR_FunErr,
    COMERR_CRCErr,
    COMERR_LenErr,
};

enum PROTOCOLTYPE
{
    PROTOCOLTYPE_ModbusRTU = 0,
    PROTOCOLTYPE_ModbusTCP,
};

//---------------------------------------------- CMyUnitModbus ----------------
class CLASSMODBUS_EXPORT CMyUnitModbus:public CMyUnit
{
protected:
    DECLARE_SERIAL(CMyUnitModbus);
    CMyUnitModbus();

public:
    virtual BOOL OnAttrib(CBCGPPropertySheet& sheet);
    virtual void Serialize(CArchive& ar);

protected:
    int m_nAddr;
    int m_nTimeout;
    PROTOCOLTYPE m_ProtocolType;                // 协议类型0-Modbus;1-ModbusTCP;
    CMyCRC16 m_CRC16;

protected:      // Modbus
// Modbus和ModbusTCP通讯接口函数
    BOOL MODBUS_Read(COMCONTROL* pCC, WORD wBaseAddress, WORD wCountWord, WORD* pData);
    BOOL MODBUS_Write(COMCONTROL* pCC, WORD wBaseAddress, WORD wDataWrite);
    BOOL MODBUS_Write(COMCONTROL* pCC, WORD wBaseAddress, WORD wCountWord, const WORD* pData);
    BOOL MODBUS_WriteYK(COMCONTROL* pCC, WORD wBaseAddress);

    // 读取4字节地址数据
    BOOL MODBUS_ReadA(COMCONTROL* pCC, DWORD dwBaseAddress,WORD wCountWord, WORD* pData);
    
    // Modbus通讯函数
    BOOL MODBUS_ReadM(COMCONTROL* pCC, WORD wBaseAddress, WORD wCountWord, WORD* pData);
    BOOL MODBUS_WriteM(COMCONTROL* pCC, WORD wBaseAddress, WORD wCountWord, const WORD* pData);
    
    // 读取4字节地址数据
    BOOL MODBUS_ReadAM(COMCONTROL* pCC, DWORD dwBaseAddress,WORD wCountWord, WORD* pData);
    
    // ModbusTCP通讯函数
    BOOL MODBUS_ReadTCP(COMCONTROL* pCC, WORD wBaseAddress, WORD wCountWord, WORD* pData);
    BOOL MODBUS_WriteTCP(COMCONTROL* pCC, WORD wBaseAddress, WORD wCountWord, const WORD* pData);
    
    // 读取4字节地址数据
    BOOL MODBUS_ReadATCP(COMCONTROL* pCC, DWORD dwBaseAddress, WORD wCountWord, WORD* pData);

public:
    virtual int ReadCom(COMCONTROL* pCC, BYTE* pRXData, int nRXLength);
    CString GetAllAnalogInfo(void);

public:
    virtual void OnEditMem(const CMyDataMem& Mem){};
    virtual WORD GetDeviceTypeCode(void) { return 0; }
    void CopyByte2WORDHL(COMCONTROL* pCC, WORD* pwDest, WORD wWORDCount);             // 先高后低
//     void CopyWORD2BYTEHL(BYTE* pDest, WORD* pwSrc, WORD wWORDCount);             // 先高后低

public:
    static void CopyByte2WORDHL(WORD* pwDest, BYTE* pSrc, WORD wWORDCount);             // 先高后低
//     static void CopyWORD2BYTEHL(BYTE* pDest, WORD* pwSrc, WORD wWORDCount);             // 先高后低
    static void CopyStringToWSZ(WORD* pwszDest,CString strSrc);
    static void CopyWSZToString(CString& strDest,WORD* pwszSrc);
//     void WriteData(WORD wErrorCode,BYTE* Buff,WORD wLength,WORD wCnt=1);

};

#endif // _CMYUNITMODBUS_H


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------


