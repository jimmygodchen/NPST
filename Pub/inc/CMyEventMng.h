//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef __CMYEVENTMNG_H
#define __CMYEVENTMNG_H

#define WM_EVENTMSG            (WM_USER + 2)             // �¼���Ϣ

typedef struct
{
    WORD wYear;                     // ��
    BYTE Mon;                       // ��
    BYTE Day;                       // ��
    BYTE Hour;                      // ʱ
    BYTE Min;                       // ��
    BYTE Sec;                       // ��
    WORD wMs;                       // ����
    COLORREF clrColor;              // ��ɫ
    CString strContent;             // ����
}EVTMSG;

typedef CArray<EVTMSG, EVTMSG&> CMyEventArray;

class CLASS_EXPORT CMyEventMng:public CMyObj
{
public:
    DECLARE_SERIAL(CMyEventMng);
    CMyEventMng();
    ~CMyEventMng();

public:
    CWnd* m_pwndMsg;                    // ������Ϣ�Ĵ���
    CMyEventArray m_aEvent;             // �¼�

public:
    void SndMsg(const EVTMSG& EventMsg);
    BOOL GetMsg(EVTMSG& EventMsg);
    void Empty(void);
};


#endif/*__CMYEVENTMNG_H*/


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------

