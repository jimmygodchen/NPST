//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef __CMYWAVEINFO_H
#define __CMYWAVEINFO_H

//---------------------------------------------- CMyWaveInfo ------------------
class CLASS_EXPORT CMyWaveInfo
{
public:
    CMyWaveInfo();
    ~CMyWaveInfo();

public:
    WORD m_wYear;               // ¼����ʼʱ��:��;
    WORD m_wMonth;              // ¼����ʼʱ��:��;
    WORD m_wDay;                // ¼����ʼʱ��:��;
    WORD m_wHour;               // ¼����ʼʱ��:ʱ;
    WORD m_wMinute;             // ¼����ʼʱ��:��;
    WORD m_wSecond;             // ¼����ʼʱ��:��;
    WORD m_wMilliSecond;        // ¼����ʼʱ��:����;
    BYTE m_NumChannelAD;        // ¼��ADͨ����;
    BYTE m_NumChannelDI;        // ¼��DIͨ����;
    WORD m_wDotPerChannel;      // ÿ��ͨ����������;
    WORD m_wFrequency;          // ����Ƶ��(ÿ�ܲ�12��=600);
    CStringArray m_astrNameAD;   // ADͨ������;
    CStringArray m_astrUnitageAD;// ADͨ����λ;
//     float m_fFullScaleAD[16];	// ADͨ���ֵ;
    CStringArray m_astrNameDI;  // DIͨ������;
//     CString m_strStatus0DI[16]; // DIͨ��״̬0����;
//     CString m_strStatus1DI[16]; // DIͨ��״̬1����;
    float* m_pDataAD;      // AD¼������;
    BYTE* m_pDataDI;       // DI¼������;

public:
    void Create(BYTE NumChannelAD, BYTE NumChannelDI, WORD wDotPerChannel, WORD wFrequency);
    void SetTime(time_t timeStart, WORD wMilliSecond);
    void SetTime(WORD wYear,WORD wMonth,WORD wDay,WORD wHour,WORD wMinute,WORD wSecond,WORD wMilliSecond);
    void SetChannelInfoAD(BYTE ChannelNo,CString strName,CString strUnitage,float fFullScale);
    void SetChannelInfoDI(BYTE ChannelNo,CString strName,CString strStatus0,CString strStatus1);
    void Destroy(void);
    void LoadFromFile(CString strFileName);
    void StoreToFile(CString strUnitName,CString strFileName);
    CString GetFileName(void);
    BOOL IsWaveValid(void);
    BOOL Serialize(CArchive& ar);
};

#endif/*__CMYWAVEINFO_H*/


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------

