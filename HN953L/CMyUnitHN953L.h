//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef __CMYUNITHN953L_H
#define __CMYUNITHN953L_H

//-----------------------------------------------------------------------------
#define EVENTTYPE_NULL		0x0000		//���¼�
#define EVENTTYPE_SWITCH	0x0001		//���ر�λ�¼�
#define EVENTTYPE_RUNINFO	0x0002		//������Ϣ�¼�
#define EVENTTYPE_ALARMED	0x0003		//�豸�澯�¼�
#define EVENTTYPE_TRIPPED	0x0004		//�豸�����¼�
#define EVENTTYPE_OPERATE	0x0005		//������¼�¼�
#define EVENTTYPE_ERRORED	0x0006		//�Լ��쳣�¼�
#define EVENTTYPE_NOTUSED	0x0007		//��Ч�¼�

#define EVENTCODE_NULL					//���¼�����
#define EVENTCODE_OTHER		0x0100		//�豸����¼�
#define EVENTCODE_SWITCH	0x0200		//��������λ�¼�
#define EVENTCODE_ALARMED	0x0300		//�澯����¼�
#define EVENTCODE_PROTECT	0x0400		//���������¼�
#define EVENTCODE_ERRORED	0x0500		//�Լ��쳣�¼�
#define EVENTCODE_LAD		0x0600		//����ͼ�¼�
#define EVENTCODE_REMOTE	0x0700		//ң�ز����¼�

//-----------------------------------------------------------------------------
typedef struct _DEVICETIME
{
    WORD wYear;						//��(ʵ����-2000,0-100);
    WORD wMonth;					//��(1-12);
    WORD wDay;						//��(1-31);
    WORD wHour;						//ʱ(0-23);
    WORD wMinute;					//��(0-59);
    WORD wSecond;					//��(0-59);
    WORD wMilliSecond;				//����(0-999);
}DEVICETIME;

typedef struct
{
    DEVICETIME time;				//�¼�������ʱ���;
    WORD wType;						//�¼�����;
    WORD wCode;						//�¼�����;
    WORD wData;						//�������,�京��ȡ�����¼�����;
}tEVENT;

typedef struct
{
    WORD wLCDContrast;					// LCD�Աȶ�
    WORD wszDeviceType[17];				// �豸����
    WORD wMultiLanguage;				// ��������
    WORD wModbusAddr1;					//ͨ�ŵ�ַ
    WORD wBaudrate1;					//ͨ������
    WORD wReserved[11];					// ����:�����ͺ����в���
}tDEVICEPARAM;

typedef struct
{
    WORD wToggleAlarmPT;			// PT���߸澯
    WORD wModePT;
    WORD wScaleCT;
    WORD wScalePT;
    WORD wSLType;
    WORD wDevLocal;
}tDEVICEPARAM_NPS;

typedef struct
{
    short nRegulateR;				//У��ϵ��ʵ��;
    short nRegulateX;				//У��ϵ���鲿;
}tREGULATE;

#define DFT_CHANNEL_HARD    11

//-----------------------------------------------------------------------------
typedef struct
{
    WORD wLinkIN;					// ����������;
    WORD wToggle;					// ����������Ͷ��;
}tINSETPOINT;

//-----------------------------------------------------------------------------
typedef struct
{
    WORD wToggle[10];                   // ����Ͷ��;
    WORD wSetpointArea1[32];            // ������ֵ��;
    tINSETPOINT INSetpoint[4];           // ����������;
}tDEVICESETPOINT;

typedef struct
{
    WORD wBZT_Mode;                 // ����Ͷ��ʽ
    WORD wBZT_MLSetUh;              // ĸ����ѹ��ֵ
    WORD wBZT_MLSetUl;              // ĸ��ʧѹ��ֵ
    WORD wBZT_SetUh1;               // 1ĸ��ѹ��ֵ
    WORD wBZT_SetUl1;               // 1ĸʧѹ��ֵ
    WORD wBZT_SetUh2;               // 2ĸ��ѹ��ֵ
    WORD wBZT_SetUl2;               // 2ĸʧѹ��ֵ
    WORD wBZT_SetI1;                // 1ĸ������ֵ
    WORD wBZT_SetI2;                // 2ĸ������ֵ
    WORD wBZT_SetTL1;               // ��1DLʱ��
    WORD wBZT_SetTL2;               // ��2DLʱ��
    WORD wBZT_SetT;                 // ����Ͷʱ��
    
    WORD wDL1_SetI;                 // ����I�ε���;
    WORD wDL1_SetT;                 // ����I��ʱ��;
    WORD wDL1_TogU;                 // ��ѹ����
    
    WORD wDL2_SetI;                 // ����II�ε���;
    WORD wDL2_SetT;                 // ����II��ʱ��;
    WORD wDL2_TogU;                 // ��ѹ����
    
    WORD wDL3_SetI;                 // ����III�ε���;
    WORD wDL3_SetT;                 // ����III��ʱ��;
    WORD wDL3_TogU;                 // ��ѹ����
    
    WORD wDL_SetU;                  // ��������������ѹ
    
    WORD wLX1_SetI;                 // ����I�ε���;
    WORD wLX1_SetT;                 // ����I��ʱ��;
    
    WORD wLX2_SetI;                 // ����I�ε���;
    WORD wLX2_SetT;                 // ����I��ʱ��;
    
    WORD wSY_SetU;					// ʧѹ��ѹ;
    WORD wSY_SetI;					// ʧѹ��������;
    WORD wSY_SetT;					// ʧѹʱ��;
}tDEVICESETPOINTNPS;

// ----------------------CMyDataHN953OPList-------------------------------------------
typedef struct
{
    CString strName;
    int nIndex;
}OPList;

typedef CArray<OPList, OPList&> CMyOpListArray;

class CMyDataHN953OPList:public CMyDataOperate
{
protected:
    DECLARE_SERIAL(CMyDataHN953OPList);
    CMyDataHN953OPList();
    
public:
    // ��ȡ��ʷ����¼����Ϣ
    CMyOpListArray m_arOPList;
    int m_nOPIndex;                     // Ҫ��ȡ���ݱ��
    
public:
    //     void SerializeDynInfo(CArchive& ar,int nDynInfoMode);
    void RefreshData(CMyOpListArray& arOpList);
    void SndCmd(int nOPIndex,BYTE Cmd=0xff);
    BOOL ExeOperate(void);
};

#define WAVERECORD_WAVECNT      10                  // �ܲ���
#define WAVERECORD_DOTNUM       (24*WAVERECORD_WAVECNT)
#define WAVERECORD_WAVENUM      5

#define WAVERECORD_DATASIZE     10               //ÿ��¼�������ݴ�С;

typedef struct
{
    DEVICETIME timeFreeze;                              // ¼����¼������ʱ��;
    WORD wRecordStatus;                                 // ¼������ǰ¼��״̬;
    WORD wFreezeDotNo;                                  // ¼����¼��������;
    WORD wCycleFlag;                                    // ¼�����Ƿ�ѭ����־;
    short nK[WAVERECORD_DATASIZE];                      // У��ϵ��
    WORD wOffset;                                       // ֱ������
    short nData[WAVERECORD_DATASIZE][WAVERECORD_DOTNUM]; // ¼����¼������;
}WAVERECORDR;


//---------------------------------------------- CMyDataHN953YK -----------
class CMyDataHN953YK:public CMyDataOperate
{
protected:
    DECLARE_SERIAL(CMyDataHN953YK);
    CMyDataHN953YK();
    
public:
    virtual BOOL ExeOperate(void);
};


//---------------------------------------------- CMyUnitHN953L ----------------------
class CMyUnitHN953L:public CMyUnitModbus
{
public:
    DECLARE_SERIAL(CMyUnitHN953L);
    CMyUnitHN953L();
    ~CMyUnitHN953L();

public:
    const float m_fScaleIM;
    const float m_fScaleIP;
    const float m_fScaleUll;

public:
    CMyDataString* m_pCRCInfo;
    CMyDataBin* m_pBI[17];
    CMyDataVector* m_pVector[14];
    CMyDataFloat* m_pFloat[4];

    CMyDataHN953YK* m_pYK[6];

    CMyDataOperate* m_pInitDev;
    CMyDataOperate* m_pResetDev;
    CMyDataOperate* m_pFreezeRecord;
    CMyDataOperate* m_pAdjust;
    CMyDataOperate* m_pTimesyn;

    CMyDataMem* m_pParam;
    CMyDataMem* m_pRegulate;
    CMyDataMem* m_pSetpoint;
    CMyDataHN953OPList* m_pWaveRecordList;
    CMyRTWave* m_pRTWave;

public:
    int m_nTask;
    BOOL m_bInfoOK;
    BOOL m_bTimeSyn;
    BOOL m_bParamOK;
    BOOL m_bRegulateOK;
    BOOL m_bSetpointOK;
    BOOL m_bWaveRecordListOK;

    WORD m_wCountParam;
    WORD m_wCountParamOld;
    WORD m_wCountRegulate;
    WORD m_wCountRegulateOld;
    WORD m_wCountSetpoint;
    WORD m_wCountSetpointOld;
    WORD m_wCountWaveRecord;
    WORD m_wCountWaveRecordOld;

public:
    virtual BOOL OnCreate(void);
    virtual BOOL OnCreateData(CMyData* pData);
    virtual void OnPortOpen(void);
    virtual void ExchangeComData(COMCONTROL* pCC);

public:
    virtual void OnEditMem(const CMyDataMem& Mem);

public:
    void ReceiveInfo(COMCONTROL* pCC);
    void TimeSyn(COMCONTROL* pCC);
    void ReceiveParam(COMCONTROL* pCC);
    void ReceiveRegulate(COMCONTROL* pCC);
    void ReceiveSetpoint(COMCONTROL* pCC);
    void ReceiveAnalog(COMCONTROL* pCC);
    void ReceiveAnalogExt(COMCONTROL* pCC);
    void ReceiveEventTable(COMCONTROL* pCC);
    void ReceiveWaveRecordHeadList(COMCONTROL* pCC);
    void ReceiveRTWave(COMCONTROL* pCC);

    BOOL ReceiveWave(COMCONTROL* pCC, int nWaveNo);
    BOOL ReceiveWaveRecordHead(COMCONTROL* pCC, int nWaveNo, WAVERECORDR& Waverecord);
    BOOL ReceiveWaveRecordData(COMCONTROL* pCC, int nWaveNo, WAVERECORDR& Waverecord);

public:
    void OnOpenList(CMyDataHN953OPList* pOPList);
    CString GetEventText(tEVENT& Event);
    CString GetEventTextProtect(WORD wProtectAct, WORD wProtectIndexExt, WORD wActData);
    void SaveWave(WAVERECORDR& Waverecord);
    void SetWaveInfoAD(CMyWaveInfo& waveinfo,int nChannelNo,CString strChannelName, CString strUnitage,
        int nWaveRecordedDot, WAVERECORDR& Waverecord);
    void SetWaveInfoDI(CMyWaveInfo& waveinfo, int nChannelNo, WORD wMask, int nWaveRecordedDot, WAVERECORDR& Waverecord);
    float GetChK(int nChIndex);

};

#endif/*__CMYUNITHN953L_H*/

//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------

