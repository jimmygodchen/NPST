/*
;*****************************************************************************************************
;*						Copyright (c) 2009 by ThinkBoy. 
;*						All rights reserved.
;*
;* Header:
;* File Name: 
;* Author: jimmy
;* Date:
;*****************************************************************************************************
;*/

#include "stdafx.h"
#include "CMyEnumSCI.h"
#include "atlbase.h"

void CMyEnumSCI::EnumSCI(void)
{
    DWORD wKeySize = 512;
    TCHAR *wKey = new TCHAR[wKeySize];
    CString strKey;
    DWORD wValueSize = 512;
    TCHAR *wValue = new TCHAR[wValueSize];
    CString strValue;
    DWORD dwCountOfSubKey;
    DWORD dwCountOfValue;
    DWORD dwType;
    LONG lResult;
    
    CString strpath = _T("HARDWARE\\DEVICEMAP\\SERIALCOMM");
    
    CRegKey regKey;
//     m_arKey.RemoveAll();
    m_arCOM.RemoveAll();
    
    lResult = regKey.Open(HKEY_LOCAL_MACHINE, strpath, KEY_READ);
    if(lResult != ERROR_SUCCESS) return;
    
    lResult = ::RegQueryInfoKey(regKey.m_hKey, NULL, NULL, NULL,  
        &dwCountOfSubKey, NULL, NULL, &dwCountOfValue, NULL, NULL, NULL, NULL);
    if(lResult==ERROR_SUCCESS)
    {
        for(int i=0;i<dwCountOfValue;i++)
        {
            wKeySize = 512;
            // 必须要在循环体内重新设置该值，因为wStrSize每次会被RegEnumValue改变，用来接受下一个wStr  
            // 如果不重新设置，你会发现遍历只能进行一两次  
            lResult = RegEnumValue(regKey.m_hKey, i, wKey, &wKeySize, NULL, &dwType,NULL, NULL);
            
            if(lResult!=ERROR_SUCCESS) break;
            if(dwType!=REG_SZ) continue;
            
            strKey = wKey;
//             m_arKey.Add(strKey);
            if(strKey==_T("")) continue;
            wValueSize = 512;
            lResult = regKey.QueryValue(wValue, wKey, &wValueSize);
            if(lResult==ERROR_SUCCESS)
            {
                strValue = wValue;
                strValue.MakeUpper();
                m_arCOM.Add(strValue);
            }
        }
    }
    
//     m_wndListCom.SetItemCount(m_arCOM.GetSize());
    
    delete []wKey;
    delete []wValue;
    regKey.Close();
}

int CMyEnumSCI::GetSCI(int nIndex)
{
    int nSize = m_arCOM.GetSize();
    ASSERT(nIndex<nSize);
    CString str = m_arCOM[nIndex];
    str.MakeUpper();
    str.TrimRight();
    int nPos = str.Find(_T("COM"));
    int nLen = str.GetLength()-3-nPos;
    CString strID = str.Right(nLen);
    int nComID = atoi(strID);
    return nComID;
}

/*
;*****************************************************************************************************
;*							End Of File
;*****************************************************************************************************
;*/