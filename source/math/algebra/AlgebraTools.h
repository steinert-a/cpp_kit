#pragma once

//+-----------------------------------------------------------------------------+
//! Algebra Tools																!
//+-----------------------------------------------------------------------------+
namespace math
{

template<uint16_t _R, uint16_t _C>
double Norm1(Matrix<_R,_C>& p_mat)
{
	double dRes	= 0;

	for(uint32_t nR=0; nR<_R; nR++)
	{
		for(uint32_t nC=0; nC<_C; nC++)
		{
			dRes += abs(p_mat.m_adData[nR][nC]);
		}
	}

	return dRes;
}

template<uint16_t _R, uint16_t _C>
double Norm2(Matrix<_R,_C>& p_mat)
{
	double dRes	= 0;

	for(uint32_t nR=0; nR<_R; nR++)
	{
		for(uint32_t nC=0; nC<_C; nC++)
		{
			dRes += p_mat.m_adData[nR][nC] * p_mat.m_adData[nR][nC];
		}
	}

	return std::sqrt(dRes);
}

template<template<uint16_t> class _T, uint16_t _RC>
double Norm1(_T<_RC>& p_vec)
{
	double dRes	= 0;

	for(uint32_t nRC=0; nRC<_RC; nRC++)
		dRes += abs(p_vec.m_adData[nRC]);

	return dRes;
}

template<template<uint16_t> class _T, uint16_t _RC>
double Norm2(_T<_RC>& p_vec)
{
	double dRes	= 0;

	for(uint32_t nRC=0; nRC<_RC; nRC++)
		dRes += p_vec.m_adData[nRC] * p_vec.m_adData[nRC];

	return std::sqrt(dRes);
}

template<template<uint16_t> class _T, uint16_t _RC>
_T<_RC> Normalize(_T<_RC>& p_vec)
{
	_T<_RC> vecRes;
	double dNorm2 = Norm2(p_vec);
	
	if(dNorm2 < MATH_ERROR) THROW_MATH(MTE_NORM,_T(""));

	vecRes = p_vec * (1.0 / dNorm2);

	return vecRes;
}

template<uint16_t _RC>
Matrix<_RC,_RC> IdentityMatrix()
{
	Matrix<_RC,_RC> matRes;
	
	for(uint32_t nRC=0; nRC<_RC; nRC++)
		matRes.m_adData[nRC][nRC] = 1.0;

	return matRes;
}

template<uint16_t _R, uint16_t _C>
Matrix<_C,_R> Transpose(Matrix<_R,_C>& p_mat)
{
	Matrix<_C,_R> matRes;
	
	for(uint32_t nR=0; nR<_R; nR++)
	{
		for(uint32_t nC=0; nC<_C; nC++)
		{
			matRes.m_adData[nC][nR] = p_mat.m_adData[nR][nC];
		}
	}

	return matRes;
}

template<uint16_t _RC>
ColumnVector<_RC> Transpose(RowVector<_RC>& p_vec)
{
	ColumnVector<_RC> vecRes;
	
	for(uint32_t nRC=0; nRC<_RC; nRC++)
		vecRes.m_adData[nRC] = p_vec.m_adData[nRC];

	return vecRes;
}

template<uint16_t _RC>
RowVector<_RC> Transpose(ColumnVector<_RC>& p_vec)
{
	RowVector<_RC> vecRes;
	
	for(uint32_t nRC=0; nRC<_RC; nRC++)
		vecRes.m_adData[nRC] = p_vec.m_adData[nRC];

	return vecRes;
}

template<template<uint16_t> class _T1, template<uint16_t> class _T2, uint16_t _RC>
double DotProduct(_T1<_RC>& p_vec1, _T2<_RC>& p_vec2)
{
	double dDot = 0;

	for(uint32_t nRC=0; nRC<_RC; nRC++)
		dDot	+= p_vec1.m_adData[nRC] * p_vec2.m_adData[nRC];

	return dDot;
}

template<template<uint16_t> class _T1, template<uint16_t> class _T2, uint16_t _RC>
double Radian(_T1<_RC>& p_vec1, _T2<_RC>& p_vec2)
{
	double dRes		= 0;
	double dDot		= 0;
	double dNorm2_1	= 0;
	double dNorm2_2	= 0;

	dNorm2_1	= Norm2(p_vec1);
	dNorm2_2	= Norm2(p_vec2);
	if(dNorm2_1 < MATH_ERROR || dNorm2_2 < MATH_ERROR) 
		THROW_MATH(MTE_NORM,_T(""));

	dDot	= DotProduct(p_vec1,p_vec2);
	dRes	= (dDot) / (dNorm2_1*dNorm2_2);
	dRes	= acos(dRes);

	return dRes;
}

template<uint16_t _R>
Matrix<_R,_R> Projection(RowVector<_R>& p_vec)
{
	Matrix<_R,_R> matRes;

	if(Norm1(p_vec) < MATH_ERROR) 
		THROW_MATH(MTE_NORM,_T(""));

	matRes = IdentityMatrix<_R>() - (p_vec * Transpose(p_vec)) * (1.0/DotProduct(p_vec,p_vec));

	return matRes;
}

template<uint16_t _R>
Matrix<_R,_R> Householder(RowVector<_R>& p_vec)
{
	Matrix<_R,_R> matRes;

	if(Norm1(p_vec) < MATH_ERROR) 
		THROW_MATH(MTE_NORM,_T(""));

	matRes = IdentityMatrix<_R>() - (p_vec * Transpose(p_vec)) * (2.0/DotProduct(p_vec,p_vec));

	return matRes;
}

}