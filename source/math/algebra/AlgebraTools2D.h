#pragma once

//+-----------------------------------------------------------------------------+
//! Algebra Tools 2D															!
//+-----------------------------------------------------------------------------+
namespace math
{

RowVector<2> RVec2D(double p_dX, double p_dY)
{
	RowVector<2> vec;

	vec.m_adData[0] = p_dX;
	vec.m_adData[1] = p_dY;

	return vec;
}

ColumnVector<2> CVec2D(double p_dX, double p_dY)
{
	ColumnVector<2> vec;

	vec.m_adData[0] = p_dX;
	vec.m_adData[1] = p_dY;

	return vec;
}

VEC2D Vec2D(double p_dX, double p_dY)
{
	VEC2D vec;

	vec.m_adData[0] = p_dX;
	vec.m_adData[1] = p_dY;

	return vec;
}

MAT2D Mat2D(double p_d00, double p_d01,
			double p_d10, double p_d11)
{
	MAT2D mat;

	mat.m_adData[0][0] = p_d00;
	mat.m_adData[0][1] = p_d01;

	mat.m_adData[1][0] = p_d10;
	mat.m_adData[1][1] = p_d11;

	return mat;
}

MAT2D RotMat2D(double p_dRadian)
{
	MAT2D matRes;
	
	matRes.m_adData[0][0] = cos(p_dRadian);
	matRes.m_adData[1][0] = sin(p_dRadian);
	matRes.m_adData[0][1] = -sin(p_dRadian);
	matRes.m_adData[1][1] = cos(p_dRadian);

	return matRes;
}

} // namespace

