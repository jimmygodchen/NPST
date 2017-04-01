// Public.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>
#include "Pub.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/*static*/ AFX_EXTENSION_MODULE PublicDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    // Remove this if you use lpReserved
    UNREFERENCED_PARAMETER(lpReserved);

    if (dwReason == DLL_PROCESS_ATTACH)
    {
        TRACE0("PUBLIC.DLL Initializing!\n");

        // Extension DLL one-time initialization
        if (!AfxInitExtensionModule(PublicDLL, hInstance))
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

        new CDynLinkLibrary(PublicDLL);
//         CMyPort::RegisterClass(_T("�ն˿�"), RUNTIME_CLASS(CMyPort));
        CMyData::RegisterClass("��ֵ��",RUNTIME_CLASS(CMyDataFloat),TRUE);
        CMyData::RegisterClass("����",RUNTIME_CLASS(CMyDataVector),TRUE);
        CMyData::RegisterClass("������",RUNTIME_CLASS(CMyDataBin),TRUE);
        CMyData::RegisterClass("�ַ�",RUNTIME_CLASS(CMyDataString),TRUE);
        CMyData::RegisterClass("һ�����",RUNTIME_CLASS(CMyDataOperate),TRUE);
        CMyData::RegisterClass("�ڴ����",RUNTIME_CLASS(CMyDataMem),TRUE);
        CMyData::RegisterClass("ʵʱ����",RUNTIME_CLASS(CMyRTWave),TRUE);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
        TRACE0("PUBLIC.DLL Terminating!\n");
        // Terminate the library before destructors are called
        AfxTermExtensionModule(PublicDLL);
    }
    return 1;   // ok
}
