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
#include "ModbusLib.h"
#include "CMyDlgUnitParam.h"

void RegisterClassModbusData(void)
{
//     CMyData::RegisterClass("DataMIS",RUNTIME_CLASS(CMyDataMIS));
//     CMyData::RegisterClass("DataCRCINFO",RUNTIME_CLASS(CMyDataCRCInfo));
//     CMyData::RegisterClass("DataMem",RUNTIME_CLASS(CMyDataMem));
}

//---------------------------------------------- CMyUnitModbus ----------------
IMPLEMENT_SERIAL(CMyUnitModbus, CMyUnit,0)

CMyUnitModbus::CMyUnitModbus():CMyUnit(), m_CRC16(0x8005,TRUE)
{
    m_nAddr = 1;			// 地址初始化
    m_nTimeout = 1000;
    m_ProtocolType = PROTOCOLTYPE_ModbusRTU;
}

void CMyUnitModbus::Serialize(CArchive& ar)
{
    CMyUnit::Serialize(ar);
    if(ar.IsStoring())
    {
        ar << m_nAddr;
        ar << m_nTimeout;
    }
    else
    {
        ar >> m_nAddr;
        ar >> m_nTimeout;
    }
}

BOOL CMyUnitModbus::OnAttrib(CBCGPPropertySheet& sheet)
{
    HINSTANCE hInstOld = AfxGetResourceHandle();
    AfxSetResourceHandle(MobusLibDLL.hModule);
    
    CMyDlgUnitParam pageNPS;
    pageNPS.m_nAddr = m_nAddr;
    pageNPS.m_nTimeout = m_nTimeout;
    sheet.AddPage(&pageNPS);
    
    if(CMyUnit::OnAttrib(sheet))
    {
        m_nAddr = pageNPS.m_nAddr;
        m_nTimeout = pageNPS.m_nTimeout;
        
        AfxSetResourceHandle(hInstOld);
        return TRUE;
    }
    
    AfxSetResourceHandle(hInstOld);
    
    return FALSE;
}

int CMyUnitModbus::ReadCom(COMCONTROL* pCC, BYTE* pRXData, int nRXLength)
{
    int nLenRcv = 0;
    DWORD dwTimeold = timeGetTime();
    DWORD dwTimeNow = dwTimeold;
    while((dwTimeNow - dwTimeold)<3000)
    {
        int nLenRcved = pCCPort->ReadCom(pRXData+nLenRcv, nRXLength-nLenRcv);
        nLenRcv += nLenRcved;
        Sleep(20);
        if(nLenRcv>=nRXLength) break;
        dwTimeNow = timeGetTime();
    }
    return nLenRcv;
}

BOOL CMyUnitModbus::MODBUS_Read(COMCONTROL* pCC,WORD wBaseAddress,WORD wCountWord, WORD* pData)
{
    switch(m_ProtocolType)
    {
    case PROTOCOLTYPE_ModbusRTU:
        {
            return MODBUS_ReadM(pCC, wBaseAddress, wCountWord, pData);
        }
        break;
    case PROTOCOLTYPE_ModbusTCP:
        {
            return MODBUS_ReadTCP(pCC, wBaseAddress, wCountWord, pData);
        }
        break;
    default: return FALSE;
    }
}

BOOL CMyUnitModbus::MODBUS_Write(COMCONTROL* pCC, WORD wBaseAddress, WORD wDataWrite)
{
    switch(m_ProtocolType)
    {
    case PROTOCOLTYPE_ModbusRTU:
        {
            return MODBUS_WriteM(pCC, wBaseAddress, 1, &wDataWrite);
        }
        break;
    case PROTOCOLTYPE_ModbusTCP:
        {
            return MODBUS_WriteTCP(pCC, wBaseAddress, 1, &wDataWrite);
        }
        break;
    default: return FALSE;
    }
}

BOOL CMyUnitModbus::MODBUS_Write(COMCONTROL* pCC, WORD wBaseAddress, WORD wCountWord, const WORD* pData)
{
    switch(m_ProtocolType)
    {
    case PROTOCOLTYPE_ModbusRTU:
        {
            return MODBUS_WriteM(pCC, wBaseAddress, wCountWord, pData);
        }
        break;
    case PROTOCOLTYPE_ModbusTCP:
        {
            return MODBUS_WriteTCP(pCC, wBaseAddress, wCountWord, pData);
        }
        break;
    default: return FALSE;
    }
}

BOOL CMyUnitModbus::MODBUS_ReadA(COMCONTROL* pCC, DWORD dwBaseAddress, WORD wCountWord, WORD* pData)
{
    switch(m_ProtocolType)
    {
    case PROTOCOLTYPE_ModbusRTU:
        {
            return MODBUS_ReadAM(pCC, dwBaseAddress, wCountWord, pData);
        }
        break;
    case PROTOCOLTYPE_ModbusTCP:
        {
            return MODBUS_ReadATCP(pCC, dwBaseAddress, wCountWord, pData);
        }
        break;
    default: return FALSE;
    }
}

BOOL CMyUnitModbus::MODBUS_ReadM(COMCONTROL* pCC, WORD wBaseAddress, WORD wCountWord, WORD* pData)
{
    BYTE* pTX = pCCTX;
    *pTX++ = BYTE(m_nAddr);
    *pTX++ = 0x03;
    *pTX++ = BYTE(wBaseAddress>>8);
    *pTX++ = BYTE(wBaseAddress&0xff);
    *pTX++ = BYTE(wCountWord>>8);
    *pTX++ = BYTE(wCountWord&0xff);
    WORD wCRC = 0xffff;
    m_CRC16.CalculateCRC(pCCTX,pTX-pCCTX,wCRC);
    *pTX++ = BYTE(wCRC&0xff);
    *pTX++ = BYTE(wCRC>>8);
    pCCPort->ClearCom();
    pCCPort->WriteCom(pCCTX,pTX-pCCTX);
    int nLength = wCountWord*2+((wCountWord<=125)?5:6);
    int nLengthRead = 0;

    m_pParentPort->m_bAutoSndMsg = FALSE;
    nLengthRead += ReadCom(pCC, pCCRX, 1);

    if(nLengthRead<2)
    {
        AddEvent(_T("通信超时!"));
        m_pParentPort->m_bAutoSndMsg = TRUE;
        return COMERR_Timeout;
    }
    if((pCCRX[1]&0x80)) nLength = 8;
    nLengthRead += ReadCom(pCC, pCCRX+2, nLength - 2);
    m_pParentPort->m_bAutoSndMsg = TRUE;
    m_pParentPort->AddComReportRX(pCCRX, nLengthRead);
    
    if(nLengthRead<nLength)
    {
        AddEvent(_T("通信超时!"));
        return COMERR_Timeout;
    }


    if(pCCRX[0]!=(BYTE)m_nAddr)
    {
        AddEvent(_T("通信地址出错!"));
        return COMERR_AddrErr;
    }

    if((pCCRX[1]&0x7f)!=0x03)
    {
        AddEvent(_T("功能码应答出错!"));
        return COMERR_FunErr; 
    }

    wCRC = 0xffff;
    m_CRC16.CalculateCRC(pCCRX, nLength, wCRC);
    if(wCRC!=0)
    {
        AddEvent(_T("校验和出错!"));
        return COMERR_CRCErr;
    }

    if(pCCRX[1]&0x80) return COMERR_Nodata;

    CopyByte2WORDHL(pCC, pData, wCountWord);

    return COMERR_NoErr;
}

BOOL CMyUnitModbus::MODBUS_WriteM(COMCONTROL* pCC, WORD wBaseAddress, WORD wCountWord, const WORD* pData)
{
    BYTE* pTX = pCCTX;
    *pTX++ = BYTE(m_nAddr);
    *pTX++ = 0x10;
    *pTX++ = BYTE(wBaseAddress>>8);
    *pTX++ = BYTE(wBaseAddress&0xff);
    *pTX++ = BYTE(wCountWord>>8);
    *pTX++ = BYTE(wCountWord&0xff);
    if(wCountWord<=125)
    {
        *pTX++ = BYTE(wCountWord*2);
    }
    else
    {
        *pTX++ = BYTE((wCountWord*2)&0xff);
        *pTX++ = BYTE((wCountWord*2)>>8);
    }
    for(WORD i=0;i<wCountWord;i++)
    {
        *pTX++ = *pData>>8;
        *pTX++ = *pData&0xff;
        pData++;
    }
    WORD wCRC = 0xffff;
    m_CRC16.CalculateCRC(pCCTX,pTX-pCCTX,wCRC);
    *pTX++ = BYTE(wCRC&0xff);
    *pTX++ = BYTE(wCRC>>8);
    pCCPort->ClearCom();
    pCCPort->WriteCom(pCCTX,pTX-pCCTX);
// 	Sleep(200);
    if(m_nAddr==0) return TRUE;
    if(pCCPort->ReadCom(pCCRX,8)<8)
    {
        AddEvent(_T("通信超时!"));
        return COMERR_Timeout;
    }

    if(pCCRX[0]!=(BYTE)m_nAddr)
    {
        AddEvent(_T("通信地址出错!"));
        return COMERR_AddrErr;
    }

    if((pCCRX[1]&0x7f)!=0x10)
    {
        AddEvent(_T("功能码应答出错!"));
        return COMERR_FunErr;
    }

    wCRC = 0xffff;
    m_CRC16.CalculateCRC(pCCRX, 8, wCRC);
    if(wCRC!=0)
    {
        AddEvent(_T("校验和出错!"));
        return COMERR_CRCErr;
    }
    return COMERR_NoErr;
}

BOOL CMyUnitModbus::MODBUS_WriteYK(COMCONTROL* pCC, WORD wBaseAddress)
{
    if(MODBUS_Write(pCC, wBaseAddress,0xaaaa)==FALSE) return FALSE;
    if(MODBUS_Write(pCC, wBaseAddress,0xaaaa)==FALSE) return FALSE;
    return TRUE;
}

BOOL CMyUnitModbus::MODBUS_ReadAM(COMCONTROL* pCC, DWORD dwBaseAddress, WORD wCountWord, WORD* pData)
{
    BYTE* pTX = pCCTX;
    *pTX++ = BYTE(m_nAddr);
    *pTX++ = 0x14;
    *pTX++ = BYTE(dwBaseAddress>>8);
    *pTX++ = BYTE(dwBaseAddress);
    *pTX++ = BYTE(dwBaseAddress>>24);
    *pTX++ = BYTE(dwBaseAddress>>16);
    *pTX++ = BYTE(wCountWord>>8);
    *pTX++ = BYTE(wCountWord&0xff);
    WORD wCRC = 0xffff;
    m_CRC16.CalculateCRC(pCCTX, pTX-pCCTX, wCRC);
    *pTX++ = BYTE(wCRC&0xff);
    *pTX++ = BYTE(wCRC>>8);
    pCCPort->ClearCom();
    pCCPort->WriteCom(pCCTX, pTX-pCCTX);
    // 	Sleep(100);
    int nLength = wCountWord*2+((wCountWord<=125)?5:6);
    int nLengthRead = 0;
    
    m_pParentPort->m_bAutoSndMsg = FALSE;
    nLengthRead += ReadCom(pCC, pCCRX, 2);
    if(nLengthRead<2)
    {
        AddEvent(_T("通信超时!"));
        m_pParentPort->m_bAutoSndMsg = TRUE;
        return COMERR_Timeout;
    }

    if((pCCRX[1]&0x80)) nLength = 8;
    nLengthRead += ReadCom(pCC, pCCRX+2, nLength - 2);
    m_pParentPort->m_bAutoSndMsg = TRUE;
    m_pParentPort->AddComReportRX(pCCRX, nLengthRead);
    
    if(nLengthRead<nLength)
    {
        AddEvent(_T("通信超时!"));
        return COMERR_Timeout;
    }

    if(pCCRX[0]!=(BYTE)m_nAddr)
    {
        AddEvent(_T("通信地址出错!"));
        return COMERR_AddrErr;
    }
    
    if((pCCRX[1]&0x7f)!=0x03)
    {
        AddEvent(_T("功能码应答出错!"));
        return COMERR_FunErr;
    }
    wCRC = 0xffff;
    wCRC = 0xffff;
    m_CRC16.CalculateCRC(pCCRX,nLength,wCRC);
    if(wCRC!=0)
    {
        AddEvent(_T("校验和出错!"));
        return COMERR_CRCErr;
    }
    
    if(pCCRX[1]&0x80) return COMERR_Nodata;
    CopyByte2WORDHL(pCC, pData, wCountWord);

    return COMERR_NoErr;
}

BOOL CMyUnitModbus::MODBUS_ReadTCP(COMCONTROL* pCC, WORD wBaseAddress, WORD wCountWord, WORD* pData)
{
    BYTE* pTX = pCCTX;
    *pTX++ = 0;			// byte 0: transaction identifier - copied by server - usually 0 
    *pTX++ = 0;			// byte 1: transaction identifier - copied by server - usually 0
    *pTX++ = 0;			// byte 2: protocol identifier = 0 
    *pTX++ = 0;			// byte 3: protocol identifier = 0
    *pTX++ = 0;			// byte 4: length field (upper byte) = 0 (since all messages are smaller than 256) 
    *pTX++ = 6;			// byte 5: length field (lower byte) = number of bytes following
    *pTX++ = BYTE(m_nAddr);
    *pTX++ = 0x03;
    *pTX++ = BYTE(wBaseAddress>>8);
    *pTX++ = BYTE(wBaseAddress&0xff);
    *pTX++ = BYTE(wCountWord>>8);
    *pTX++ = BYTE(wCountWord&0xff);
    pCCPort->ClearCom();
    pCCPort->WriteCom(pCCTX,pTX-pCCTX);
    // 	Sleep(100);
    int nLength = wCountWord*2+((wCountWord<=125)?9:10);
    int nLengthRead = 0;
    
    m_pParentPort->m_bAutoSndMsg = FALSE;
    nLengthRead += ReadCom(pCC, pCCRX, 2);
    if(nLengthRead<2)
    {
        AddEvent(_T("通信超时!"));
        m_pParentPort->m_bAutoSndMsg = TRUE;
        return COMERR_Timeout;
    }
    
    if((pCCRX[1]&0x80)) nLength = 8;
    nLengthRead += ReadCom(pCC, pCCRX+2, nLength - 2);
    m_pParentPort->m_bAutoSndMsg = TRUE;
    m_pParentPort->AddComReportRX(pCCRX, nLengthRead);

    if(nLengthRead<nLength)
    {
        AddEvent(_T("通信超时!"));
        return COMERR_Timeout;
    }
    
    if(pCCRX[6]!=(BYTE)m_nAddr)
    {
        AddEvent(_T("通信地址出错!"));
        return COMERR_AddrErr;
    }
    
    if(pCCRX[7]&0x7f!=0x03)
    {
        AddEvent(_T("功能码应答出错!"));
        return COMERR_FunErr;
    }

    if((pCCRX[4]*256+pCCRX[5])!=(nLength-6))
    {
        AddEvent(_T("数据长度不符!"));
        return COMERR_LenErr;
    }

    CopyByte2WORDHL(pCC, pData, wCountWord);

    return COMERR_NoErr;
}

BOOL CMyUnitModbus::MODBUS_ReadATCP(COMCONTROL* pCC,DWORD dwBaseAddress,WORD wCountWord, WORD* pData)
{
    BYTE* pTX = pCCTX;
    *pTX++ = 0;			// byte 0: transaction identifier - copied by server - usually 0 
    *pTX++ = 0;			// byte 1: transaction identifier - copied by server - usually 0
    *pTX++ = 0;			// byte 2: protocol identifier = 0 
    *pTX++ = 0;			// byte 3: protocol identifier = 0
    *pTX++ = 0;			// byte 4: length field (upper byte) = 0 (since all messages are smaller than 256) 
    *pTX++ = 8;			// byte 5: length field (lower byte) = number of bytes following
    *pTX++ = BYTE(m_nAddr);
    *pTX++ = 0x14;
    *pTX++ = BYTE(dwBaseAddress>>8);
    *pTX++ = BYTE(dwBaseAddress);
    *pTX++ = BYTE(dwBaseAddress>>24);
    *pTX++ = BYTE(dwBaseAddress>>16);
    *pTX++ = BYTE(wCountWord>>8);
    *pTX++ = BYTE(wCountWord&0xff);
    pCCPort->ClearCom();
    pCCPort->WriteCom(pCCTX,pTX-pCCTX);
    // 	Sleep(100);
    int nLength = wCountWord*2+((wCountWord<=125)?9:10);
    int nLengthRead = 0;
    
    m_pParentPort->m_bAutoSndMsg = FALSE;
    nLengthRead += ReadCom(pCC, pCCRX, 2);
    if(nLengthRead<2)
    {
        AddEvent(_T("通信超时!"));
        m_pParentPort->m_bAutoSndMsg = TRUE;
        return COMERR_Timeout;
    }

    if((pCCRX[1]&0x80)) nLength = 8;
    nLengthRead += ReadCom(pCC, pCCRX+2, nLength - 2);
    m_pParentPort->m_bAutoSndMsg = TRUE;
    m_pParentPort->AddComReportRX(pCCRX, nLengthRead);

    if(nLengthRead<nLength)
    {
        AddEvent(_T("通信超时!"));
        return COMERR_Timeout;
    }
    
    if(pCCRX[6]!=(BYTE)m_nAddr)
    {
        AddEvent(_T("通信地址出错!"));
        return COMERR_AddrErr;
    }
    
    if(pCCRX[7]&0x7f!=0x14)
    {
        AddEvent(_T("功能码应答出错!"));
        return COMERR_FunErr;
    }

    if((pCCRX[4]*256+pCCRX[5])!=(nLength-6))
    {
        AddEvent(_T("数据长度不符!"));
        return COMERR_LenErr;
    }
    
    CopyByte2WORDHL(pCC, pData, wCountWord);

    return COMERR_NoErr;
}

BOOL CMyUnitModbus::MODBUS_WriteTCP(COMCONTROL* pCC, WORD wBaseAddress, WORD wCountWord, const WORD* pData)
{
    BYTE* pTX = pCCTX;
    int nLen = wCountWord*2 + ((wCountWord<=125)?7:8);
    *pTX++ = 0;			// byte 0: transaction identifier - copied by server - usually 0 
    *pTX++ = 0;			// byte 1: transaction identifier - copied by server - usually 0
    *pTX++ = 0;			// byte 2: protocol identifier = 0 
    *pTX++ = 0;			// byte 3: protocol identifier = 0
    *pTX++ = nLen>>8;	// byte 4: length field (upper byte) = 0 (since all messages are smaller than 256) 
    *pTX++ = nLen;		// byte 5: length field (lower byte) = number of bytes following
    *pTX++ = BYTE(m_nAddr);
    *pTX++ = 0x10;
    *pTX++ = BYTE(wBaseAddress>>8);
    *pTX++ = BYTE(wBaseAddress&0xff);
    *pTX++ = BYTE(wCountWord>>8);
    *pTX++ = BYTE(wCountWord&0xff);
    if(wCountWord<=125)
    {
        *pTX++ = BYTE(wCountWord*2);
    }
    else
    {
        *pTX++ = BYTE((wCountWord*2)&0xff);
        *pTX++ = BYTE((wCountWord*2)>>8);
    }
    for(WORD i=0;i<wCountWord;i++)
    {
        *pTX++ = *pData>>8;
        *pTX++ = *pData&0xff;
        pData++;
    }
    pCCPort->ClearCom();
    pCCPort->WriteCom(pCCTX,pTX-pCCTX);
    Sleep(200);
    if(m_nAddr==0) return TRUE;
    if(ReadCom(pCC,pCCRX,12)<12)
    {
        AddEvent(_T("通信超时!"));
        return COMERR_Timeout;
    }
    
    if(pCCRX[6]!=(BYTE)m_nAddr)
    {
        AddEvent(_T("通信地址出错!"));
        return COMERR_AddrErr;
    }
    
    if(pCCRX[7]%0x7f!=0x10)
    {
        AddEvent(_T("功能码应答出错!"));
        return COMERR_FunErr;
    }
    
    if((pCCRX[4]*256+pCCRX[5])!=6)
    {
        AddEvent(_T("数据长度不符!"));
        return COMERR_LenErr;
    }
    return COMERR_NoErr;
}

void CMyUnitModbus::CopyByte2WORDHL(COMCONTROL* pCC, WORD* pwDest, WORD wWORDCount)
{
    BYTE* pRXSrc = pCCRX;
    switch(m_ProtocolType)
    {
    case PROTOCOLTYPE_ModbusRTU: break;
    case PROTOCOLTYPE_ModbusTCP: pRXSrc += 6; break;
    default: return;
    }
    pRXSrc = (wWORDCount<=125)?(pRXSrc+3):(pRXSrc+4);
    CopyByte2WORDHL(pwDest, pRXSrc, wWORDCount);
}

void CMyUnitModbus::CopyByte2WORDHL(WORD* pwDest, BYTE* pSrc, WORD wWORDCount)             // 先高后低
{
    for(int i=0;i<wWORDCount;i++)
    {
        int nByteIndex = i<<1;
        pwDest[i] = pSrc[nByteIndex+1] + (((WORD)pSrc[nByteIndex]<<8)&0xff00);
    }
}

// void CMyUnitModbus::CopyWORD2BYTEHL(BYTE* pDest, WORD* pwSrc, WORD wWORDCount)             // 先高后低
// {
//     for(int i=0;i<wWORDCount;i++)
//     {
//         int nByteIndex = i<<1;
//         pDest[nByteIndex] = (BYTE)(pwSrc[i]>>8);
//         pDest[nByteIndex+1] = (BYTE)pwSrc[i];
//     }
// }

void CMyUnitModbus::CopyStringToWSZ(WORD* pwszDest,CString strSrc)
{
    char* pszSrc = (char*)(const char*)strSrc;
    while(*pszSrc) *pwszDest++ = WORD(BYTE(*pszSrc++));
    *pwszDest = 0;
}

void CMyUnitModbus::CopyWSZToString(CString& strDest,WORD* pwszSrc)
{
    char szDest[200];
    char* pszDest = szDest;
    for(int i=0;i<199;i++)
    {
        if(*pwszSrc) *pszDest++ = char(*pwszSrc++);
        else break;
    }
    *pszDest = 0;
    strDest = szDest;
}

CString CMyUnitModbus::GetAllAnalogInfo(void)
{
    CString strUnitData = "";
    CString strTemp = "";

    int nSize = m_aFactory.GetSize();
    for(int i=0;i<nSize;++i)
    {
        CMyFactory* pFactory = m_aFactory[i];
        ASSERT(pFactory);
        CMyData* pData = pFactory->m_pData;
        if(pData)
        {
            CRuntimeClass* pRuntimeClass = pData->GetRuntimeClass();
            if(pRuntimeClass->IsDerivedFrom(RUNTIME_CLASS(CMyDataFloat)))
            {
                CMyDataFloat* pDataFloat = (CMyDataFloat*)pData;
                CString strVlue;
                CString strFormat;
                strFormat.Format(_T("%%.%df"), pDataFloat->m_Format&0xf);
                strVlue.Format(strFormat, pDataFloat->m_fData);
//                 strTemp.Format(_T("%s=%s %s;\t"), pDataFloat->m_strField, strVlue, pDataFloat->m_strUnitage);
                strTemp.Format(_T("%s=%s;\t"), pDataFloat->m_strField, strVlue);
                strUnitData += strTemp;
            }
        }
    }
    return strUnitData;
}


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------
