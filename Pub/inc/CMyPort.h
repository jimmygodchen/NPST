//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef __CMYPORT_H
#define __CMYPORT_H

#define COMBUFFSIZE           16000

#define WM_PORTMSG            (WM_USER + 1)             // �˿ڱ�����Ϣ

typedef struct
{
//     CString strPortName;
    COLORREF clrColor;
    CString strContent;
}PORTMSG;

//---------------------------------------------- CMyPort ----------------------
class CLASS_EXPORT CMyPort:public CMyObj
{
public:
    static CStringArray s_aType;
    static CMapStringToPtr s_mapTypeToClass;
    static void RegisterClass(CString strType, CRuntimeClass* pRuntimeClass);

public:
    DECLARE_SERIAL(CMyPort);
    CMyPort();
    virtual ~CMyPort();

public:
    CPtrArray m_aMsg;                   // ͨѶ����
    CMyUnitArray m_aUnit;				// �¹ҵ����е�Ԫ;
    WORD m_wDelayWriteCom;				// ����ǰ��ʱ������;
    BOOL m_bAutoSndMsg;                 // ����ReadCom��Writeʱ�Զ����ͱ�����Ϣ
    CWnd* m_pwndMsg;                     // ������Ϣ�Ĵ���

public:
    int m_nComUnitNo;					// ��ǰͨ�Ŵ���Ԫ;
    CMyWorkThread* m_pWorkThread;		// ͨ�Ź����߳�;
// protected:
//     BOOL m_bRequestSyn;					// ͨ��Уʱ��־;
//     WORD m_wSynDiff;					// Уʱ����ֵ(����);
// public:
//     BOOL m_bComReport;					// ���ļ���־;
//     short* m_pComReportHead;			// ���ļ�⻺����ͷ;
//     short* m_pComReportTail;			// ���ļ�⻺����β;
//     short* m_pComReportCur;				// ���ļ�⵱ǰָ��;
//     CDialog* m_pComReportDlg;			// ���ļ�ⴰ��;
// public:
//     virtual BOOL OnAttrib(CPropertySheet& sheet);
//     virtual void Serialize(CArchive& ar);
//     virtual void GetParamHead(CStringArray& aParamHead);
//     virtual void GetParamInfo(CStringArray& aParamInfo);
// public:
//     virtual void OnTimerFast(void);
//     virtual void OnTimer1Sec(void);
//     virtual void OnTimer5Sec(void);
//     virtual void OnTimer1Min(void);
//     virtual void OnTimer1Hour(void);
public:
//     virtual void OnComGotoStandby(void){};
    virtual BOOL OpenCom(void){ return FALSE; };
    virtual void CloseCom(void){};
    virtual void ClearCom(void){};
    virtual int ReadCom(BYTE* pRXData,int nRXLength){ return 0; };
    virtual int WriteCom(BYTE* pTXData,int nTXLength){ return 0; };

public:
//     void TriggerSyn(void);
    void StartComLoop(void);
    void StopComLoop(void);
    void ComLoop(void);
//     void StartComReport(void);
//     void StopComReport(void);
//     void ToggleComReportDlg(void);
//     void AddComReportRX(BYTE* pData,int nCount);
//     void AddComReportTX(BYTE* pData,int nCount);
// protected:
//     void BeginReadCom(void);
//     void EndReadCom(void);
//     void BeginWriteCom(void);
//     void EndWriteCom(void);

public:
    void AddComReportRX(BYTE* pData,int nCount);
    void AddComReportTX(BYTE* pData,int nCount);
    void SndMsg(const PORTMSG& PortMsg);
    BOOL GetMsg(PORTMSG& PortMsg);
};

typedef CTypedPtrList<CObList,CMyPort*> CMyPortList;
typedef CTypedPtrArray<CObArray,CMyPort*> CMyPortArray;

#endif/*__CMYPORT_H*/


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------

