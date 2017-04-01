//-----------------------------------------------------------------------------------------------------
//                                  Copyright (c) 2009 by ThinkBoy.
//                                      All rights reserved.
//
// Header:
// File Name:
// Author: jimmy
// Date:
//-----------------------------------------------------------------------------------------------------

#include "stdAfx.h"
#include "Pub.h"

CMyVector::CMyVector()
{
    m_fR = 0;
    m_fX = 0;
    m_fA = 0;
}

CMyVector::CMyVector(float fR)
{
    SetA(fR);
}

CMyVector::CMyVector(float fR, float fX, float fA)
{
    SetA(fR, fX);
}

CMyVector::CMyVector(float fA, float fRad)
{
    SetPolar(fA, fRad);
}

CMyVector::CMyVector(const CMyVector& Vec)
{
    m_fR = Vec.m_fR;
    m_fX = Vec.m_fX;
    m_fA = Vec.m_fA;
}

const CMyVector operator+(const CMyVector& A, const CMyVector& B)
{
    CMyVector result;
    float fR = A.m_fR + B.m_fR;
    float fX = A.m_fX + B.m_fX;
    result.SetA(fR,fX);
    return result;
}

const CMyVector operator-(const CMyVector& A, const CMyVector& B)
{
    CMyVector result;
    float fR = A.m_fR - B.m_fR;
    float fX = A.m_fX - B.m_fX;
    result.SetA(fR,fX);
    return result;
}

const CMyVector operator*(const CMyVector& A, const CMyVector& B)
{
    CMyVector result;
    float fR = A.m_fR*B.m_fR - A.m_fX*B.m_fX;
    float fX = A.m_fR*B.m_fX + A.m_fX*B.m_fR;
    result.SetA(fR,fX);
    return result;
}

//     const CMyVector operator*(const CMyVector& A,const float fB);

//     const CMyVector operator*(const float fA,const CMyVector& B);

const CMyVector operator/(const CMyVector& A, const CMyVector& B)
{
    CMyVector result;
    if(B.m_fA==0)
    {
        result.SetA(0,0,0);
    }
    else
    {
        float fA = B.m_fA*B.m_fA;
        float fR = (A.m_fR*B.m_fR + A.m_fX*B.m_fX)/fA;
        float fX = (A.m_fX*B.m_fR - A.m_fR*B.m_fX)/fA;
        result.SetA(fR,fX);
    }
    return result;
}

// BOOL operator!=(const CMyVector& A, const CMyVector& B)
// {
//     if(fabs(A.m_fR-B.m_fR)>FLT_EPSILON) return TRUE;
//     if(fabs(A.m_fX-B.m_fX)>FLT_EPSILON) return TRUE;
//     return FALSE;
// }

BOOL CMyVector::operator!=(const CMyVector& Vec)
{
    if(fabsf(m_fR-Vec.m_fR)>FLT_EPSILON) return TRUE;
    if(fabsf(m_fX-Vec.m_fX)>FLT_EPSILON) return TRUE;
    return FALSE;
}

BOOL CMyVector::operator==(const CMyVector& Vec)
{
    if(fabsf(m_fR-Vec.m_fR)>FLT_EPSILON) return FALSE;
    if(fabsf(m_fX-Vec.m_fX)>FLT_EPSILON) return FALSE;
    return TRUE;
}

const CMyVector CMyVector::operator=(const CMyVector& Vec)
{
    m_fR = Vec.m_fR;
    m_fX = Vec.m_fX;
    m_fA = Vec.m_fA;
    return *this;
}

//     const CMyVector operator/(const CMyVector& A,const float fB);

//     const CMyVector operator/(const float fA,const CMyVector& B);

//-----------------------------------------------------------------------------------------------------
//                                      End Of File
//-----------------------------------------------------------------------------------------------------
