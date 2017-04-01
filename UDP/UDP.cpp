// UDP.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>
#include "UDP.h"
#include "CMyUDPDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static AFX_EXTENSION_MODULE UDPDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("UDP.DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(UDPDLL, hInstance))
			return 0;

		// Insert this DLL into the resource chain
		// NOTE: If this Extension DLL is being implicitly linked to by
		//  an MFC Regular DLL (such as an ActiveX Control)
		//  instead of an MFC application, then you will want to
		//  remove this line from DllMain and put it in a separate
		//  function exported from this Extension DLL.  The Regular DLL
		//  that uses this Extension DLL should then explicitly call that
		//  function to initialize this Extension DLL.  Otherwise,
		//  the CDynLinkLibrary object will not be attached to the
		//  Regular DLL's resource chain, and serious problems will
		//  result.

		new CDynLinkLibrary(UDPDLL);
        CMyPort::RegisterClass(_T("UDP"), RUNTIME_CLASS(CMyUDP));
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("UDP.DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(UDPDLL);
	}
	return 1;   // ok
}


//---------------------------------------------- CMySCI -----------------------
IMPLEMENT_SERIAL(CMyUDP,CMyPort,0)

CMyUDP::CMyUDP():CMyPort()
{
    m_dwIPSrc = 0x0100007f;
    m_dwIPDest = 0x0100007f;
    m_nPortSrc = 5000;
    m_nPortDest = 5001;
    m_hSocket = INVALID_SOCKET;
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2),&wsaData);
}

CMyUDP::~CMyUDP()
{
    WSACleanup();
}

BOOL CMyUDP::OnAttrib(CBCGPPropertySheet& sheet)
{
    HINSTANCE hInstOld = AfxGetResourceHandle();
    AfxSetResourceHandle(UDPDLL.hModule);

    CMyUDPDlg pageUDP;
    pageUDP.m_nPortSrc = m_nPortSrc;
    pageUDP.m_nPortDest = m_nPortDest;
    pageUDP.m_dwIPSrc = m_dwIPSrc;
    pageUDP.m_dwIPDest = m_dwIPDest;

    sheet.AddPage(&pageUDP);

    if(CMyPort::OnAttrib(sheet))
    {
        m_nPortSrc = pageUDP.m_nPortSrc;
        m_nPortDest = pageUDP.m_nPortDest;
        m_dwIPSrc = pageUDP.m_dwIPSrc;
        m_dwIPDest = pageUDP.m_dwIPDest;

        AfxSetResourceHandle(hInstOld);
        return TRUE;
    }

    AfxSetResourceHandle(hInstOld);

    return FALSE;
}

void CMyUDP::Serialize(CArchive& ar)
{
    CMyPort::Serialize(ar);
    if(ar.IsStoring())
    {
        ar << m_dwIPSrc;
        ar << m_dwIPDest;
        ar << m_nPortSrc;
        ar << m_nPortDest;
    }
    else
    {
        ar >> m_dwIPSrc;
        ar >> m_dwIPDest;
        ar >> m_nPortSrc;
        ar >> m_nPortDest;
    }
}

BOOL CMyUDP::OpenCom(void)
{
    if(m_hSocket!=INVALID_SOCKET) return FALSE;
    m_nRxLen = 0;
    memset((char*)&m_sadSrc,0,sizeof(m_sadSrc));
    memset((char*)&m_sadDest,0,sizeof(m_sadDest));
    
    struct protoent* pProto = getprotobyname("udp");
    if(pProto==NULL) return FALSE;
    m_hSocket = socket(AF_INET,SOCK_DGRAM,pProto->p_proto);
    if(m_hSocket==INVALID_SOCKET) return FALSE;
    
    m_sadSrc.sin_family = AF_INET;
    m_sadSrc.sin_port = htons(m_nPortSrc);
    unsigned long ulSrcIP = m_dwIPSrc;
    memcpy(&m_sadSrc.sin_addr,&ulSrcIP,4);
    
    m_sadDest.sin_family = AF_INET;
    m_sadDest.sin_port = htons(m_nPortDest);
    unsigned long ulDestIP = m_dwIPDest;
    memcpy(&m_sadDest.sin_addr,&ulDestIP,4);
    
    int nResult = bind(m_hSocket,(struct sockaddr*)&m_sadSrc,sizeof(m_sadSrc));
    if(nResult==SOCKET_ERROR)
    {
        CloseCom();
        return FALSE;
    }
    else
    {
        DWORD cbInQue = 1;
        ioctlsocket(m_hSocket,FIONBIO,&cbInQue);
    }
    return TRUE;
}

void CMyUDP::CloseCom(void)
{
    if(m_hSocket!=INVALID_SOCKET) closesocket(m_hSocket);
    m_nRxLen = 0;
}

void CMyUDP::ClearCom(void)
{
    m_nRxLen = 0;
}

int CMyUDP::ReadCom(BYTE* pRXData,int nRXLength)
{
    if(m_hSocket==INVALID_SOCKET) return 0;
    if(nRXLength==0) return 0;
    
    for(int i=0;i<100;i++)
    {
        if(m_nRxLen<16384)
        {
            WSASetLastError(0);
            int nFromLen = sizeof(m_sadSrc);
            int nResult = recvfrom(m_hSocket,(char*)(m_RxData+m_nRxLen),16384-m_nRxLen,0,(struct sockaddr*)&m_sadSrc,&nFromLen);
            if(nResult==SOCKET_ERROR)
            {
                DWORD dwErrorNo = WSAGetLastError();
                nResult = 0;
                if(dwErrorNo!=0 && dwErrorNo!=WSAEWOULDBLOCK)
                {
                    break;
                }
            }
            else
            {
                m_nRxLen += nResult;
            }
        }
        if(m_nRxLen>=nRXLength) break;
        Sleep(10);
    }
    int nCountAdd = min(nRXLength,m_nRxLen);
    if(nCountAdd)
    {
        memcpy(pRXData, m_RxData, nCountAdd);
        AddComReportRX(pRXData, nCountAdd);
        m_nRxLen -= nCountAdd;
        if(m_nRxLen>0) memmove(m_RxData,m_RxData+nCountAdd,m_nRxLen);
    }

    return (int)nCountAdd;
}

int CMyUDP::WriteCom(BYTE* pTXData,int nTXLength)
{
    if(m_hSocket==INVALID_SOCKET) return 0;
    if(nTXLength==0) return 0;
    
    int nLength = 0;
    for(int i=0;i<20;i++)
    {
        Sleep(10);
        WSASetLastError(0);
        int nResult = sendto(m_hSocket,(char*)(pTXData+nLength),nTXLength,0,(struct sockaddr*)&m_sadDest,sizeof(m_sadDest));
        if(nResult==SOCKET_ERROR)
        {
            DWORD dwErrorNo = WSAGetLastError();
            if(dwErrorNo!=0 && dwErrorNo!=WSAEWOULDBLOCK)
            {
                break;
            }
        }
        else
        {
            nTXLength -= nResult;
            nLength += nResult;
            if(nTXLength<=0) break;
        }
    }
    AddComReportTX(pTXData, nLength);
    return nLength;
}
