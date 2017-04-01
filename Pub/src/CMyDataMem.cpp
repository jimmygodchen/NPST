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
#include "Pub.h"

//---------------------------------------------- CMyDataMem -----------
IMPLEMENT_SERIAL(CMyDataMem, CMyDataOperate, 0)

CMyDataMem::CMyDataMem():CMyDataOperate()
{
    m_bOK = FALSE;
    m_nID = 0;
    m_nSize = 0;
    m_pMemR = NULL;
    m_pMemW = NULL;
}

CMyDataMem::~CMyDataMem()
{
    if(m_pMemR)
    {
        delete [] m_pMemR;
        m_pMemR= NULL;
    }

    if(m_pMemW)
    {
        delete [] m_pMemW;
        m_pMemW= NULL;
    }
}

void CMyDataMem::Initialize(CString strName, int nID, int nSize)
{
    CMyDataOperate::Initialize(strName);;
    m_nSize = nSize;
    m_nID = nID;
    m_pMemR = new BYTE[nSize];
    m_pMemW = new BYTE[nSize];

    memset(m_pMemR, 0, nSize);
    memset(m_pMemW, 0, nSize);
}

BOOL CMyDataMem::ExeOperate(void)
{
    if(m_bOK)
    {
        ASSERT(m_pParentUnit);
        ASSERT(m_pParentUnit->IsKindOf(RUNTIME_CLASS(CMyUnit)));
        ((CMyUnit*)m_pParentUnit)->OnEditMem(*this);
        return TRUE;
    }
    return FALSE;
}

void CMyDataMem::RefreshData(const void* pMem)
{
    memcpy(m_pMemR, pMem, m_nSize);
    m_bOK = TRUE;
    IncrementUpdateID();
}

void CMyDataMem::StoreToDevice(const void* pMem)
{
    memcpy(m_pMemW, pMem, m_nSize);
    m_OperateCode = 0xff;
    IncrementUpdateID();
}

void CMyDataMem::OnOpen(CString strDevType, char* pczExtension, void* m_pMem)
{
    CString strpath = g_strSysPath + _T("\\Param");
    _mkdir(strpath);
    DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
    strpath = strpath +_T("\\*") + pczExtension;
    LPSTR lpszFile = (char*)(const char*)strpath;;
    CString strFilter;
    strFilter.Format(_T("装置参数配置文件(*%s)|*%s||"), pczExtension, pczExtension);
    CFileDialog dlg(TRUE, pczExtension, lpszFile, dwFlags, strFilter);
    if(MyDoModal(&dlg, PublicDLL.hModule)==IDOK)
    {
        CString strFileName = dlg.GetPathName();
        CFile file;
        if(file.Open(strFileName, CFile::modeRead))
        {
            CArchive ar(&file, CArchive::load);
            CString strtype;
            ar >> strtype;
            if(strcmp(strtype, strDevType)==0)
            {
                ar.Read(m_pMem, m_nSize);
            }
            else MyMessageBox(_T("装置参数文件格式不匹配!"), _T("请注意"), MB_ICONWARNING|MB_OK);
            ar.Close();
            file.Close();
        }
    }
}

void CMyDataMem::OnSave(CString strDevType, CString strFileName, char* pczExtension, const void* pMem)
{
    CString strpath = g_strSysPath + _T("\\Param");
    _mkdir(strpath);
    strFileName= strpath + strFileName;
    DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
    LPSTR lpszFile = (char*)(const char*)strFileName;
    CString strFilter;
    strFilter.Format(_T("装置参数配置文件(*%s)|*%s||"), pczExtension, pczExtension);
    CFileDialog dlg(FALSE, pczExtension, lpszFile, dwFlags, strFilter);
    if(MyDoModal(&dlg, PublicDLL.hModule)==IDOK)
    {
        strFileName = dlg.GetPathName();
        CFile file;
        if(file.Open(strFileName,CFile::modeWrite|CFile::modeCreate))
        {
            CArchive ar(&file,CArchive::store);
            ar << strDevType ;
            ar.Write(pMem, m_nSize);
            ar.Close();
            file.Close();
        }
    }
}

//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------



