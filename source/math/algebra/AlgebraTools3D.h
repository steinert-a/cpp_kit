#pragma once

//+-----------------------------------------------------------------------------+
//! Algebra Tools 3D															!
//+-----------------------------------------------------------------------------+
namespace math
{

RowVector<3> RVec3D(double p_dX, double p_dY, double p_dZ)
{
	RowVector<3> vec;

	vec.m_adData[0] = p_dX;
	vec.m_adData[1] = p_dY;
	vec.m_adData[2] = p_dZ;

	return vec;
}

ColumnVector<3> CVec3D(double p_dX, double p_dY, double p_dZ)
{
	ColumnVector<3> vec;

	vec.m_adData[0] = p_dX;
	vec.m_adData[1] = p_dY;
	vec.m_adData[2] = p_dZ;

	return vec;
}

VEC3D Vec3D(double p_dX, double p_dY, double p_dZ)
{
	VEC3D vec;

	vec.m_adData[0] = p_dX;
	vec.m_adData[1] = p_dY;
	vec.m_adData[2] = p_dZ;

	return vec;
}

MAT3D Mat3D(double p_d00, double p_d01, double p_d02,
			double p_d10, double p_d11, double p_d12, 
			double p_d20, double p_d21, double p_d22)
{
	MAT3D mat;

	mat.m_adData[0][0] = p_d00;
	mat.m_adData[0][1] = p_d01;
	mat.m_adData[0][2] = p_d02;
	mat.m_adData[1][0] = p_d10;
	mat.m_adData[1][1] = p_d11;
	mat.m_adData[1][2] = p_d12;
	mat.m_adData[2][0] = p_d20;
	mat.m_adData[2][1] = p_d21;
	mat.m_adData[2][2] = p_d22;

	return mat;
}

MAT3D RotMatX3D(double p_dRadian)
{
	MAT3D matRes;
	
	matRes.m_adData[0][0] = 1;
	matRes.m_adData[1][1] = cos(p_dRadian);
	matRes.m_adData[2][1] = sin(p_dRadian);
	matRes.m_adData[1][2] = -sin(p_dRadian);
	matRes.m_adData[2][2] = cos(p_dRadian);

	return matRes;
}

MAT3D RotMatY3D(double p_dRadian)
{
	MAT3D matRes;
	
	matRes.m_adData[1][1] = 1;
	matRes.m_adData[0][0] = cos(p_dRadian);
	matRes.m_adData[0][2] = sin(p_dRadian);
	matRes.m_adData[2][0] = -sin(p_dRadian);
	matRes.m_adData[2][2] = cos(p_dRadian);

	return matRes;
}

MAT3D RotMatZ3D(double p_dRadian)
{
	MAT3D matRes;
	
	matRes.m_adData[2][2] = 1;
	matRes.m_adData[1][1] = cos(p_dRadian);
	matRes.m_adData[1][0] = sin(p_dRadian);
	matRes.m_adData[0][1] = -sin(p_dRadian);
	matRes.m_adData[0][0] = cos(p_dRadian);

	return matRes;
}

template<template<uint16_t> class _T>
MAT3D RotMatVec3D(_T<3>& p_vec, double p_dRadian)
{
	MAT3D matRes;
	_T<3> vec	= p_vec;
	double dSR	= sin(p_dRadian);
	double dCR	= cos(p_dRadian);

	double dNorm	= Norm2(vec);
	if(dNorm < MATH_ERROR) 
		THROW_MATH(MTE_NORM,_T(""));

	if(fabs(dNorm-1) > MATH_ERROR) 
		vec = Normalize(vec);
	
	matRes.m_adData[0][0] = vec.m_adData[0]*vec.m_adData[0]*(1.0-dCR) + dCR;
	matRes.m_adData[0][1] = vec.m_adData[0]*vec.m_adData[1]*(1.0-dCR) - vec.m_adData[2]*dSR;
	matRes.m_adData[0][2] = vec.m_adData[0]*vec.m_adData[2]*(1.0-dCR) + vec.m_adData[1]*dSR;
	matRes.m_adData[1][0] = vec.m_adData[1]*vec.m_adData[0]*(1.0-dCR) + vec.m_adData[2]*dSR;
	matRes.m_adData[1][1] = vec.m_adData[1]*vec.m_adData[1]*(1.0-dCR) + dCR;
	matRes.m_adData[1][2] = vec.m_adData[1]*vec.m_adData[2]*(1.0-dCR) - vec.m_adData[0]*dSR;
	matRes.m_adData[2][0] = vec.m_adData[2]*vec.m_adData[0]*(1.0-dCR) - vec.m_adData[1]*dSR;
	matRes.m_adData[2][1] = vec.m_adData[2]*vec.m_adData[1]*(1.0-dCR) + vec.m_adData[0]*dSR;
	matRes.m_adData[2][2] = vec.m_adData[2]*vec.m_adData[2]*(1.0-dCR) + dCR;

	return matRes;
}

} // namespace

