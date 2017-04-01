//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef __CMYNPS7510_H
#define __CMYNPS7510_H

#define EVENT_COUNT			100
#define SWITCH_COUNT		12

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

#define EVENTCODE_ALARMPT3		(EVENTCODE_ALARMED+0x00)	//����PT����;
#define EVENTCODE_ALARMPT2		(EVENTCODE_ALARMED+0x01)	//����PT����;
#define EVENTCODE_ALARMPT1		(EVENTCODE_ALARMED+0x02)	//����PT����;
#define EVENTCODE_ALARMKM		(EVENTCODE_ALARMED+0x03)    //���ƻ�·����;

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

//---------------------------------------------- CMyDataNPSParam -----------
typedef struct
{
    WORD wLCDContrast;					// LCD�Աȶ�
    WORD wszDeviceType[17];				// �豸����
    WORD wMultiLanguage;				// ��������
    WORD wModbusAddr1;					// ͨ�ŵ�ַ
    WORD wBaudrate1;					// ͨ������
    WORD wReserved[11];					// ����:�����ͺ����в���
}DEVICEPARAM;

typedef struct
{
    WORD wToggleAlarmPT;			// PT���߸澯
    WORD wModePT;
    WORD wScaleCT;
    WORD wScalePT;
}DEVICEPARAM_NPS;

class CMyDataNPSParam:public CMyDataOperate
{
protected:
    DECLARE_SERIAL(CMyDataNPSParam);
    CMyDataNPSParam();

public:
    BOOL m_bOK;
    DEVICEPARAM m_deviceParamR;
    DEVICEPARAM m_deviceParamW;

public:
    virtual void RefreshData(DEVICEPARAM& DeviceParam);
    virtual void StoreToDevice(DEVICEPARAM& pDeviceParam);
    virtual BOOL ExeOperate(void);
};

//---------------------------------------------- CMyDataNPSRegulate -----------
typedef struct
{
    short nRegulateR;				//У��ϵ��ʵ��;
    short nRegulateX;				//У��ϵ���鲿;
}REGULATE;

typedef struct
{
    REGULATE regulate[10];
}REGULATESET;

class CMyDataNPSRegulate:public CMyDataOperate
{
protected:
    DECLARE_SERIAL(CMyDataNPSRegulate);
    CMyDataNPSRegulate();
    
public:
    BOOL m_bOK;
    REGULATESET m_RegulateR;
    REGULATESET m_RegulateW;
    
public:
    virtual void RefreshData(REGULATESET& Regulate);
    virtual void StoreToDevice(REGULATESET& Regulate);
    virtual BOOL ExeOperate(void);
};


//---------------------------------------------- CMyDataNPSSetpoint -----------
//-----------------------------------------------------------------------------
typedef struct
{
    WORD wLinkIN;					// ����������;
    WORD wToggle;					// ����������Ͷ��;
}INSETPOINT;

//-----------------------------------------------------------------------------
typedef struct
{
    WORD wToggle[8];				// ����Ͷ��;
    WORD wSetpointArea1[24];		// ������ֵ��1;
    INSETPOINT INSetpoint[4];		// ����������;
}DEVICESETPOINT;

typedef struct
{
    WORD wDL1_SetI;					// ����I�ε���;
    WORD wDL1_SetT;					// ����I��ʱ��;
    WORD wDL1_TogU;                 // ��ѹ����
    
    WORD wDL2_SetI;					// ����II�ε���;
    WORD wDL2_SetT;					// ����II��ʱ��;
    WORD wDL2_TogU;                 // ��ѹ����
    
    WORD wDL3_SetI;					// ����III�ε���;
    WORD wDL3_SetT;					// ����III��ʱ��;
    WORD wDL3_TogU;                 // ��ѹ����
    
    WORD wDL_SetU;                  // ��������������ѹ
    
    WORD wLX1_SetI;				    // ����I�ε���;
    WORD wLX1_SetT;				    // ����I��ʱ��;
    
    WORD wLX2_SetI;				    // ����I�ε���;
    WORD wLX2_SetT;				    // ����I��ʱ��;
    
    WORD wGFH_SetI;				    // �����ɵ���;
    WORD wGFH_SetT;				    // ������ʱ��;
    //     WORD wGFH_GJ;                   // �澯
    
    WORD wDDY_SetU;					// �͵�ѹ��ѹ;
    WORD wDDY_SetI;					// �͵�ѹ��������;
    WORD wDDY_SetT;					// �͵�ѹʱ��;
}DEVICESETPOINT_NPS;

class CMyDataNPSSetpoint:public CMyDataOperate
{
protected:
    DECLARE_SERIAL(CMyDataNPSSetpoint);
    CMyDataNPSSetpoint();
    
public:
    BOOL m_bOK;
    DEVICESETPOINT m_SetpointR;
    DEVICESETPOINT m_SetpointW;
    
public:
    virtual void RefreshData(DEVICESETPOINT& Setpoint);
    virtual void StoreToDevice(DEVICESETPOINT& Setpoint);
    virtual BOOL ExeOperate(void);
};

//---------------------------------------------- CMyDataNPSYC -----------
class CMyDataNPSYC:public CMyDataOperate
{
protected:
    DECLARE_SERIAL(CMyDataNPSYC);
    CMyDataNPSYC();

public:
//     virtual void RefreshData(DEVICEPARAM& DeviceParam);
//     virtual void StoreToDevice(DEVICEPARAM& pDeviceParam);
    virtual BOOL ExeOperate(void);
};


// ----------------------CMyDataOPList-------------------------------------------
// ����Server��HMI֮�佻��List����
// ��Ҫ���ڶ�ȡ��ʷ����¼����ʾ��������
typedef struct
{
    CString strName;
    int nIndex;
}OPList;

class CMyDataOPList:public CMyDataOperate
{
protected:
    DECLARE_SERIAL(CMyDataOPList);
    CMyDataOPList();
    
public:
    // ��ȡ��ʷ����¼����Ϣ
    CArray<OPList,OPList> m_arOPList;
    int m_nOPIndex;					// Ҫ��ȡ���ݱ��
    
public:
//     void SerializeDynInfo(CArchive& ar,int nDynInfoMode);
    void RefreshData(CArray<OPList,OPList>& arOpList);
    void SndCmd(int nOPIndex,BYTE Cmd=0xff);
    BOOL ExeOperate(void);
};


#define WAVERECORD_WAVECNT  10                  // �ܲ���
#define WAVERECORD_DOTNUM   (24*WAVERECORD_WAVECNT)
#define WAVERECORD_WAVENUM  2

#define WAVERECORD_DATASIZE     6               //ÿ��¼�������ݴ�С;

typedef struct
{
    DEVICETIME timeFreeze;                              //¼����¼������ʱ��;
    WORD wRecordStatus;                                 //¼������ǰ¼��״̬;
    WORD wFreezeDotNo;                                  //¼����¼��������;
    WORD wCycleFlag;                                    //¼�����Ƿ�ѭ����־;
    WORD wData[WAVERECORD_DOTNUM][WAVERECORD_DATASIZE]; //¼����¼������;
}WAVERECORD;


//---------------------------------------------- CMyUnitNPS7510 ----------------------
class CMyUnitNPS7510:public CMyUnit
{
public:
    DECLARE_SERIAL(CMyUnitNPS7510);
    CMyUnitNPS7510();
    ~CMyUnitNPS7510();

protected:
    CMyCommDispatch m_commdispatch;

public:
    virtual BOOL OnAttrib(CBCGPPropertySheet& sheet);
    virtual void ExchangeComData(COMCONTROL* pCC);

public:
    int m_nAddr;
    int m_nTimeout;
    BOOL m_bInfoOK;
    BOOL m_bParamOK;
    BOOL m_bRegulateOK;
    BOOL m_bSetpointOK;
    BOOL m_bWaveRecordListOK;
    BOOL m_bTimeSyn;

//     WORD m_wCountInfo;
    WORD m_wCountParam;
    WORD m_wCountRegulate;
    WORD m_wCountRegulateOld;
    WORD m_wCountParamOld;
    WORD m_wCountSetpoint;
    WORD m_wCountSetpointOld;
    WORD m_wCountEvent;
    WORD m_wCountEventOld;
    WORD m_wCountWaveRecord;
    WORD m_wCountWaveRecordOld;

//     int m_nWaveNo;                      // ��ȡ����¼�����
//     int m_nWaveFrames;                  // ��ȡ����¼��

public:
    virtual void Serialize(CArchive& ar);

public:
    CMyDataFloat* m_pIa;
    CMyDataFloat* m_pIb;
    CMyDataFloat* m_pIc;
    CMyDataFloat* m_pIA;
    CMyDataFloat* m_pIC;
    CMyDataFloat* m_pUa;
    CMyDataFloat* m_pUb;
    CMyDataFloat* m_pIB;
    CMyDataFloat* m_pUc;
    CMyDataFloat* m_pUab;
    CMyDataFloat* m_pUbc;
    CMyDataFloat* m_pUca;
    CMyDataFloat* m_p3I0;
    CMyDataFloat* m_pF;
    CMyDataFloat* m_pP;
    CMyDataFloat* m_pQ;
    CMyDataFloat* m_pPF;

    CMyDataBin* m_pBi[12];
    CMyDataNPSYC* m_pYC[6];

    CMyDataOperate* m_pOP[5];

    CMyDataNPSParam* m_pParam;
    CMyDataNPSRegulate* m_pRegulate;
    CMyDataNPSSetpoint* m_pSetpoint;
    CMyDataOPList* m_pWaveRecordList;

public:
    virtual BOOL OnCreate(void);
    virtual BOOL OnCreateData(CMyData* pData);
    virtual void OnPortOpen(void);
//      virtual void OnPortClose(void){};

public:
    BOOL MODBUS_Read(COMCONTROL* pCC,WORD wBaseAddress,WORD wCountWord);
    BOOL MODBUS_Write(COMCONTROL* pCC,WORD wBaseAddress,WORD wCountWord,WORD* pData);
    BOOL ReadCom(COMCONTROL* pCC, BYTE* pBuff, int nLen);

public:
    void ReceiveInfo(COMCONTROL* pCC);
    void ReceiveParam(COMCONTROL* pCC);
    void ReceiveRegulate(COMCONTROL* pCC);
    void ReceiveSetpoint(COMCONTROL* pCC);
    void ReceiveAnalog(COMCONTROL* pCC);
    void ReceiveWaveRecordHeadList(COMCONTROL* pCC);
    void ReceiveEventTable(COMCONTROL* pCC);
    void TimeSyn(COMCONTROL* pCC);
    BOOL ReceiveWave(COMCONTROL* pCC, int nWaveNo);
    BOOL ReceiveWaveRecordHead(COMCONTROL* pCC, int nWaveNo, WAVERECORD& Waverecord);
    BOOL ReceiveWaveRecordData(COMCONTROL* pCC, int nWaveNo, WAVERECORD& Waverecord);

public:
    void OnEditDeviceParam(CMyDataNPSParam* pDataParam);
    void OnEditRegulate(CMyDataNPSRegulate* pDataRegulate);
    void OnEditSetpoint(CMyDataNPSSetpoint* pDataSetpoint);
    void OnExcuteYC(CMyDataNPSYC* pDataYC);
    void OnOpenList(CMyDataOPList* pOPList);

    CString GetEventText(EVENT& Event);
    CString GetEventTextProtect(WORD wProtectAct, WORD wProtectIndexExt, WORD wActData);
    void SaveWave(WAVERECORD& Waverecord);
    void GetWaveRecordMetrics(int nIndex,CString& strChannelName,float& fFullScale,float& fFullScaleAD,float& fReg);
    void SetWaveInfoAD(CMyWaveInfo& waveinfo,int nChannelNo,CString strChannelName,float fFullScale,float fFullScaleAD,
        int nWaveRecordedDot, int nWaveStartDotNo, WAVERECORD& Waverecord, float fReg);
    WORD GetWaveAIData(short nChIndex, WORD* pwData);
    void SetWaveInfoDI(CMyWaveInfo& waveinfo, int nChannelNo, WORD wMask, int nWaveRecordedDot, int nWaveStartDotNo, WAVERECORD& Waverecord);

};

#endif/*__CMYNPS7510_H*/


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------

