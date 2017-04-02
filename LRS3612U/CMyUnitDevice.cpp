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
#include "CMyUnitModbus.h"
#include "CMyUnitDevice.h"
#include "CMyDlgOpList.h"
#include "CMyDlgParam.h"
#include "CMyDlgRegulate.h"
#include "CMyDlgSetpoint.h"
#include "CMyDlgYK.h"

void RegisterData(void)
{
    CMyData::RegisterClass(_T("LRSYK"), RUNTIME_CLASS(CMyDeviceYK), TRUE);
    CMyData::RegisterClass(_T("LRSList"), RUNTIME_CLASS(CMyDeviceList), TRUE);
    CMyUnit::RegisterClass(_T("LRS3612U"), RUNTIME_CLASS(CMyUnitDevice));
}

//------------------------------- CMyDataPMOPList -----------------------------------
IMPLEMENT_SERIAL(CMyDeviceList,CMyDataOperate,0)

CMyDeviceList::CMyDeviceList():CMyDataOperate()
{
    m_nOPIndex = 0;
}

void CMyDeviceList::RefreshData(CMyOpListArray& arOpList)
{
    int nSize = arOpList.GetSize();
    m_arOPList.RemoveAll();
    for(int i=0;i<nSize;i++)
    {
        m_arOPList.Add(arOpList[i]);
    }
    IncrementUpdateID();
}

void CMyDeviceList::SndCmd(int nOPIndex,BYTE Cmd/*=0xff*/)
{
    m_nOPIndex = nOPIndex;
    m_OperateCode = Cmd;
    IncrementUpdateID();
}

BOOL CMyDeviceList::ExeOperate(void)
{
    ASSERT(m_pParentUnit);
    ASSERT(m_pParentUnit->IsKindOf(RUNTIME_CLASS(CMyUnitDevice)));
    ((CMyUnitDevice*)m_pParentUnit)->OnOpenList(this);
    return TRUE;
}


//---------------------------------------------- CMyDataHN953YK -----------
IMPLEMENT_SERIAL(CMyDeviceYK,CMyDataOperate,0)

CMyDeviceYK::CMyDeviceYK():CMyDataOperate()
{
}

BOOL CMyDeviceYK::ExeOperate(void)
{
    ASSERT(m_pParentUnit);
    ASSERT(m_pParentUnit->IsKindOf(RUNTIME_CLASS(CMyUnitDevice)));
    CMyDlgYK dlg;
    dlg.m_pYK = this;
    MyDoModal(&dlg, MYDLL_MODULE);
    return TRUE;
}

//---------------------------------------------------------------------
#define LOGADDR_DEVICETIME          0x0000      // RW;
#define LOGADDR_DEVICEINFO          0x0007      // R;
#define LOGADDR_ANALOGDATA          0x0100      // R;
#define LOGADDR_ANALOGDATAEXT       0x0200      // R;
#define LOGADDR_ANALOGWAVE          0x0300      // R;
#define LOGADDR_DFTDATASET          0x0900      // R;
#define LOGADDR_CONTROLOUT          0x0a00      // RW;
#define LOGADDR_DEVICEPARAM         0x0b00      // RW;
#define LOGADDR_DEVICEINPARAM       0x0c00      // RW;
#define LOGADDR_DEVICEDCPARAM       0x1100      // RW;
#define LOGADDR_DEVICEREGULATE      0x1300      // RW;
#define LOGADDR_DEVICESETPOINT      0x1400      // RW;
#define LOGADDR_DEVICEDRW           0x1600      // RW;
#define LOGADDR_DEVICELAD           0x1800      // RW;
#define LOGADDR_EVENTTABLE          0x1a00      // R;
#define LOGADDR_WAVERECORD          0x2000      // R;

#define CONTROLOUT_INITDEVICE       0x0000      // ��ʼ���豸;
#define CONTROLOUT_RESETDEVICE      0x0001      // �����ź�;
#define CONTROLOUT_FREEZEWAVE       0x0002      // �������¼��;
#define CONTROLOUT_ADJUST           0x0003      // У��;

#define CONTROLOUT_KH01             0x0010      // KH01;
#define CONTROLOUT_KH02             0x0011      // KH02;
#define CONTROLOUT_KH03             0x0012      // KH03;
#define CONTROLOUT_KH04             0x0013      // KH04;
#define CONTROLOUT_KH05             0x0014      // KH05;
#define CONTROLOUT_KH06             0x0015      // KH06;
#define CONTROLOUT_KH07             0x0016      // KH07;
#define CONTROLOUT_KH08             0x0017      // KH08;
#define CONTROLOUT_KH09             0x0018      // KH09;
#define CONTROLOUT_KH10             0x0019      // KH10;
#define CONTROLOUT_KH11             0x001a      // KH11;
#define CONTROLOUT_KH12             0x001b      // KH12;
#define CONTROLOUT_KH13             0x001c      // KH13;
#define CONTROLOUT_KH14             0x001d      // KH14;
#define CONTROLOUT_KH15             0x001e      // KH15;
#define CONTROLOUT_KH16             0x001f      // KH16;
#define CONTROLOUT_KH17             0x0020      // KH17;
#define CONTROLOUT_KH18             0x0021      // KH18;
#define CONTROLOUT_KH19             0x0022      // KH19;
#define CONTROLOUT_KH20             0x0023      // KH20;
#define CONTROLOUT_KH21             0x0024      // KH21;
#define CONTROLOUT_KH22             0x0025      // KH22;
#define CONTROLOUT_KH23             0x0026      // KH23;
#define CONTROLOUT_KH24             0x0027      // KH24;
#define CONTROLOUT_KH25             0x0028      // KH25;
#define CONTROLOUT_KH26             0x0029      // KH26;
#define CONTROLOUT_KH27             0x002a      // KH27;
#define CONTROLOUT_KH28             0x002b      // KH28;
#define CONTROLOUT_KH29             0x002c      // KH29;
#define CONTROLOUT_KH30             0x002d      // KH30;
#define CONTROLOUT_KH31             0x002e      // KH31;
#define CONTROLOUT_KH32             0x002f      // KH32;

typedef struct _DEVICEINFO
{
    WORD wDeviceType;					// �豸���ʹ���
    WORD wSwitchStatus1;				// ������״̬ 0~15
    WORD wSwitchStatus2;				// ������״̬16~31
    // --------------------��Ҫ����---------------------------------
    WORD wNumPwrup;						// �������� Number of Power ups
    WORD wWrmStr;						// �������� Number of Warm Starts
    WORD wDeviceStatus1;				// �Լ���Ϣ
    WORD wDeviceStatus2;
    // ------------------------------------------------------------
    WORD wDeviceStatus3;
    WORD wDeviceStatus4;
    WORD wExtID;
    WORD wSelfTestMain;					// ���洢���Լ���Ϣ
    WORD wSelfTestSub;					// �Ӵ洢���Լ���Ϣ
    WORD wCountAll;
    WORD wCountEventTable;
    WORD wCountWaveRecord;
    WORD wCountDeviceParam;
    WORD wCountDeviceRegulate;
    WORD wCountDeviceSetpoint;
    WORD wMainVersion;
    WORD wSubVersion;
    WORD wLCDHeigh;
    WORD wLCDWidth;
    WORD wCRC;
}tDEVICEINFO;

typedef struct
{
    WORD wDataIa;
    WORD wDataIb;
    WORD wDataIc;
    WORD wDataIA;
    WORD wDataIB;
    WORD wDataIC;
	WORD wDataI0;
    WORD wDataUa;
    WORD wDataUb;
    WORD wDataUc;
    WORD wDataUx;
    WORD wDataUab;
    WORD wDataUbc;
    WORD wDataUca;
    WORD wDataF;
    short nDataP;
    short nDataQ;
    short nDataS;
    short nDataPF;
    short nAngIa;
    short nAngIb;
    short nAngIc;
    short nAngIA;
    short nAngIB;
    short nAngIC;
    short nAngI0;
    short nAngUa;
    short nAngUb;
    short nAngUc;
    short nAngUab;
    short nAngUbc;
    short nAngUca;
    short nAngUx;
}tANALOGDATA;

typedef struct
{
    DWORD dwDataPhImp;
    DWORD dwDataQhImp;
    DWORD dwDataPhExp;
    DWORD dwDataQhExp;
    DWORD dwDataPhImpW10ms;
    DWORD dwDataQhImpW10ms;
    DWORD dwDataPhExpW10ms;
    DWORD dwDataQhExpW10ms;
}tANALOGDATAEXT;

typedef struct
{
    char* czField;
    char* czName;
    char* czStatus0;
    char* czStatus1;
}tBIINFO;

static const tBIINFO s_BIInfo[] = 
{
    {_T("IN1"), _T("�����غ�բ/����˹"), "��λ", "��λ"},
    {_T("IN2"), _T("����δ����"), "��λ", "��λ"},
    {_T("IN3"), _T("����3/����˹"), "��λ", "��λ"},
    {_T("IN4"), _T("����4/������բ"), "��λ", "��λ"},
    {_T("IN5"), _T("����5/�¸߸澯"), "��λ", "��λ"},
    {_T("IN6"), _T("С������λ��"), "��λ", "��λ"},
    {_T("IN7"), _T("С������λ��"), "��λ", "��λ"},
    {_T("IN8"), _T("�ӵص�բλ��"), "��λ", "��λ"},
    {_T("IN9"), _T("Զ������"), "��λ", "��λ"},
    {_T("IN10"), _T("HWJ"), "��λ", "��λ"},
    {_T("IN11"), _T("TWJ"), "��λ", "��λ"},
    {_T("IN12"), _T("�ֶ���ң����բ"), "��λ", "��λ"},
    {_T("IN13"), _T("�ֶ���ң�غ�բ"), "��λ", "��λ"},
    {_T("CBERR"), _T("���ƻ�·����"), "��λ", "��λ"},
    {_T("TRIP"), _T("�¹���"), "��λ", "��λ"},
    {_T("ALARM"), _T("�澯��"), "��λ", "��λ"},
    {_T("ERR"), _T("�Լ�"), "��λ", "��λ"},
};
static const int s_nBINum = sizeof(s_BIInfo)/sizeof(tBIINFO);

#define SWITCHCNT           13

typedef struct
{
    char* czField;
    char* czName;
    char* czUnit;
    BYTE Format;
    BYTE AngFormat;
    short nDisplayType;
}tVECTORINFO;

static const tVECTORINFO s_VectorInfo[] = 
{
    {_T("Ia"), _T("A���������"), _T("A"), 0x03, 0x01, 1},
    {_T("Ib"), _T("B���������"), _T("A"), 0x03, 0x01, 1},
    {_T("Ic"), _T("C���������"), _T("A"), 0x03, 0x01, 1},
    {_T("IA"), _T("A�ౣ������"), _T("A"), 0x02, 0x01, 1},
    {_T("IB"), _T("B�ౣ������"), _T("A"), 0x02, 0x01, 1},
    {_T("IC"), _T("C�ౣ������"), _T("A"), 0x02, 0x01, 1},
	{_T("I0"), _T("���򱣻�����"), _T("A"), 0x02, 0x01, 1},
    {_T("Ua"), _T("A���ѹ"), _T("V"), 0x02, 0x01, 1},
    {_T("Ub"), _T("B���ѹ"), _T("V"), 0x02, 0x01, 1},
    {_T("Uc"), _T("C���ѹ"), _T("V"), 0x02, 0x01, 1},
    {_T("Ux"), _T("��ȡ��ѹ"), _T("V"), 0x02, 0x01, 1},
    {_T("Uab"), _T("AB�ߵ�ѹ"), _T("V"), 0x02, 0x01, 1},
    {_T("Ubc"), _T("BC�ߵ�ѹ"), _T("V"), 0x02, 0x01, 1},
    {_T("Uca"), _T("CA�ߵ�ѹ"), _T("V"), 0x02, 0x01, 1},
};
static const int s_nVectorNum = sizeof(s_VectorInfo)/sizeof(tVECTORINFO);

enum AIINDEX
{
    AI_Ia = 0,
	AI_Ib,
    AI_Ic,
    AI_IA,
    AI_IB,
    AI_IC,
	AI_I0,
    AI_Ua,
    AI_Ub,
    AI_Uc,
    AI_Ux,
    AI_Uab,
    AI_Ubc,
    AI_Uca,
    AI_Epimp = 0,
    AI_Eqimp,
    AI_Epexp,
    AI_Eqexp,
};

typedef struct
{
    char* czField;
    char* czName;
    char* czUnit;
    BYTE Format;
}tAIINFO;

static const tAIINFO s_AIInfo[] = 
{
    {_T("Ep+"), _T("�����й����"), _T("kWh"), 0x01},
    {_T("Eq+"), _T("�����޹����"), _T("kVar"), 0x01},
    {_T("Ep-"), _T("�����й����"), _T("kWh"), 0x01},
    {_T("Eq-"), _T("�����޹����"), _T("kVar"), 0x01},
};
static const int s_nAINum = sizeof(s_AIInfo)/sizeof(tAIINFO);

typedef struct
{
    char* czField;
    char* czName;
}tYKINFO;

static const tYKINFO s_YKInfo[] = 
{
    {_T("TZ"), _T("��բ")},
    {_T("HZ"), _T("��բ")},
    {_T("YT"), _T("ң��")},
    {_T("YH"), _T("ң��")},
    {_T("T1D"), _T("��������")},
    {_T("T2D"), _T("�����澯")},
};
static const int s_nYKNum = sizeof(s_YKInfo)/sizeof(tYKINFO);

enum MemType
{
    MTP_Param = 0,
    MTP_Regulate,
    MTP_Setpoint,
    MTP_Max,
};

//---------------------------------------------- CMyUnitHN953L -----------------------
IMPLEMENT_SERIAL(CMyUnitDevice, CMyUnitModbus, 0)

CMyUnitDevice::CMyUnitDevice():CMyUnitModbus(),
    m_fScaleIM(6.0f), m_fScaleIP(100.0f), m_fScaleUll(120.0f)
{
    m_bInfoOK = FALSE;
    m_bTimeSyn = FALSE;
    m_bParamOK = FALSE;
    m_bRegulateOK = FALSE;
    m_bSetpointOK = FALSE;
    m_bWaveRecordListOK = FALSE;
    m_nTask = 0;

    m_wCountParam = 0;
    m_wCountParamOld = 0;
    m_wCountRegulate = 0;
    m_wCountRegulateOld = 0;
    m_wCountSetpoint = 0;
    m_wCountSetpointOld = 0;
    m_wCountWaveRecord = 0;
    m_wCountWaveRecordOld = 0;
}

CMyUnitDevice::~CMyUnitDevice()
{
}

BOOL CMyUnitDevice::OnCreate(void)
{
    int i;
    CMyUnitModbus::OnCreate();

    AddDataFactory(RUNTIME_CLASS(CMyDataString), _T("CRCInfo"));

    for(i=0;i<s_nBINum;++i) AddDataFactory(RUNTIME_CLASS(CMyDataBin), s_BIInfo[i].czField);
    for(i=0;i<s_nVectorNum;++i) AddDataFactory(RUNTIME_CLASS(CMyDataVector), s_VectorInfo[i].czField);
    for(i=0;i<s_nAINum;++i) AddDataFactory(RUNTIME_CLASS(CMyDataFloat), s_AIInfo[i].czField);
    for(i=0;i<s_nYKNum;++i) AddDataFactory(RUNTIME_CLASS(CMyDeviceYK), s_YKInfo[i].czField);

    AddDataFactory(RUNTIME_CLASS(CMyDataOperate), _T("InitDev"));
    AddDataFactory(RUNTIME_CLASS(CMyDataOperate), _T("ResetDev"));
    AddDataFactory(RUNTIME_CLASS(CMyDataOperate), _T("FreezeWaveRecord"));
    AddDataFactory(RUNTIME_CLASS(CMyDataOperate), _T("Adjust"));
    AddDataFactory(RUNTIME_CLASS(CMyDataOperate), _T("TimeSyn"));

    AddDataFactory(RUNTIME_CLASS(CMyDataMem), _T("Param"));
    AddDataFactory(RUNTIME_CLASS(CMyDataMem), _T("Regulate"));
    AddDataFactory(RUNTIME_CLASS(CMyDataMem), _T("Setpoint"));
    AddDataFactory(RUNTIME_CLASS(CMyDeviceList), _T("WaveRecordList"));

    return TRUE;
}

BOOL CMyUnitDevice::OnCreateData(CMyData* pData)
{
    int i;
    CMyUnitModbus::OnCreateData(pData);

    if(pData->m_strField==_T("CRCInfo"))
    {
        ((CMyDataString*)pData)->Initialize(_T("CRC��Ϣ"));
        return TRUE;
    }

    for(i=0;i<s_nBINum;++i)
    {
        if(pData->m_strField==s_BIInfo[i].czField)
        {
            ((CMyDataBin*)pData)->Initialize(s_BIInfo[i].czName);
            return TRUE;
        }
    }

    for(i=0;i<s_nVectorNum;++i)
    {
        if(pData->m_strField==s_VectorInfo[i].czField)
        {
            ((CMyDataVector*)pData)->Initialize(s_VectorInfo[i].czName, s_VectorInfo[i].czUnit,
                s_VectorInfo[i].Format, s_VectorInfo[i].AngFormat, s_VectorInfo[i].nDisplayType);
            return TRUE;
        }
    }

    for(i=0;i<s_nAINum;++i)
    {
        if(pData->m_strField==s_AIInfo[i].czField)
        {
            ((CMyDataFloat*)pData)->Initialize(s_AIInfo[i].czName, s_AIInfo[i].czUnit, s_AIInfo[i].Format);
            return TRUE;
        }
    }

    for(i=0;i<s_nYKNum;++i)
    {
        if(pData->m_strField==s_YKInfo[i].czField)
        {
            ((CMyDeviceYK*)pData)->Initialize(s_YKInfo[i].czName);
            return TRUE;
        }
    }

    if(pData->m_strField==_T("InitDev"))
    {
        ((CMyDataOperate*)pData)->Initialize("�豸��ʼ��");
        return TRUE;
    }

    if(pData->m_strField==_T("ResetDev"))
    {
        ((CMyDataOperate*)pData)->Initialize("�豸����");
        return TRUE;
    }

    if(pData->m_strField==_T("FreezeWaveRecord"))
    {
        ((CMyDataOperate*)pData)->Initialize("�ֶ�¼��");
        return TRUE;
    }
    
    if(pData->m_strField==_T("Adjust"))
    {
        ((CMyDataOperate*)pData)->Initialize(_T("У��"));
        return TRUE;
    }

    if(pData->m_strField==_T("TimeSyn"))
    {
        ((CMyDataOperate*)pData)->Initialize(_T("Уʱ"));
        return TRUE;
    }

    if(pData->m_strField==_T("Param"))
    {
        ((CMyDataMem*)pData)->Initialize("�༭�豸����", MTP_Param, sizeof(tDEVICEPARAM));
        return TRUE;
    }

    if(pData->m_strField==_T("Regulate"))
    {
        ((CMyDataMem*)pData)->Initialize("�༭У��ϵ��", MTP_Regulate, sizeof(tREGULATE)*DFT_CHANNEL_HARD);
        return TRUE;
    }

    if(pData->m_strField==_T("Setpoint"))
    {
        ((CMyDataMem*)pData)->Initialize("�༭������ֵ", MTP_Setpoint, sizeof(tDEVICESETPOINT));
        return TRUE;
    }

    if(pData->m_strField==_T("WaveRecordList"))
    {
        ((CMyDeviceList*)pData)->Initialize("����¼���б�");
        return TRUE;
    }

    return TRUE;
}

void CMyUnitDevice::OnPortOpen(void)
{
    int i;
    CMyUnitModbus::OnPortOpen();

    m_pCRCInfo = (CMyDataString*)GetData(_T("CRCInfo"));

    for(i=0;i<s_nBINum;++i)
    {
         m_pBI[i] = (CMyDataBin*)GetData(s_BIInfo[i].czField);
    }

    for(i=0;i<s_nVectorNum;++i)
    {
        m_pVector[i] = (CMyDataVector*)GetData(s_VectorInfo[i].czField);
    }

    for(i=0;i<s_nAINum;++i)
    {
        m_pFloat[i] = (CMyDataFloat*)GetData(s_AIInfo[i].czField);
    }

    for(i=0;i<s_nYKNum;++i)
    {
        m_pYK[i] = (CMyDeviceYK*)GetData(s_YKInfo[i].czField);
    }

    m_pInitDev = (CMyDataOperate*)GetData(_T("InitDev"));
    m_pResetDev = (CMyDataOperate*)GetData(_T("ResetDev"));
    m_pFreezeRecord = (CMyDataOperate*)GetData(_T("FreezeWaveRecord"));
    m_pAdjust = (CMyDataOperate*)GetData(_T("Adjust"));
    m_pTimesyn = (CMyDataOperate*)GetData(_T("TimeSyn"));

    m_pParam = (CMyDataMem*)GetData(_T("Param"));
    m_pRegulate = (CMyDataMem*)GetData(_T("Regulate"));
    m_pSetpoint = (CMyDataMem*)GetData(_T("Setpoint"));
    m_pWaveRecordList = (CMyDeviceList*)GetData(_T("WaveRecordList"));
}

void CMyUnitDevice::ExchangeComData(COMCONTROL* pCC)
{
    int i;
    if(!m_bInfoOK) { ReceiveInfo(pCC); return; }
    if(!m_bTimeSyn) { TimeSyn(pCC); return; }
    if(!m_bParamOK) { ReceiveParam(pCC); return; }
    if(!m_bRegulateOK) { ReceiveRegulate(pCC); return; }
    if(!m_bSetpointOK) { ReceiveSetpoint(pCC); return; }
    if(!m_bWaveRecordListOK) { ReceiveWaveRecordHeadList(pCC); return; }

    if(m_wCountParam!=m_wCountParamOld)
    {
        ReceiveParam(pCC);
        return;
    }

    if(m_wCountRegulate!=m_wCountRegulateOld)
    {
        ReceiveRegulate(pCC);
        return;
    }

    if(m_wCountSetpoint!=m_wCountSetpointOld)
    {
        ReceiveSetpoint(pCC);
        return;
    }

    for(i=0;i<s_nYKNum;i++)
    {
        if(m_pYK[i])
        {
            BYTE Code = m_pYK[i]->GetOperateCode();
            WORD wCode = Code*0x0101;
            if(wCode)
            {
                MODBUS_Write(pCC,LOGADDR_CONTROLOUT+CONTROLOUT_KH01+i,1,&wCode);
                m_pYK[i]->EndOperate();
            }
        }
    }

    if(m_pInitDev && m_pInitDev->GetOperateCode()==0xff)
    {
        MODBUS_Write(pCC, LOGADDR_CONTROLOUT+CONTROLOUT_INITDEVICE, 0xaaaa);
        m_pInitDev->EndOperate();
        return;
    }

    if(m_pResetDev && m_pResetDev->GetOperateCode()==0xff)
    {
        MODBUS_Write(pCC, LOGADDR_CONTROLOUT+CONTROLOUT_RESETDEVICE, 0xaaaa);
        m_pResetDev->EndOperate();
        return;
    }

    if(m_pFreezeRecord && m_pFreezeRecord->GetOperateCode()==0xff)
    {
        MODBUS_Write(pCC, LOGADDR_CONTROLOUT+CONTROLOUT_FREEZEWAVE, 0xaaaa);
        m_pFreezeRecord->EndOperate();
        return;
    }

    if(m_pAdjust && m_pAdjust->GetOperateCode()==0xff)
    {
        MODBUS_Write(pCC, LOGADDR_CONTROLOUT+CONTROLOUT_ADJUST, 0xaaaa);
        m_pAdjust->EndOperate();
    }
    
    if(m_pTimesyn && m_pTimesyn->GetOperateCode()==0xff)
    {
        TimeSyn(pCC);
        m_pTimesyn->EndOperate();
    }

    if(m_pParam && m_pParam->GetOperateCode()==0xff)
    {
        MODBUS_Write(pCC, LOGADDR_DEVICEPARAM, m_pParam->m_nSize/sizeof(WORD), (WORD*)m_pParam->m_pMemW);
        m_pParam->EndOperate();
        Sleep(100);
        return;
    }

    if(m_pRegulate && m_pRegulate->GetOperateCode()==0xff)
    {
        MODBUS_Write(pCC, LOGADDR_DEVICEREGULATE, m_pRegulate->m_nSize/sizeof(WORD), (WORD*)m_pRegulate->m_pMemW);
        m_pRegulate->EndOperate();
        Sleep(100);
        return;
    }

    if(m_pSetpoint && m_pSetpoint->GetOperateCode()==0xff)
    {
        MODBUS_Write(pCC, LOGADDR_DEVICESETPOINT, m_pSetpoint->m_nSize/sizeof(WORD), (WORD*)m_pSetpoint->m_pMemW);
        m_pSetpoint->EndOperate();
        Sleep(100);
        return;
    }

    if(m_wCountWaveRecordOld!=m_wCountWaveRecord)
    {
        ReceiveWaveRecordHeadList(pCC);
        m_wCountWaveRecordOld = m_wCountWaveRecord;
        return;
    }

    if(m_pWaveRecordList && m_pWaveRecordList->GetOperateCode())
    {
        //         int nWaveNo = m_pWaveRecordList->m_arOPList[m_pWaveRecordList->m_nOPIndex].nIndex;
        int nWaveNo = m_pWaveRecordList->m_nOPIndex;
        ReceiveWave(pCC, nWaveNo);
        m_pWaveRecordList->EndOperate();
        return;
    }

    switch(m_nTask)
    {
    case 0: ReceiveInfo(pCC); break;
    case 1: ReceiveAnalog(pCC); break;
    case 2: ReceiveAnalogExt(pCC); break;
    case 3: ReceiveEventTable(pCC); break;
    }
    m_nTask = (++m_nTask)%4;
}

void CMyUnitDevice::ReceiveInfo(COMCONTROL* pCC)
{
    int i;
    tDEVICEINFO deviceInfo;
    if(MODBUS_Read(pCC, LOGADDR_DEVICEINFO, (sizeof(tDEVICEINFO)/sizeof(WORD)), (WORD*)&deviceInfo)) return;
//     CopyByte2WORDHL((WORD*)&deviceInfo, pCCRX+3, sizeof(tDEVICEINFO)/sizeof(WORD));
    if(deviceInfo.wDeviceType!=7510)
    {
        AddEvent(_T("�豸���Ͳ�ƥ��!"));
        return;
    }
    
    WORD wMask = 0x01;
    for(i=0; i<13; i++, wMask = wMask<<1)
    {
        if(m_pBI[i]) m_pBI[i]->RefreshData((deviceInfo.wSwitchStatus1&wMask)?1:0);
    }
    if(m_pBI[13]) m_pBI[13]->RefreshData((deviceInfo.wSwitchStatus1&0x0600)?0:1);
    if(m_pBI[14]) m_pBI[14]->RefreshData((deviceInfo.wDeviceStatus1&0x0002)?1:0);
    if(m_pBI[15]) m_pBI[15]->RefreshData((deviceInfo.wDeviceStatus1&0x0001)?1:0);
    if(m_pBI[16]) m_pBI[16]->RefreshData((deviceInfo.wDeviceStatus1&0xfffc)?1:0);

    CString strCRC;
    strCRC.Format(_T("0x%4X"), deviceInfo.wCRC);
    if(m_pCRCInfo) m_pCRCInfo->RefreshData(strCRC);

    m_wCountParam = deviceInfo.wCountDeviceParam;
    m_wCountRegulate = deviceInfo.wCountDeviceRegulate;
    m_wCountSetpoint = deviceInfo.wCountDeviceSetpoint;
    m_wCountWaveRecord = deviceInfo.wCountWaveRecord;
    if(m_bInfoOK==FALSE)
    {
        m_wCountParamOld = deviceInfo.wCountDeviceParam;
        m_wCountRegulateOld = deviceInfo.wCountDeviceRegulate;
        m_wCountSetpointOld = deviceInfo.wCountDeviceSetpoint;
        m_wCountWaveRecordOld = deviceInfo.wCountWaveRecord;
    }
    
    m_bInfoOK = TRUE;
}

void CMyUnitDevice::TimeSyn(COMCONTROL* pCC)
{
    CTime timeNow = CTime::GetCurrentTime();
    if(timeNow.GetYear()<2000) return;
    WORD wTime[7];
    wTime[0] = WORD(timeNow.GetYear()-2000);
    wTime[1] = WORD(timeNow.GetMonth());
    wTime[2] = WORD(timeNow.GetDay());
    wTime[3] = WORD(timeNow.GetHour());
    wTime[4] = WORD(timeNow.GetMinute());
    wTime[5] = WORD(timeNow.GetSecond());
    wTime[6] = 0;
    DWORD dwAddressDest = m_nAddr;
    m_nAddr = 0;
    MODBUS_Write(pCC, LOGADDR_DEVICETIME, 7, wTime);
    m_nAddr = dwAddressDest;
    m_bTimeSyn = TRUE;
}

void CMyUnitDevice::ReceiveParam(COMCONTROL* pCC)
{
    tDEVICEPARAM deviceParam;
    if(MODBUS_Read(pCC, LOGADDR_DEVICEPARAM, (sizeof(tDEVICEPARAM)/sizeof(WORD)), (WORD*)&deviceParam)) return;

    if(m_pParam) m_pParam->RefreshData(&deviceParam);

    m_wCountParamOld = m_wCountParam;
    m_bParamOK = TRUE;
}

void CMyUnitDevice::ReceiveRegulate(COMCONTROL* pCC)
{
    tREGULATE Regulate[DFT_CHANNEL_HARD];
    if(MODBUS_Read(pCC, LOGADDR_DEVICEREGULATE, (sizeof(tREGULATE)/sizeof(WORD))*DFT_CHANNEL_HARD, (WORD*)&Regulate[0])) return;
    
    if(m_pRegulate) m_pRegulate->RefreshData(&Regulate);
    
    m_wCountRegulateOld = m_wCountRegulate;
    m_bRegulateOK = TRUE;
}

void CMyUnitDevice::ReceiveSetpoint(COMCONTROL* pCC)
{
    tDEVICESETPOINT Setpoint;
    if(MODBUS_Read(pCC, LOGADDR_DEVICESETPOINT, (sizeof(tDEVICESETPOINT)/sizeof(WORD)), (WORD*)&Setpoint)) return;
    
    if(m_pSetpoint) m_pSetpoint->RefreshData(&Setpoint);
    
    m_wCountSetpointOld = m_wCountSetpoint;
    m_bSetpointOK = TRUE;
}

void CMyUnitDevice::ReceiveAnalog(COMCONTROL* pCC)
{
    tANALOGDATA Analog;
    if(MODBUS_Read(pCC, LOGADDR_ANALOGDATA, (sizeof(tANALOGDATA)/sizeof(WORD)), (WORD*)&Analog)) return;
//     CopyByte2WORDHL((WORD*)&Analog, pCCRX+3, sizeof(tANALOGDATA)/sizeof(WORD));
    CMyVector Vec;
    Vec.SetPolar(GetAIFloat(m_fScaleIM, Analog.wDataIa), bcg_deg2rad(GetAIFloat((BYTE)0x01, Analog.nAngIa)));
    if(m_pVector[AI_Ia]) m_pVector[AI_Ia]->RefreshData(Vec);
    Vec.SetPolar(GetAIFloat(m_fScaleIM, Analog.wDataIb), bcg_deg2rad(GetAIFloat((BYTE)0x01, Analog.nAngIb)));
    if(m_pVector[AI_Ib]) m_pVector[AI_Ib]->RefreshData(Vec);
    Vec.SetPolar(GetAIFloat(m_fScaleIM, Analog.wDataIc), bcg_deg2rad(GetAIFloat((BYTE)0x01, Analog.nAngIc)));
    if(m_pVector[AI_Ic]) m_pVector[AI_Ic]->RefreshData(Vec);
    Vec.SetPolar(GetAIFloat(m_fScaleIP, Analog.wDataIA), bcg_deg2rad(GetAIFloat((BYTE)0x01, Analog.nAngIA)));

    if(m_pVector[AI_IA]) m_pVector[AI_IA]->RefreshData(Vec);
    Vec.SetPolar(GetAIFloat(m_fScaleIP, Analog.wDataIB), bcg_deg2rad(GetAIFloat((BYTE)0x01, Analog.nAngIB)));
    if(m_pVector[AI_IB]) m_pVector[AI_IB]->RefreshData(Vec);
    Vec.SetPolar(GetAIFloat(m_fScaleIP, Analog.wDataIC), bcg_deg2rad(GetAIFloat((BYTE)0x01, Analog.nAngIC)));
    if(m_pVector[AI_IC]) m_pVector[AI_IC]->RefreshData(Vec);

    Vec.SetPolar(GetAIFloat(m_fScaleIP, Analog.wDataI0), bcg_deg2rad(GetAIFloat((BYTE)0x01, Analog.nAngI0)));
    if(m_pVector[AI_I0]) m_pVector[AI_I0]->RefreshData(Vec);

    Vec.SetPolar(GetAIFloat(m_fScaleUll, Analog.wDataUa), bcg_deg2rad(GetAIFloat((BYTE)0x01, Analog.nAngUa)));
    if(m_pVector[AI_Ua]) m_pVector[AI_Ua]->RefreshData(Vec);
    Vec.SetPolar(GetAIFloat(m_fScaleUll, Analog.wDataUb), bcg_deg2rad(GetAIFloat((BYTE)0x01, Analog.nAngUb)));
    if(m_pVector[AI_Ub]) m_pVector[AI_Ub]->RefreshData(Vec);
    Vec.SetPolar(GetAIFloat(m_fScaleUll, Analog.wDataUc), bcg_deg2rad(GetAIFloat((BYTE)0x01, Analog.nAngUc)));
    if(m_pVector[AI_Uc]) m_pVector[AI_Uc]->RefreshData(Vec);
    Vec.SetPolar(GetAIFloat(m_fScaleUll, Analog.wDataUx), bcg_deg2rad(GetAIFloat((BYTE)0x01, Analog.nAngUx)));
    if(m_pVector[AI_Ux]) m_pVector[AI_Ux]->RefreshData(Vec);

    Vec.SetPolar(GetAIFloat(m_fScaleUll, Analog.wDataUab), bcg_deg2rad(GetAIFloat((BYTE)0x01, Analog.nAngUab)));
    if(m_pVector[AI_Uab]) m_pVector[AI_Uab]->RefreshData(Vec);
    Vec.SetPolar(GetAIFloat(m_fScaleUll, Analog.wDataUbc), bcg_deg2rad(GetAIFloat((BYTE)0x01, Analog.nAngUbc)));
    if(m_pVector[AI_Ubc]) m_pVector[AI_Ubc]->RefreshData(Vec);
    Vec.SetPolar(GetAIFloat(m_fScaleUll, Analog.wDataUca), bcg_deg2rad(GetAIFloat((BYTE)0x01, Analog.nAngUca)));
    if(m_pVector[AI_Uca]) m_pVector[AI_Uca]->RefreshData(Vec);

//     Vec.SetPolar(GetAIFloat(m_fScaleIP, Analog.wDataIL1), bcg_deg2rad(GetAIFloat((BYTE)0x01, Analog.nAngIL1)));
//     if(m_pVector[AI_IL1]) m_pVector[AI_IL1]->RefreshData(Vec);
//     Vec.SetPolar(GetAIFloat(m_fScaleIM, Analog.wDataIL2), bcg_deg2rad(GetAIFloat((BYTE)0x01, Analog.nAngIL2)));
//     if(m_pVector[AI_IL2]) m_pVector[AI_IL2]->RefreshData(Vec);
}

void CMyUnitDevice::ReceiveAnalogExt(COMCONTROL* pCC)
{
    tANALOGDATAEXT AnalogExt;
    if(MODBUS_Read(pCC, LOGADDR_ANALOGDATAEXT, (sizeof(tANALOGDATAEXT)/sizeof(WORD)), (WORD*)&AnalogExt)) return;
//     CopyByte2WORDHL((WORD*)&AnalogExt, pCCRX+3, sizeof(tANALOGDATAEXT)/sizeof(WORD));
    if(m_pFloat[AI_Epimp]) m_pFloat[AI_Epimp]->RefreshData(AnalogExt.dwDataPhImp*0.1f);
    if(m_pFloat[AI_Eqimp]) m_pFloat[AI_Eqimp]->RefreshData(AnalogExt.dwDataQhImp*0.1f);
    if(m_pFloat[AI_Epexp]) m_pFloat[AI_Epexp]->RefreshData(AnalogExt.dwDataPhExp*0.1f);
    if(m_pFloat[AI_Eqexp]) m_pFloat[AI_Eqexp]->RefreshData(AnalogExt.dwDataQhExp*0.1f);
}

enum PROTRCTCODE
{
    PROTECT_DL1 = 0,           // ����I��;			0
    PROTECT_DL2,               // ����II��;			1
    PROTECT_DL3,               // ����III��;		2
    PROTECT_LX1,               // ����I��;			3
    PROTECT_LX2,               // ����II��			4
    PROTECT_GFH,               // ������			5
    PROTECT_DDY,               // �͵�ѹ;			6
    PROTECT_CHZ,               // �غ�բ;			7
    PROTECT_HJS,               // �����;			8
    PROTECT_MAX1
};

enum PROTECTCODE
{
    PROTECT_IN1 = PROTECT_MAX1,
    PROTECT_IN2,
    PROTECT_IN3,
    PROTECT_IN4,
    PROTECT_MAX
};

enum
{
    PROTECTACT_NULL = 0,
    PROTECTACT_IP,
    PROTECTACT_U,
};

typedef struct
{
    const char* pszName;
    WORD wAct;
}PROTECTACTINFO;

static const PROTECTACTINFO c_protectActInfo[PROTECT_MAX1] = 
{
    {_T("�������"),   PROTECTACT_IP},
    {_T("�������"),  PROTECTACT_IP},
    {_T("�������"),  PROTECTACT_IP},
    {_T("�������"), PROTECTACT_IP},
    {_T("�������"), PROTECTACT_IP},
    {_T("������"), PROTECTACT_IP},
    {_T("�͵�ѹ"), PROTECTACT_U},
    {_T("�غ�բ"), PROTECTACT_NULL},
    {_T("�����"),   PROTECTACT_IP},
};

const char* g_pszINSETName[] =
{
    "����˹",
	"����˹",
	"������բ",
	"�¸߸澯",
};

// static const char* g_pszDoName[] =
// {
//     "J1",
//     "J2",
// };

#define EVENTCODE_ALARMPT3		(EVENTCODE_ALARMED+0x00)	//����PT����;
#define EVENTCODE_ALARMPT2		(EVENTCODE_ALARMED+0x01)	//����PT����;
#define EVENTCODE_ALARMPT1		(EVENTCODE_ALARMED+0x02)	//����PT����;
#define EVENTCODE_ALARMKM		(EVENTCODE_ALARMED+0x03)    //���ƻ�·����;

CString CMyUnitDevice::GetEventText(tEVENT& Event)
{
    CString strEventText = "";
//     if(Event.wCode>=EVENTCODE_REMOTE && Event.wCode<EVENTCODE_REMOTE+2)
//     {
//         strEventText += g_pszDoName[Event.wCode-EVENTCODE_REMOTE];
//         strEventText += _T("->");
//         strEventText += _T("ң�س���");
//     }
    if(Event.wCode>=EVENTCODE_SWITCH && Event.wCode<EVENTCODE_SWITCH+SWITCHCNT)
    {
        WORD wIndex = Event.wCode - EVENTCODE_SWITCH;
        strEventText += s_BIInfo[wIndex].czName;
        strEventText += "->";
        strEventText += (Event.wData==0)?s_BIInfo[wIndex].czStatus0:s_BIInfo[wIndex].czStatus1;
    }
    if(Event.wCode>=EVENTCODE_PROTECT && Event.wCode<EVENTCODE_PROTECT+256)
    {
        WORD wProtectIndexExt = (WORD)(Event.wCode-EVENTCODE_PROTECT);
        WORD wProtectIndex = wProtectIndexExt&0x001f;
        if(c_protectActInfo[wProtectIndex].pszName)
        {
            strEventText += c_protectActInfo[wProtectIndex].pszName;
            strEventText += _T("��������");
            if(Event.wData!=0xffff)
            {
                strEventText +=  GetEventTextProtect(c_protectActInfo[wProtectIndex].wAct, wProtectIndexExt, Event.wData);
            }
        }
    }
    if(Event.wCode>=EVENTCODE_PROTECT+PROTECT_IN1 && Event.wCode<EVENTCODE_PROTECT+PROTECT_MAX)
    {
        WORD wProtectIndexExt = Event.wCode-EVENTCODE_PROTECT-PROTECT_IN1;
        strEventText += ((char*)g_pszINSETName[wProtectIndexExt]);
        strEventText += ("��������");
    }
    switch(Event.wCode)
    {
    case EVENTCODE_ALARMPT3: strEventText = "����PT����" + (Event.wData==0)?"":"�ָ�";
    case EVENTCODE_ALARMPT2: strEventText = "����PT����" + (Event.wData==0)?"":"�ָ�";
    case EVENTCODE_ALARMPT1: strEventText = "����PT����" + (Event.wData==0)?"":"�ָ�";
    case EVENTCODE_ALARMKM: strEventText = "���ƻ�·����" + (Event.wData==0)?"":"�ָ�";
    }
    return strEventText;
}

CString CMyUnitDevice::GetEventTextProtect(WORD wProtectAct, WORD wProtectIndexExt, WORD wActData)
{
    CString strText = "";
    switch(wProtectAct)
    {
    case PROTECTACT_IP: strText.Format(",I=%.2fA", wActData*0.0333333f); break;
//     case PROTECTACT_3I0: strText.Format(",3I0=%.2fA", wActData*0.0333333f); break;
    case PROTECTACT_U: strText.Format(",U=%.2fV", wActData*0.04f); break;
    }
    return strText;
}

void CMyUnitDevice::ReceiveEventTable(COMCONTROL* pCC)
{
    tEVENT Event;
    while(MODBUS_Read(pCC, LOGADDR_EVENTTABLE, sizeof(tEVENT)/sizeof(short), (WORD*)&Event)==COMERR_NoErr)
    {
        EVTMSG EventMsg;
        EventMsg.wYear = Event.time.wYear + 2000;
        EventMsg.Mon = Event.time.wMonth;
        EventMsg.Day = Event.time.wDay;
        EventMsg.Hour = Event.time.wHour;
        EventMsg.Min = Event.time.wMinute;
        EventMsg.Sec = Event.time.wSecond;
        EventMsg.wMs = Event.time.wMilliSecond;
        EventMsg.strContent = GetEventText(Event);
        EventMsg.clrColor = RGB(255,0,0);
        g_MngEvent.SndMsg(EventMsg);
    }
}

void CMyUnitDevice::OnEditMem(const CMyDataMem& Mem)
{
    switch(Mem.m_nID)
    {
    case MTP_Param:
        {
            CMyDlgParam dlg;
            dlg.m_pParam = (CMyDataMem*)&Mem;
            MyDoModal(&dlg, MYDLL_MODULE);
        }
        break;
    case MTP_Regulate:
        {
            CMyDlgRegulate dlg;
            dlg.m_pRegulate = (CMyDataMem*)&Mem;
            MyDoModal(&dlg, MYDLL_MODULE);
        }
        break;
    case MTP_Setpoint:
        {
            CMyDlgSetpoint dlg;
            dlg.m_pSetpoint = (CMyDataMem*)&Mem;
            MyDoModal(&dlg, MYDLL_MODULE);
        }
        break;
    default: break;
    }
}

void CMyUnitDevice::OnOpenList(CMyDeviceList* pOPList)
{
    CMyDlgOpList dlg;
    dlg.m_pOPList = pOPList;
    MyDoModal(&dlg,MYDLL_MODULE);
}

void CMyUnitDevice::ReceiveWaveRecordHeadList(COMCONTROL* pCC)
{
    int nHeadLen = 11 + WAVERECORD_DATASIZE;
    int nWaveLen = sizeof(WAVERECORDR)/sizeof(WORD);
    WAVERECORDR WaveRecord;
    CMyOpListArray arList;
    OPList List;
    for(int i=0;i<WAVERECORD_WAVENUM;i++)
    {
        if(MODBUS_Read(pCC, LOGADDR_WAVERECORD+i*nWaveLen, nHeadLen, (WORD*)&WaveRecord)) break;
//         CopyByte2WORDHL((WORD*)&WaveRecord,pCCRX+3,nHeadLen);
        if(WaveRecord.wRecordStatus==0xffff && WaveRecord.wFreezeDotNo<=WAVERECORD_DOTNUM)
        {
            WORD wYear = WaveRecord.timeFreeze.wYear+2000;
            WORD wMonth = WaveRecord.timeFreeze.wMonth;
            WORD wDay = WaveRecord.timeFreeze.wDay;
            WORD wHour = WaveRecord.timeFreeze.wHour;
            WORD wMinute = WaveRecord.timeFreeze.wMinute;
            WORD wSecond = WaveRecord.timeFreeze.wSecond;
            WORD wMilliSecond = WaveRecord.timeFreeze.wMilliSecond;
            List.strName.Format("Wave:%d-%02d-%02d %02d:%02d:%02d.%03d",
                wYear,wMonth,wDay,wHour,wMinute,wSecond,wMilliSecond);
            List.nIndex = i;
            arList.Add(List);
        }
    }
    ASSERT(m_pWaveRecordList);
    m_pWaveRecordList->RefreshData(arList);
    m_bWaveRecordListOK = TRUE;
}

BOOL CMyUnitDevice::ReceiveWave(COMCONTROL* pCC, int nWaveNo)
{
    WAVERECORDR WaveRecord;
    nWaveNo %= WAVERECORD_WAVENUM;
    if(!ReceiveWaveRecordHead(pCC, nWaveNo, WaveRecord)) return FALSE;
    if(!ReceiveWaveRecordData(pCC, nWaveNo, WaveRecord)) return FALSE;
    SaveWave(WaveRecord);
    CString strMessage;
    strMessage.Format("���չ���¼������,¼����:%d", nWaveNo);
    AddEvent(strMessage);
    return TRUE;
}

BOOL CMyUnitDevice::ReceiveWaveRecordHead(COMCONTROL* pCC, int nWaveNo, WAVERECORDR& Waverecord)
{
    ASSERT(nWaveNo>=0 && nWaveNo<WAVERECORD_WAVENUM);
    int nHeadLen = 11 + WAVERECORD_DATASIZE;
    int nWaveLen = sizeof(WAVERECORDR)/sizeof(WORD);
    
    if(MODBUS_Read(pCC, LOGADDR_WAVERECORD+nWaveNo*nWaveLen, nHeadLen, (WORD*)&Waverecord)) return FALSE;
//     CopyByte2WORDHL((WORD*)&Waverecord, pCCRX+3, nHeadLen);
    if(Waverecord.wRecordStatus==0xffff && Waverecord.wFreezeDotNo<=WAVERECORD_DOTNUM)
    {
        CString strMessage;
        strMessage.Format("���չ���¼����ʼ,¼����:%d",nWaveNo);
        AddEvent(strMessage);
        return TRUE;
    }
    return FALSE;
}

BOOL CMyUnitDevice::ReceiveWaveRecordData(COMCONTROL* pCC, int nWaveNo, WAVERECORDR& Waverecord)
{
    ASSERT(nWaveNo>=0 && nWaveNo<WAVERECORD_WAVENUM);
    int nHeadLen = 11 + WAVERECORD_DATASIZE;
    int nWaveLen = sizeof(WAVERECORDR)/sizeof(WORD);
    int nDataLen = nWaveLen - nHeadLen;
    int nDataRcv = 0;                     // �Ѷ���ʱ������
    while(nDataRcv<nDataLen)
    {
        int nData = nDataLen - nDataRcv;
        if(nData>100) nData = 100;
        if(MODBUS_Read(pCC, LOGADDR_WAVERECORD+nWaveNo*nWaveLen +nHeadLen+nDataRcv, nData, (WORD*)&Waverecord.nData[0]+nDataRcv)) return FALSE;
        nDataRcv += nData;
    }
    return TRUE;
}

static const char* g_pszChannelName[] =
{
    _T("IA:A�ౣ������"),
    _T("IB:B�ౣ������"),
    _T("IC:C�ౣ������"),
    _T("I0:���򱣻�����"),
    _T("Ua:A���ѹ"),
    _T("Ub:B���ѹ"),
    _T("Uc:C���ѹ"),
    _T("Ux:��ȡ��ѹ"),
};

static const char* g_pszChannelUnit[] =
{
    _T("A"),
    _T("A"),
    _T("A"),
    _T("A"),
    _T("V"),
    _T("V"),
    _T("V"),
    _T("V"),
};

void CMyUnitDevice::SaveWave(WAVERECORDR& Waverecord)
{
    WORD wYear = Waverecord.timeFreeze.wYear+2000;
    WORD wMonth = Waverecord.timeFreeze.wMonth;
    WORD wDay = Waverecord.timeFreeze.wDay;
    WORD wHour = Waverecord.timeFreeze.wHour;
    WORD wMinute = Waverecord.timeFreeze.wMinute;
    WORD wSecond = Waverecord.timeFreeze.wSecond;
    WORD wMilliSecond = Waverecord.timeFreeze.wMilliSecond;
    if(wYear<2000 || wYear>2050) return;
    if(wMonth<1 || wMonth>12) return;
    if(wDay<1 || wDay>31) return;
    if(wHour>23) return;
    if(wMinute>59) return;
    if(wSecond>59) return;
    if(wMilliSecond>999) return;
    
    CString strFileName;
    strFileName.Format("Wave%d%02d%02d_%02d%02d%02d%03d.www",
        wYear,wMonth,wDay,wHour,wMinute,wSecond,wMilliSecond);
    
    int nWaveRecordedDot = Waverecord.wFreezeDotNo;

    CTime time = CTime(wYear,wMonth,wDay,wHour,wMinute,wSecond);
    time -= 10L;                // -10s
    DWORD dwMilliSecond = 10000L + wMilliSecond;
    dwMilliSecond -= (nWaveRecordedDot-24*5)*(20)/(24);            // ����ǰ(nWaveRecordedDot-24*5)��
//     dwMilliSecond -= nWaveRecordedDot*(20)/(24);                        // ����ǰ(nWaveRecordedDot)��
    time += dwMilliSecond/1000;
    wMilliSecond = (WORD)(dwMilliSecond%1000);
    
    CMyWaveInfo waveinfo;
    waveinfo.Create(WAVERECORD_DATASIZE-1, SWITCHCNT, nWaveRecordedDot, 24*50);
    waveinfo.SetTime(time.GetTime(),wMilliSecond);
    
    for(int i=0;i<WAVERECORD_DATASIZE-1;++i)
    {
        SetWaveInfoAD(waveinfo,i,g_pszChannelName[i], g_pszChannelUnit[i], nWaveRecordedDot, Waverecord);
    }
    for(i=0;i<SWITCHCNT;i++) SetWaveInfoDI(waveinfo, i, 1<<i, nWaveRecordedDot, Waverecord);
    
    waveinfo.StoreToFile(m_strName, strFileName);
}

void CMyUnitDevice::SetWaveInfoAD(CMyWaveInfo& waveinfo,int nChannelNo,CString strChannelName, CString strUnitage,
                                   int nWaveRecordedDot, WAVERECORDR& Waverecord)
{
    waveinfo.SetChannelInfoAD(nChannelNo, strChannelName, strUnitage, 4096);
    float* pData = waveinfo.m_pDataAD + nWaveRecordedDot*nChannelNo;
    float fSum = 0;
    for(int i=0;i<nWaveRecordedDot;i++)
    {
        int nData;
        nData = Waverecord.nData[nChannelNo][i];
        pData[i] = (float)nData;
        fSum += (float)nData;
    }
    if(nWaveRecordedDot) fSum /= nWaveRecordedDot;
    for(i=0;i<nWaveRecordedDot;i++)
    {
        float fWaveData = pData[i] - fSum;
        fWaveData = fWaveData*Waverecord.nK[nChannelNo]*0.0001f;
        pData[i] = fWaveData;
    }
}

void CMyUnitDevice::SetWaveInfoDI(CMyWaveInfo& waveinfo, int nChannelNo, WORD wMask, int nWaveRecordedDot, WAVERECORDR& Waverecord)
{
    ASSERT(nChannelNo>=0 && nChannelNo<SWITCHCNT);
    
    CString strChannelName = s_BIInfo[nChannelNo].czName;
    waveinfo.SetChannelInfoDI(nChannelNo,strChannelName,"0","1");
    for(int i=0;i<nWaveRecordedDot;i++)
    {
        BYTE* pDataDI = waveinfo.m_pDataDI + nChannelNo*nWaveRecordedDot;
        pDataDI[i] = ((Waverecord.nData[WAVERECORD_DATASIZE-1][i]&wMask)==wMask);
    }
}

//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------

