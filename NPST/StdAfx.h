// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__4EFB307C_C249_440B_B298_F9C150B2BA5A__INCLUDED_)
#define AFX_STDAFX_H__4EFB307C_C249_440B_B298_F9C150B2BA5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxadv.h>
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxrich.h>		// MFC rich edit classes


// #define COMM_BUFFERSIZE				5120
// #include <WINSOCK2.H>
#include <BCGCBProInc.h>			// BCGControlBar Pro
#include "Pub.h"
// #include "Comm.h"

// typedef struct _PORTINFO
// {
// 	int nComMode;					// ͨѶ��ʽ:0-COM;1-UDP;2-TCPIPServer;3-TCPIPClient
// 	int nComBaud;					// ���ڲ�����
// 	int nComPort;					// ���ں�
// 	DWORD dwCommIPSrc;				// UDPԴ��ַ
// 	DWORD dwCommIPDest;				// UDPĿ�ĵ�ַ
// 	int nCommPortSrc;				// UDPԴ�˿�
// 	int nCommPortDest;				// UDPĿ�Ķ˿�
// 	DWORD dwTCPIPServer;			// TCPIPServer��������ַ
// 	DWORD dwTCPIPClient;			// TCPIPClient��������ַ
// 	int nPortTCPIPServer;			// TCPIPServer�������˿�
// 	int nPortTCPIPClient;			// TCPIPClientĿ��˿�
// }PortInfo;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__4EFB307C_C249_440B_B298_F9C150B2BA5A__INCLUDED_)
