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

//---------------------------------------------- CMyObj -----------------------
IMPLEMENT_SERIAL(CMyObj,CObject,0)

CMyObj::CMyObj():CObject()
{
    m_nID = 0;
    m_strType = _T("");
    m_strName = _T("");
}

void CMyObj::Serialize(CArchive& ar)
{
    CObject::Serialize(ar);
    if(ar.IsStoring())
    {
        ar << m_strType;
        ar << m_strName;
    }
    else
    {
        ar >> m_strType;
        ar >> m_strName;
    }
}

BOOL CMyObj::OnAttrib(void)
{
    CString strOEMType;
    CString strName = m_strName;
    if(DeviceType2OEMType(m_strName,strOEMType))
    {
        strName = strOEMType;
    }
    CBCGPPropertySheet sheet(_T("<")+strName+_T(">参数设定"));
    sheet.SetLook(CBCGPPropertySheet::PropSheetLook_OneNoteTabs);
    sheet.GetTab().EnableAutoColor();
//     sheet.GetTab().SetButtonsVisible(FALSE);
    sheet.GetTab().SetTabBorderSize(1);
    sheet.EnableVisualManagerStyle(TRUE, TRUE);
    sheet.EnablePageHeader(0);
    return OnAttrib(sheet);
}

BOOL CMyObj::OnAttrib(CBCGPPropertySheet& sheet)
{
    CPtrArray aPage;
    int nPageSize = sheet.GetPageCount();
    for(int i=0;i<nPageSize;i++)
    {
        CPropertyPage* pPropertyPage = sheet.GetPage(nPageSize-i-1);
        sheet.RemovePage(nPageSize-i-1);
        pPropertyPage->m_psp.dwFlags &= ~PSP_HASHELP;
        aPage.Add(pPropertyPage);
    }
    for(i=0;i<nPageSize;i++) sheet.AddPage((CPropertyPage*)aPage[i]);
    
    sheet.m_psh.dwFlags |= PSH_NOAPPLYNOW;
    sheet.m_psh.dwFlags &= ~PSP_HASHELP;
//     sheet.Construct("<"+m_strName+">参数设定");
    if(sheet.DoModal()==IDOK) return TRUE;
    return FALSE;
}

CString CMyObj::GetFullName(void)
{
    if(m_strType.GetLength()==0) return m_strName;
    else return MyReverseSpanExcluding(m_strType,"%")+":"+m_strName;
}

void CMyObj::Load(void)
{
    CFile file;
    if(file.Open(GetFileName(),CFile::modeRead|CFile::shareDenyNone))
    {
        CArchive ar(&file,CArchive::load);
        DWORD dwID;
        ar >> dwID;
        if(dwID==0xaaaaaaaa)
        {
            m_critical.Lock();
            Serialize(ar);
            m_critical.Unlock();
        }
        ar.Close();
        file.Close();
    }
}

void CMyObj::Store(void)
{
    ASSERT(!m_strName.IsEmpty());

    remove(GetFileName());
    CFile file;
    if(file.Open(GetFileName(),CFile::modeWrite|CFile::modeCreate))
    {
        CArchive ar(&file,CArchive::store);
        DWORD dwID = 0xaaaaaaaa;
        ar << dwID;
        m_critical.Lock();
        Serialize(ar);
        m_critical.Unlock();
        ar.Close();
        file.Flush();
        file.Close();
    }
}

CString CMyObj::GetFileName(void)
{
    CString strFullName = GetFullName();
    CString strFileName = g_strSysPath + _T("\\Temp\\") + strFullName + _T(".cfg");
    return strFileName;
}

// void CMyObj::ClearError(void)
// {
//     m_strError.Empty();
// }
// 
// void CMyObj::SetError(CString strError)
// {
//     m_strError = strError;
// }
// 
// CString CMyObj::GetLastError(void)
// {
//     return m_strError;
// }

//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------



