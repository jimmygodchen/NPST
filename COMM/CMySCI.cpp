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
#include "CMySCI.h"
#include "CMyPortSCIDlg.h"

extern AFX_EXTENSION_MODULE COMMDLL;

const int g_cnBaud[12] = { 300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 43000, 56000, 57600, 115200 };

//---------------------------------------------- CMySCI -----------------------
IMPLEMENT_SERIAL(CMySCI,CMyPort,0)

CMySCI::CMySCI():CMyPort()
{
    m_nCom = 0;                // Com1
    m_nBaud = 5;               // 9600
    m_hFile = (HANDLE)-1;
    CMyEnumSCI::EnumSCI();
}

CMySCI::~CMySCI()
{
}


BOOL CMySCI::OnAttrib(CBCGPPropertySheet& sheet)
{
    HINSTANCE hInstOld = AfxGetResourceHandle();
    AfxSetResourceHandle(COMMDLL.hModule);

    CMyPortSCIDlg pageSCI;
//     pageSCI.m_pEnumSCI = &m_EnumSCI;
    pageSCI.m_nCom = m_nCom;
    pageSCI.m_nBaud = m_nBaud;

    sheet.AddPage(&pageSCI);

    if(CMyPort::OnAttrib(sheet))
    {
        m_nCom = pageSCI.m_nCom;
        m_nBaud = pageSCI.m_nBaud;

        AfxSetResourceHandle(hInstOld);
        return TRUE;
    }

    AfxSetResourceHandle(hInstOld);

    return FALSE;
}

void CMySCI::Serialize(CArchive& ar)
{
    CMyPort::Serialize(ar);
    if(ar.IsStoring())
    {
        ar << m_nCom;
        ar << m_nBaud;
    }
    else
    {
        ar >> m_nCom;
        ar >> m_nBaud;
    }
}

BOOL CMySCI::OpenCom(void)
{
    int nSize = CMyEnumSCI::m_arCOM.GetSize();
    if(nSize==0) return FALSE;

    CString strCom = _T("//./") + CMyEnumSCI::m_arCOM[m_nCom];

    m_hFile = CreateFile(strCom,									// (g_nCommMode==1)?"COM1":"COM2",
        GENERIC_READ | GENERIC_WRITE,
        0,                    // exclusive access
        NULL,                 // no security attrs
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL );
    if(m_hFile==(HANDLE)-1) return FALSE;
    
    SetLastError(0);
    
    DCB dcb;
    dcb.DCBlength = sizeof(DCB);
    GetCommState(m_hFile,&dcb);

    nSize = sizeof(g_cnBaud)/sizeof(int);
    int nBaud = 9600;
    if(m_nBaud>=0 && m_nBaud<nSize)
    {
        nBaud = g_cnBaud[m_nBaud];
    }

    dcb.BaudRate = nBaud;
    dcb.ByteSize = 8;
    dcb.Parity = NOPARITY;
    dcb.StopBits = ONESTOPBIT;
    dcb.fOutxDsrFlow = FALSE;
    dcb.fDtrControl = DTR_CONTROL_ENABLE;
    dcb.fOutxCtsFlow = FALSE;
    dcb.fRtsControl = RTS_CONTROL_ENABLE;
    dcb.fInX = FALSE;
    dcb.fOutX = FALSE;
    dcb.XonChar = 0x11;
    dcb.XoffChar = 0x13;
    dcb.XonLim = 100;
    dcb.XoffLim = 100;
    dcb.fBinary = TRUE;
    dcb.fParity = TRUE;
    SetCommState(m_hFile,&dcb);
    COMMTIMEOUTS CommTimeOuts;
    CommTimeOuts.ReadIntervalTimeout = 1000;
    CommTimeOuts.ReadTotalTimeoutMultiplier = 12000/dcb.BaudRate + 1;
    CommTimeOuts.ReadTotalTimeoutConstant = 2000;
    CommTimeOuts.WriteTotalTimeoutMultiplier = 12000/dcb.BaudRate + 1;
    CommTimeOuts.WriteTotalTimeoutConstant = 1000;
    
    SetCommTimeouts(m_hFile,&CommTimeOuts);
    
    SetupComm(m_hFile,2048,2048);
    
    PurgeComm(m_hFile,PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);
    
    EscapeCommFunction(m_hFile,SETDTR);
    
    return TRUE;
}

void CMySCI::CloseCom(void)
{
    if(m_hFile==(HANDLE)-1) return;
    EscapeCommFunction(m_hFile,CLRDTR);
    PurgeComm(m_hFile,PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);
    CloseHandle(m_hFile);
}

void CMySCI::ClearCom(void)
{
    if(m_hFile==(HANDLE)-1) return;
    PurgeComm(m_hFile,PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);
}

int CMySCI::ReadCom(BYTE* pRXData,int nRXLength)
{
    if(m_hFile==(HANDLE)-1) return 0;
    if(nRXLength==0) return 0;
    
    SetLastError(0);
    DWORD dwLength = 0;
    if(ReadFile(m_hFile,pRXData,nRXLength,&dwLength,NULL)==FALSE) return 0;
    AddComReportRX(pRXData, dwLength);
    return (int)dwLength;
}

int CMySCI::WriteCom(BYTE* pTXData,int nTXLength)
{
    if(m_hFile==(HANDLE)-1) return 0;
    if(nTXLength==0) return 0;

    SetLastError(0);
    DWORD dwLength = 0;
    if(WriteFile(m_hFile,pTXData,nTXLength,&dwLength,NULL)==FALSE) return 0;
    else if(FlushFileBuffers(m_hFile)==FALSE) return 0;
    AddComReportTX(pTXData, dwLength);
    return (int)dwLength;
}


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------



