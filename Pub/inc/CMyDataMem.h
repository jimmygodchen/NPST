//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef __CMYDATAMEM_H
#define __CMYDATAMEM_H

// ---------------------------------------------- CMyDataMem -------------
class CLASS_EXPORT CMyDataMem:public CMyDataOperate
{
protected:
    DECLARE_SERIAL(CMyDataMem);
    CMyDataMem();
    ~CMyDataMem();
    
public:
    int m_nID;                      // ������ָʾCMyDataMem����;
    int m_nSize;                    // �����ڴ��С
    BOOL m_bOK;                     // ָʾ�ڴ��������Ƿ���Ч
    void* m_pMemR;                  // һ�����ڴ���޸�ǰ����
    void* m_pMemW;                  // һ�����ڴ���޸ĺ�����
    
public:
    virtual void Initialize(CString strName, int nID, int nSize);
    virtual BOOL ExeOperate(void);
    virtual void RefreshData(const void* pMem);
    void StoreToDevice(const void* pMem);
    void OnOpen(CString strDevType, char* pczExtension, void* m_pMem);
    void OnSave(CString strDevType, CString strFileName, char* pczExtension, const void* pMem);
};

#endif/*__CMYDATAMEM_H*/


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------

