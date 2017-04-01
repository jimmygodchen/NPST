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
#include "Pub.h"

CString g_strSysPath = _T("");
CFileStatusArray g_aDllInfo;

CMyPortMng g_MngPort;
CMyDataView* g_pDataView = NULL;
CMyEventMng g_MngEvent;
CMyMapDeviceTypeArray g_aMapDeviceType;

//---------------------------------------------- CMyObj -----------------------
void MySystemCreate(void)
{
//     CString strCommandLine = ::GetCommandLine();
//     strCommandLine.MakeUpper();
//     strCommandLine.Replace("\"","");
//     int nFind = strCommandLine.Find("BIN");
//     if(nFind!=-1) g_strSysPath = strCommandLine.Mid(0,nFind-1);

    CString strPath;
    GetModuleFileName(NULL,strPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
    strPath.ReleaseBuffer();
    int pos = strPath.ReverseFind('\\');
    g_strSysPath = strPath.Left(pos);

    _mkdir(g_strSysPath + _T("\\Temp"));
    _mkdir(g_strSysPath + _T("\\Wave"));

    MyLoadDllInfo();
    MyLoadAllLibrary();
    InitMapDeviceType();

    int nSize = CMyDataView::s_aClass.GetSize();
    if(nSize)
    {
        CRuntimeClass* pRuntimeClass = (CRuntimeClass*)CMyDataView::s_aClass[0];

        ASSERT(pRuntimeClass->IsDerivedFrom(RUNTIME_CLASS(CMyDataView)));
        g_pDataView = (CMyDataView*)(pRuntimeClass->CreateObject());
    }
}

void MySystemDestroy(void)
{
    if(g_pDataView)
    {
        delete g_pDataView;
        g_pDataView = NULL;
    }

    MyFreeAllLibrary();
}

int MyDoModal(CDialog* pDlg,HINSTANCE hInstance)
{
    HINSTANCE hInstOld = AfxGetResourceHandle();
    AfxSetResourceHandle(hInstance);
    HWND hWndFocus = ::GetFocus();
    int nReturn = pDlg->DoModal();
    ::SetFocus(hWndFocus);
    AfxSetResourceHandle(hInstOld);
    return nReturn;
}

int MyMessageBox(CString strMessage,CString strTitle,UINT uType)
{
    static BOOL s_bMessageBox = FALSE;
    int nResult = 0;
    if(!s_bMessageBox)
    {
        s_bMessageBox = TRUE;
        HWND hWndFocus = ::GetFocus();
        CWnd* pMainFrame = AfxGetMainWnd();
        if(pMainFrame && ::IsWindow(pMainFrame->m_hWnd)) nResult = pMainFrame->MessageBox(strMessage,strTitle,uType);
        else nResult = ::MessageBox(NULL,strMessage,strTitle,uType);
        if(::IsWindow(hWndFocus)) ::SetFocus(hWndFocus);
        s_bMessageBox = FALSE;
    }
    return nResult;
}

CString MyReverseSpanExcluding(CString strSource,CString strSpan)
{
    strSource.MakeReverse();
    strSource = strSource.SpanExcluding(strSpan);
    strSource.MakeReverse();
    return strSource;
}

void MyAbortSystem(CString strMessage)
{
    if(!strMessage.IsEmpty()) MyMessageBox(strMessage,"出错",MB_OK|MB_ICONSTOP);
    ::ExitProcess(1);
//     PostQuitMessage(0);
}

void MyLoadDllInfo(void)
{
    g_aDllInfo.RemoveAll();
    CFileStatus fileStatus;
    if(CFile::GetStatus(g_strSysPath + _T("\\Public.dll"),fileStatus)) g_aDllInfo.Add(fileStatus);
    else
    {
        MyAbortSystem("共享库文件Public.dll丢失！");
        return;
    }
    CStdioFile file;
    if(file.Open(g_strSysPath + "\\dll.cfg", CFile::modeRead|CFile::shareDenyNone))
    {
        char szDllFile[_MAX_PATH+1];
        while(file.ReadString(szDllFile,_MAX_PATH)!=NULL)
        {
            CString strDllFile = strtok(szDllFile,"\n");
            strDllFile.TrimLeft();
            strDllFile.TrimRight();
            if(strDllFile.IsEmpty()) continue;
            if(strDllFile.Find("///")==0) break;
            if(strDllFile.Find("//")==0) continue;
            if(CFile::GetStatus(g_strSysPath + _T("\\") + strDllFile, fileStatus)) g_aDllInfo.Add(fileStatus);
        }
    }
}

static CPtrArray s_aInstances;
void MyLoadAllLibrary(void)
{
    ASSERT(s_aInstances.GetSize()==0);
    int nSize = g_aDllInfo.GetSize();
    for(int i=0;i<nSize;i++)
    {
        CString strDllFile = g_aDllInfo[i].m_szFullName;
        HINSTANCE hInstance = AfxLoadLibrary(strDllFile);
        if(hInstance!=NULL) s_aInstances.Add(hInstance);
        else
        {
            CString strMessage;
            strMessage += "动态连接库文件";
            strMessage += strDllFile;
            strMessage += "无法装入!";
            strMessage += "\n是否跳过该文件继续执行?";
            if(MyMessageBox(strMessage,"请注意",MB_YESNO|MB_ICONWARNING)==IDYES) continue;
            MyAbortSystem("");
            return;
        }
    }
}

void MyFreeAllLibrary(void)
{
    int nSize = s_aInstances.GetSize();
    for(int i=0;i<nSize;i++) AfxFreeLibrary((HINSTANCE)(s_aInstances[i]));
    s_aInstances.RemoveAll();
}

void InitMapDeviceType(void)
{
    CStdioFile file;
    if(file.Open(g_strSysPath + _T("\\DEV.ini"), CFile::modeRead|CFile::shareDenyNone))
    {
        char szLine[256], szDeviceType[256], szOEMType[256];
        while(file.ReadString(szLine,255)!=NULL)
        {
            tMAPDEVICETYPE Map;
            int nSize = sscanf(szLine,_T("%[^,],%[^,]\n"), szDeviceType, szOEMType);
            if(nSize>=2)
            {
                Map.strDeviceType = szDeviceType;
                Map.strOEMType = szOEMType;
                Map.strDeviceType.TrimLeft();
                Map.strDeviceType.TrimRight();
                Map.strOEMType.TrimLeft();
                Map.strOEMType.TrimRight();
                g_aMapDeviceType.Add(Map);
            }
        }
    }
}

BOOL DeviceType2OEMType(CString strDeviceType, CString& strOEMType)
{
    int nSize = g_aMapDeviceType.GetSize();
    for(int i=0;i<nSize;++i)
    {
        if(g_aMapDeviceType[i].strDeviceType==strDeviceType)
        {
            strOEMType = g_aMapDeviceType[i].strOEMType;
            return TRUE;
        }
    }
    return FALSE;
}

//---------------------------------------------- CMyCRC8 ----------------------
CMyCRC8::CMyCRC8(BYTE Poly,BOOL bInvert)
{
	m_bInvert = bInvert;
	if(m_bInvert)
	{
		BYTE PolyInvert = 0;
		if(Poly&0x01) PolyInvert |= 0x80;
		if(Poly&0x02) PolyInvert |= 0x40;
		if(Poly&0x04) PolyInvert |= 0x20;
		if(Poly&0x08) PolyInvert |= 0x10;
		if(Poly&0x10) PolyInvert |= 0x08;
		if(Poly&0x20) PolyInvert |= 0x04;
		if(Poly&0x40) PolyInvert |= 0x02;
		if(Poly&0x80) PolyInvert |= 0x01;
		Poly = PolyInvert;
	}
	for(int i=0;i<256;i++)
	{
		BYTE Data = (BYTE)i;
		BYTE Accum = 0;
		if(m_bInvert)
		{
			for(int j=0;j<8;j++)
			{
				if((Data^Accum)&0x01) Accum = (Accum>>1)^Poly;
				else Accum >>= 1;
				Data >>= 1;
			}
		}
		else
		{
			for(int j=0;j<8;j++)
			{
				if((Data^Accum)&0x80) Accum = (Accum<<1)^Poly;
				else Accum <<= 1;
				Data <<= 1;
			}
		}
		m_Table[i] = Accum;
	}
}

void CMyCRC8::CalculateCRC(BYTE* pData,int nLength,BYTE& CRC)
{
	BYTE* pStop = pData + nLength;
	while(pData<pStop) CRC = m_Table[(CRC^*pData++)];
}


//---------------------------------------------- CMyCRC16 ---------------------
CMyCRC16::CMyCRC16(WORD wPoly,BOOL bInvert)
{
	m_bInvert = bInvert;
	if(m_bInvert)
	{
		WORD wPolyInvert = 0;
		if(wPoly&0x0001) wPolyInvert |= 0x8000;
		if(wPoly&0x0002) wPolyInvert |= 0x4000;
		if(wPoly&0x0004) wPolyInvert |= 0x2000;
		if(wPoly&0x0008) wPolyInvert |= 0x1000;
		if(wPoly&0x0010) wPolyInvert |= 0x0800;
		if(wPoly&0x0020) wPolyInvert |= 0x0400;
		if(wPoly&0x0040) wPolyInvert |= 0x0200;
		if(wPoly&0x0080) wPolyInvert |= 0x0100;
		if(wPoly&0x0100) wPolyInvert |= 0x0080;
		if(wPoly&0x0200) wPolyInvert |= 0x0040;
		if(wPoly&0x0400) wPolyInvert |= 0x0020;
		if(wPoly&0x0800) wPolyInvert |= 0x0010;
		if(wPoly&0x1000) wPolyInvert |= 0x0008;
		if(wPoly&0x2000) wPolyInvert |= 0x0004;
		if(wPoly&0x4000) wPolyInvert |= 0x0002;
		if(wPoly&0x8000) wPolyInvert |= 0x0001;
		wPoly = wPolyInvert;
	}
	for(int i=0;i<256;i++)
	{
		BYTE Data = (BYTE)i;
		WORD wAccum = 0;
		if(m_bInvert)
		{
			for(int j=0;j<8;j++)
			{
				if((Data^wAccum)&0x0001) wAccum = (wAccum>>1)^wPoly;
				else wAccum >>= 1;
				Data >>= 1;
			}
		}
		else
		{
			for(int j=0;j<8;j++)
			{
				if((Data^wAccum)&0x8000) wAccum = (wAccum<<1)^wPoly;
				else wAccum <<= 1;
				Data <<= 1;
			}
		}
		m_wTable[i] = wAccum;
	}
}

void CMyCRC16::CalculateCRC(BYTE* pData,int nLength,WORD& wCRC)
{
	BYTE* pStop = pData + nLength;
	if(m_bInvert)
	{
		while(pData<pStop) wCRC = (wCRC>>8)^m_wTable[(wCRC^*pData++)&0x00ff];
	}
	else
	{
		while(pData<pStop) wCRC = (wCRC<<8)^m_wTable[(wCRC^*pData++)&0x00ff];
	}
}

//---------------------------------------------- CMyWorkThread ----------------
CPtrArray CMyWorkThread::s_aWorkThread;

CMyWorkThread::CMyWorkThread()
{
    m_pParam = NULL;
    m_nThreadFlag = TF_NULL;
    m_pWinThread = NULL;
    s_aWorkThread.Add(this);
}

CMyWorkThread::~CMyWorkThread()
{
    Exit();
    int nSize = s_aWorkThread.GetSize();
    for(int i=0;i<nSize;i++)
    {
        if(s_aWorkThread[i]==this)
        {
            s_aWorkThread.RemoveAt(i);
            if(s_aWorkThread.GetSize()==0) s_aWorkThread.RemoveAll();
            break;
        }
    }
}

void CMyWorkThread::Run(AFX_THREADPROC pfnThreadProc,LPVOID pParam,int nPriority)
{
    m_pParam = pParam;
    m_eventExit.ResetEvent();
    m_pWinThread = AfxBeginThread(pfnThreadProc,this,nPriority);
}

void CMyWorkThread::Exit(void)
{
    m_eventExit.SetEvent();
    if(m_nThreadFlag==TF_RUNNING)
    {
        m_nThreadFlag = TF_EXITING;
        while(m_nThreadFlag!=TF_NULL) Sleep(1);
    }
    m_pWinThread = NULL;
}


//---------------------------------------------- CMyCommDispatch ------------------
CMyCommDispatch::CMyCommDispatch()
{
}

void CMyCommDispatch::AddTask(DWORD dwSpan100ms)
{
    tTASK Task;
    if(dwSpan100ms<=0) dwSpan100ms = 1;
    Task.dwTaskSpan100ms = dwSpan100ms;
    Task.dwTaskClock100ms = timeGetTime();
    m_aTask.Add(Task);

}

void CMyCommDispatch::ResetTask(int nIndex)
{
    int nSize = m_aTask.GetSize();
    if(nIndex>=0 && nIndex<nSize)
    {
        DWORD dwClock = timeGetTime();
        m_aTask[nIndex].dwTaskClock100ms = dwClock;
    }
}

int CMyCommDispatch::GetActiveTask(BOOL bAutoReset)
{
    int nSize = m_aTask.GetSize();
    int nActiveTask = -1;
    DWORD dwClockDiffMax = 0;

    DWORD dwClock = timeGetTime();
    for(int i=0;i<nSize;i++)
    {
        tTASK Task = m_aTask[i];
        DWORD dwClockDiff = dwClock - Task.dwTaskClock100ms;
        if(dwClockDiff>=Task.dwTaskSpan100ms*100)
        {
            // 激活超时时间比例最大的任务
            DWORD dwClockDiffMaxTmp = dwClockDiff/Task.dwTaskSpan100ms;                 // dwClockDiff*100/(Task.dwTaskSpan100ms*100)
            if(dwClockDiffMaxTmp>dwClockDiffMax)
            {
                dwClockDiffMax = dwClockDiffMaxTmp;
                nActiveTask = i;
            }
        }
    }
   
    if(nActiveTask>=0)
    {
        if(bAutoReset)
        {
            m_aTask[nActiveTask].dwTaskClock100ms = dwClock;
        }
        else
        {
            m_aTask[nActiveTask].dwTaskClock100ms += m_aTask[nActiveTask].dwTaskSpan100ms;
        }
    }

    return nActiveTask;
}


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------



