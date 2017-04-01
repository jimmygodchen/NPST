//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef __CMYPM310_H
#define __CMYPM310_H

#define SWITCH_COUNT            4

// #define EVENT_COUNT			100

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

// #define EVENTCODE_ALARMPT3		(EVENTCODE_ALARMED+0x00)	//����PT����;
// #define EVENTCODE_ALARMPT2		(EVENTCODE_ALARMED+0x01)	//����PT����;
// #define EVENTCODE_ALARMPT1		(EVENTCODE_ALARMED+0x02)	//����PT����;
// #define EVENTCODE_ALARMKM		(EVENTCODE_ALARMED+0x03)    //���ƻ�·����;
// 
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

typedef struct _EVENT
{
    DEVICETIME time;				//�¼�������ʱ���;
    WORD wType;						//�¼�����;
    WORD wCode;						//�¼�����;
    WORD wData;						//�������,�京��ȡ�����¼�����;
}EVENT;

//---------------------------------------------- CMyDataPMParam -----------
typedef struct
{
    WORD wLCDContrast;					// LCD�Աȶ�
    WORD wszDeviceType[17];				// �豸����
    WORD wMultiLanguage;				// ��������
    WORD wModbusAddr1;					// ͨ�ŵ�ַ
    WORD wBaudrate1;					// ͨ������
    WORD wReserved[11];					// ����:�����ͺ����в���
}tDEVICEPARAM;

typedef struct
{
    WORD wToggleAlarmPT;                // PT���߸澯
    WORD wModePT;
    WORD wScaleCT;
    WORD wScalePT;
    WORD wSLType;
}tDEVICEPARAM_PM;

class CMyDataPMParam:public CMyDataOperate
{
protected:
    DECLARE_SERIAL(CMyDataPMParam);
    CMyDataPMParam();

public:
    BOOL m_bOK;
    tDEVICEPARAM m_deviceParamR;
    tDEVICEPARAM m_deviceParamW;

public:
    virtual void RefreshData(tDEVICEPARAM& DeviceParam);
    virtual void StoreToDevice(tDEVICEPARAM& pDeviceParam);
    virtual BOOL ExeOperate(void);
};

//---------------------------------------------- CMyDataPMRegulate -----------
typedef struct
{
    short nRegulateR;				//У��ϵ��ʵ��;
    short nRegulateX;				//У��ϵ���鲿;
}REGULATE;

typedef struct
{
    REGULATE regulate[6];
}tREGULATESET;

class CMyDataPMRegulate:public CMyDataOperate
{
protected:
    DECLARE_SERIAL(CMyDataPMRegulate);
    CMyDataPMRegulate();
    
public:
    BOOL m_bOK;
    tREGULATESET m_RegulateR;
    tREGULATESET m_RegulateW;
    
public:
    virtual void RefreshData(tREGULATESET& Regulate);
    virtual void StoreToDevice(tREGULATESET& Regulate);
    virtual BOOL ExeOperate(void);
};


//---------------------------------------------- CMyDataPMSetpoint -----------
//-----------------------------------------------------------------------------
typedef struct
{
    WORD wConfig;					// ��������;
    WORD wLinkIN;					// ����������;
    WORD wToggle;					// ����������Ͷ��;
}INSETPOINT;

//-----------------------------------------------------------------------------
typedef struct
{
    WORD wConfig[6];			    // ��������;
    WORD wToggle[6];				// ����Ͷ��;
    WORD wSetpointArea1[24];		// ������ֵ��1;
    INSETPOINT INSetpoint[4];		// ����������;
}tDEVICESETPOINT;

typedef struct
{
    WORD wDL1_SetI;					// ����I�ε���;
    WORD wDL1_SetT;					// ����I��ʱ��;

    WORD wDL2_SetI;					// ����II�ε���;
    WORD wDL2_SetT;					// ����II��ʱ��;

    WORD wGY1_SetU;					// ��ѹI�ε���;
    WORD wGY1_SetT;					// ��ѹI��ʱ��;

    WORD wGY2_SetU;					// ��ѹII�ε���;
    WORD wGY2_SetT;					// ��ѹII��ʱ��;

    WORD wQY1_SetU;					// ǷѹI�ε���;
    WORD wQY1_SetT;					// ǷѹI��ʱ��;

    WORD wQY2_SetU;					// ǷѹII�ε���;
    WORD wQY2_SetT;					// ǷѹII��ʱ��;
}tDEVICESETPOINT_PM;

class CMyDataPMSetpoint:public CMyDataOperate
{
protected:
    DECLARE_SERIAL(CMyDataPMSetpoint);
    CMyDataPMSetpoint();
    
public:
    BOOL m_bOK;
    tDEVICESETPOINT m_SetpointR;
    tDEVICESETPOINT m_SetpointW;
    
public:
    virtual void RefreshData(tDEVICESETPOINT& Setpoint);
    virtual void StoreToDevice(tDEVICESETPOINT& Setpoint);
    virtual BOOL ExeOperate(void);
};

// //---------------------------------------------- CMyDataNPSYC -----------
// class CMyDataNPSYC:public CMyDataOperate
// {
// protected:
//     DECLARE_SERIAL(CMyDataNPSYC);
//     CMyDataNPSYC();
// 
// public:
// //     virtual void RefreshData(DEVICEPARAM& DeviceParam);
// //     virtual void StoreToDevice(DEVICEPARAM& pDeviceParam);
//     virtual BOOL ExeOperate(void);
// };

// ----------------------CMyDataPMOPList-------------------------------------------
// ����Server��HMI֮�佻��List����
// ��Ҫ���ڶ�ȡ��ʷ����¼����ʾ��������

typedef struct
{
    CString strName;
    int nIndex;
}OPList;

typedef CArray<OPList, OPList&> CMyOpListArray;

class CMyDataPMOPList:public CMyDataOperate
{
protected:
    DECLARE_SERIAL(CMyDataPMOPList);
    CMyDataPMOPList();

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

#define WAVERECORD_WAVECNT  10                  // �ܲ���
#define WAVERECORD_DOTNUM   (24*WAVERECORD_WAVECNT)
#define WAVERECORD_WAVENUM  5

#define WAVERECORD_DATASIZE     7               //ÿ��¼�������ݴ�С;

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


//---------------------------------------------- CMyUnitPM310 ----------------------
class CMyUnitPM310:public CMyUnitModbus
{
public:
    DECLARE_SERIAL(CMyUnitPM310);
    CMyUnitPM310();
    ~CMyUnitPM310();

public:
    virtual BOOL OnCreate(void);
    virtual BOOL OnCreateData(CMyData* pData);
    virtual void OnPortOpen(void);
    virtual void ExchangeComData(COMCONTROL* pCC);

public:
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
    const float m_fScaleI;
    const float m_fScaleUll;

public:
//     CMyDataFloat* m_pIa;
//     CMyDataFloat* m_pAngIa;
//     CMyDataFloat* m_pIb;
//     CMyDataFloat* m_pAngIb;
//     CMyDataFloat* m_pIc;
//     CMyDataFloat* m_pAngIc;
// 
//     CMyDataFloat* m_pUa;
//     CMyDataFloat* m_pUb;
//     CMyDataFloat* m_pUc;
//     CMyDataFloat* m_pUab;
//     CMyDataFloat* m_pUbc;
//     CMyDataFloat* m_pUca;
//     CMyDataFloat* m_pAngUa;
//     CMyDataFloat* m_pAngUb;
//     CMyDataFloat* m_pAngUc;
//     CMyDataFloat* m_pAngUab;
//     CMyDataFloat* m_pAngUbc;
//     CMyDataFloat* m_pAngUca;

    CMyDataVector* m_pIa;
    CMyDataVector* m_pIb;
    CMyDataVector* m_pIc;
    CMyDataVector* m_pUa;
    CMyDataVector* m_pUb;
    CMyDataVector* m_pUc;
    CMyDataVector* m_pUab;
    CMyDataVector* m_pUbc;
    CMyDataVector* m_pUca;

    CMyDataFloat* m_pFreq;
    CMyDataFloat* m_pP;
    CMyDataFloat* m_pQ;
    CMyDataFloat* m_pS;
    CMyDataFloat* m_pPF;

    CMyDataFloat* m_pEpimp;
    CMyDataFloat* m_pEqimp;
    CMyDataFloat* m_pEpexp;
    CMyDataFloat* m_pEqexp;

    CMyDataString* m_pCRCInfo;

public:
//     CMyDataFloat* m_pIa;
//     CMyDataFloat* m_pIb;
//     CMyDataFloat* m_pIc;
//     CMyDataFloat* m_pIA;
//     CMyDataFloat* m_pIC;
//     CMyDataFloat* m_pUa;
//     CMyDataFloat* m_pUb;
//     CMyDataFloat* m_pIB;
//     CMyDataFloat* m_pUc;
//     CMyDataFloat* m_pUab;
//     CMyDataFloat* m_pUbc;
//     CMyDataFloat* m_pUca;
//     CMyDataFloat* m_p3I0;
//     CMyDataFloat* m_pF;
//     CMyDataFloat* m_pP;
//     CMyDataFloat* m_pQ;
//     CMyDataFloat* m_pPF;

    CMyDataBin* m_pBi[SWITCH_COUNT];

    CMyDataOperate* m_pOpInitDevice;
    CMyDataOperate* m_pOpReset;
    CMyDataOperate* m_pOpFreezeWave;
    CMyDataOperate* m_pOpAdjust;
    CMyDataOperate* m_pOpTimesyn;

    CMyDataPMParam* m_pParam;
    CMyDataPMRegulate* m_pRegulate;
    CMyDataPMSetpoint* m_pSetpoint;
    CMyDataPMOPList* m_pWaveRecordList;

public:
    void ReceiveInfo(COMCONTROL* pCC);
    void TimeSyn(COMCONTROL* pCC);
    void ReceiveParam(COMCONTROL* pCC);
    void ReceiveRegulate(COMCONTROL* pCC);
    void ReceiveSetpoint(COMCONTROL* pCC);
    void ReceiveAnalog(COMCONTROL* pCC);
    void ReceiveAnalogExt(COMCONTROL* pCC);
    void ReceiveWaveRecordHeadList(COMCONTROL* pCC);
    void ReceiveEventTable(COMCONTROL* pCC);
    BOOL ReceiveWave(COMCONTROL* pCC, int nWaveNo);
    BOOL ReceiveWaveRecordHead(COMCONTROL* pCC, int nWaveNo, WAVERECORDR& Waverecord);
    BOOL ReceiveWaveRecordData(COMCONTROL* pCC, int nWaveNo, WAVERECORDR& Waverecord);

public:
    void OnEditDeviceParam(CMyDataPMParam* pDataParam);
    void OnEditRegulate(CMyDataPMRegulate* pDataRegulate);
    void OnEditSetpoint(CMyDataPMSetpoint* pDataSetpoint);
//     void OnExcuteYC(CMyDataNPSYC* pDataYC);
    void OnOpenList(CMyDataPMOPList* pOPList);

    CString GetEventText(EVENT& Event);
    CString GetEventTextProtect(WORD wProtectAct, WORD wProtectIndexExt, WORD wActData);
    void SaveWave(WAVERECORDR& Waverecord);
    void SetWaveInfoAD(CMyWaveInfo& waveinfo,int nChannelNo,CString strChannelName, CString strUnitage,
        int nWaveRecordedDot, WAVERECORDR& Waverecord);
    void SetWaveInfoDI(CMyWaveInfo& waveinfo, int nChannelNo, WORD wMask, int nWaveRecordedDot, WAVERECORDR& Waverecord);

};

#endif/*__CMYPM310_H*/


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------

