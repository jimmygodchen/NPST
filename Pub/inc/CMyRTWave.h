//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#ifndef __CMYRTWAVE_H
#define __CMYRTWAVE_H

typedef struct
{
    char* pszChName;                  // ͨ������
    BOOL bVisible;                      // �Ƿ���ʾ
}tRTWAVECHINFO;

typedef CArray<tRTWAVECHINFO, tRTWAVECHINFO&> CMyRTWaveChInfoArray;

// ---------------------------------------------- CMyRTWave -------------
class CLASS_EXPORT CMyRTWave:public CMyDataOperate
{
protected:
    DECLARE_SERIAL(CMyRTWave);
    CMyRTWave();
    ~CMyRTWave();

protected:
    int m_nDotPerWave;                      // ÿ�ܲ�����
    CMyRTWaveChInfoArray m_arRTWaveChInfo;
    float* m_pfRTWave;                       // ʵʱ��������

public:
//     virtual void Serialize(CArchive& ar);
    virtual void Initialize(CString strName, const CMyRTWaveChInfoArray& arRTWaveChInfo, int nDotPerWave);
    virtual BOOL ExeOperate(void);
    virtual void RefreshData(int nChIndex, const float* pfData);

public:
    int GetChNum(void);                     // ��ȡͨ����
    const tRTWAVECHINFO& GetChInfo(int nChIndex);
    void SetChVisible(int nChIndex, BOOL bVisible);
    int GetDotNum(void);
    const float* GetBuff(int nChIndex);
};


#endif/*__CMYRTWAVE_H*/


//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------

