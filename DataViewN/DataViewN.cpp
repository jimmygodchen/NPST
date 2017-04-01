// DataViewN.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>
#include "DataViewN.h"
#include "CMyDlgDataView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static AFX_EXTENSION_MODULE DataViewNDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("DATAVIEWN.DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(DataViewNDLL, hInstance))
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

		new CDynLinkLibrary(DataViewNDLL);
        CMyDataView::RegisterClass(RUNTIME_CLASS(CMyDataViewN));

//         globalData.SetDPIAware ();
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
//         BCGCBProCleanUp();
		TRACE0("DATAVIEWN.DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(DataViewNDLL);
	}
	return 1;   // ok
}


//---------------------------------------------- CMyDataViewN -----------------------
IMPLEMENT_SERIAL(CMyDataViewN,CMyDataView,0)

CMyDataViewN::CMyDataViewN():CMyDataView()
{
}

CMyDataViewN::~CMyDataViewN()
{
}

void CMyDataViewN::OnViewData(void)
{
    HINSTANCE hInstOld = AfxGetResourceHandle();
    AfxSetResourceHandle(DataViewNDLL.hModule);

    CMyDlgDataView dlg;

    dlg.DoModal();

    AfxSetResourceHandle(hInstOld);
}
