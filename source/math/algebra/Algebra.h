#pragma once

//+-----------------------------------------------------------------------------+
//! description                                                                 !
//! -----------                                                                 !
//!                                                                             !
//! matrix with 1 column or 1 row is not allowed, convert to a vector           !
//! vector with 1 column and 1 row is not allowed, convert to a double          !
//!                                                                             !
//!	four types are given                                                        !
//! matrix / row vector	/ column vector / double                                !
//+-----------------------------------------------------------------------------+

//+-----------------------------------------------------------------------------+
//! Matrix																		!
//+-----------------------------------------------------------------------------+
namespace math
{

template<uint16_t _R, uint16_t _C>
class Matrix
{
public:
	Matrix();
	~Matrix();
	Matrix(const Matrix<_R,_C>&);

public:
	double	m_adData[_R][_C];

public:
	double* operator[](uint16_t);
	Matrix<_R,_C>& operator=(const Matrix<_R,_C>&);

public:
	void Zeroise();
};

template<uint16_t _R, uint16_t _C>
Matrix<_R,_C>::Matrix()
{
	Zeroise();
}

template<uint16_t _R, uint16_t _C>
Matrix<_R,_C>::Matrix(const Matrix<_R,_C>& p_gr)
{
	(*this) = p_gr;
}

template<uint16_t _R, uint16_t _C>
Matrix<_R,_C>::~Matrix()
{}

template<uint16_t _R, uint16_t _C>
void Matrix<_R,_C>::Zeroise()
{
	memset(m_adData,0,_R*_C*sizeof(double));
}

template<uint16_t _R, uint16_t _C>
double* Matrix<_R,_C>::operator[](uint16_t p_nR)
{
	return m_adData[p_nR];
}

template<uint16_t _R, uint16_t _C>
Matrix<_R,_C>& Matrix<_R,_C>::operator=(const Matrix<_R,_C>& p_gr)
{
	memcpy(m_adData,p_gr.m_adData,_R*_C*sizeof(double));
	return (*this);
}

//+-----------------------------------------------------------------------------+
//! Row Vector																	!
//+-----------------------------------------------------------------------------+
template<uint16_t _R>
class RowVector
{
public:
	RowVector();
	~RowVector();
	RowVector(const RowVector<_R>&);

public:
	double	m_adData[_R];

public:
	double& operator[](uint16_t);
	RowVector<_R>& operator=(const RowVector<_R>&);

public:
	void Zeroise();
};

template<uint16_t _R>
RowVector<_R>::RowVector()
{
	Zeroise();
}

template<uint16_t _R>
RowVector<_R>::RowVector(const RowVector<_R>& p_gr)
{
	(*this) = p_gr;
}

template<uint16_t _R>
RowVector<_R>::~RowVector()
{}

template<uint16_t _R>
void RowVector<_R>::Zeroise()
{
	memset(m_adData,0,_R*sizeof(double));
}

template<uint16_t _R>
double& RowVector<_R>::operator[](uint16_t p_nR)
{
	return m_adData[p_nR];
}

template<uint16_t _R>
RowVector<_R>& RowVector<_R>::operator=(const RowVector<_R>& p_gr)
{
	memcpy(m_adData,p_gr.m_adData,_R*sizeof(double));
	return (*this);
}

//+-----------------------------------------------------------------------------+
//! Column Vector																!
//+-----------------------------------------------------------------------------+
template<uint16_t _C>
class ColumnVector
{
public:
	ColumnVector();
	~ColumnVector();
	ColumnVector(const ColumnVector<_C>&);

public:
	double	m_adData[_C];

public:
	double& operator[](uint16_t);
	ColumnVector<_C>& operator=(const ColumnVector<_C>&);

public:
	void Zeroise();
};

template<uint16_t _C>
ColumnVector<_C>::ColumnVector()
{
	Zeroise();
}

template<uint16_t _C>
ColumnVector<_C>::ColumnVector(const ColumnVector<_C>& p_gr)
{
	(*this) = p_gr;
}

template<uint16_t _C>
ColumnVector<_C>::~ColumnVector()
{}

template<uint16_t _C>
void ColumnVector<_C>::Zeroise()
{
	memset(m_adData,0,_C*sizeof(double));
}

template<uint16_t _C>
double& ColumnVector<_C>::operator[](uint16_t p_nC)
{
	return m_adData[p_nC];
}

template<uint16_t _C>
ColumnVector<_C>& ColumnVector<_C>::operator=(const ColumnVector<_C>& p_gr)
{
	memcpy(m_adData,p_gr.m_adData,_C*sizeof(double));
	return (*this);
}

//+-----------------------------------------------------------------------------+
//! matrix vector operators														!
//+-----------------------------------------------------------------------------+

//+-----------------------------------------------------------------------------+
//!   *  !!mat  !r_vec!c_vec!float!												!
//! -----++-----+-----+-----+-----+												!
//! -----++-----+-----+-----+-----+												!
//! mat  !!mat  !r_vec!     !mat  !												!
//! -----++-----+-----+-----+-----+												!
//! r_vec!!     !     !mat  !r_vec!												!
//! -----++-----+-----+-----+-----+												!
//! c_vec!!c_vec!float!     !c_vec!												!
//! -----++-----+-----+-----+-----+												!
//! float!!mat  !r_vec!c_vec!     !												!
//! -----++-----+-----+-----+-----+												!
//+-----------------------------------------------------------------------------+

// mat * mat = mat
template<uint16_t _R, uint16_t _C, uint16_t _RC>
Matrix<_R,_C> operator*(Matrix<_R,_RC>& p_matM1, Matrix<_RC,_C>& p_matM2)
{
	Matrix<_R,_C> matRes;

	for(uint16_t nR=0; nR<_R; nR++)
	{	
		for(uint16_t nC=0; nC<_C; nC++)
		{
			for(uint16_t nRC=0; nRC<_RC; nRC++)
			{
				matRes.m_adData[nR][nC] += p_matM1.m_adData[nR][nRC] * p_matM2.m_adData[nRC][nC];
			}
		}
	}

	return matRes;
}

// cvec * mat = cvec
template<uint16_t _RC, uint16_t _C>
ColumnVector<_C> operator*(ColumnVector<_RC>& p_vec, Matrix<_RC,_C>& p_mat)
{
	ColumnVector<_C> vecRes;

	for(uint16_t nC=0; nC<_C; nC++)
	{
		for(uint16_t nRC=0; nRC<_RC; nRC++)
		{
			vecRes.m_adData[nC] += p_vec.m_adData[nRC] * p_mat.m_adData[nRC][nC];
		}
	}

	return vecRes;
}

// mat * rvec = rvec
template<uint16_t _R, uint16_t _RC>
RowVector<_R> operator*(Matrix<_R,_RC>& p_mat, RowVector<_RC>& p_vec)
{
	RowVector<_R> vecRes;

	for(uint16_t nR=0; nR<_R; nR++)
	{	
		for(uint16_t nRC=0; nRC<_RC; nRC++)
		{
			vecRes.m_adData[nR] += p_mat.m_adData[nR][nRC] * p_vec.m_adData[nRC];
		}
	}

	return vecRes;
}

// cvec * rvec = float
template<uint16_t _RC>
double operator*(ColumnVector<_RC>& p_vecV1, RowVector<_RC>& p_vecV2)
{
	double dRes = 0;

	for(uint16_t nRC=0; nRC<_RC; nRC++)
		dRes += p_vecV1.m_adData[nRC] * p_vecV2.m_adData[nRC];

	return dRes;
}

// rvec * cvec = mat
template<uint16_t _RC>
Matrix<_RC,_RC> operator*(RowVector<_RC>& p_vecV1, ColumnVector<_RC>& p_vecV2)
{
	Matrix<_RC,_RC>  matRes;

	for(uint16_t nR=0; nR<_RC; nR++)
	{
		for(uint16_t nC=0; nC<_RC; nC++)
		{
			matRes.m_adData[nR][nC] = p_vecV1.m_adData[nR] * p_vecV2.m_adData[nC];
		}
	}

	return matRes;
}

// mat * float = mat
template<uint16_t _R, uint16_t _C>
Matrix<_R,_C> operator*(Matrix<_R,_C>& p_mat, double p_d)
{
	Matrix<_R,_C> matRes;

	for(uint16_t nR=0; nR<_R; nR++)
	{	
		for(uint16_t nC=0; nC<_C; nC++)
		{
			matRes.m_adData[nR][nC] = p_mat.m_adData[nR][nC] * p_d;
		}
	}

	return matRes;
}

// float * mat = mat
template<uint16_t _R, uint16_t _C>
Matrix<_R,_C> operator*(double p_d, Matrix<_R,_C>& p_mat)
{
	Matrix<_R,_C> matRes;

	for(uint16_t nR=0; nR<_R; nR++)
	{	
		for(uint16_t nC=0; nC<_C; nC++)
		{
			matRes.m_adData[nR][nC] = p_mat.m_adData[nR][nC] * p_d;
		}
	}

	return matRes;
}

// cvec * float = cvec
// rvec * float = rvec
template<template<uint16_t> class _T, uint16_t _RC>
_T<_RC> operator*(_T<_RC>& p_vec, double p_d)
{
	_T<_RC> vecRes;

	for(uint16_t nRC=0; nRC<_RC; nRC++)	
		vecRes.m_adData[nRC] = p_vec.m_adData[nRC] * p_d;

	return vecRes;
}

// float * rvec = rvec 
// float * cvec = cvec
template<template<uint16_t> class _T, uint16_t _RC>
_T<_RC> operator*(double p_d, _T<_RC>& p_vec)
{
	_T<_RC> vecRes;

	for(uint16_t nRC=0; nRC<_RC; nRC++)	
		vecRes.m_adData[nRC] = p_vec.m_adData[nRC] * p_d;

	return vecRes;
}

//+-----------------------------------------------------------------------------+
//!  +/- !!mat  !r_vec!c_vec!float!												!
//! -----++-----+-----+-----+-----+												!
//! -----++-----+-----+-----+-----+												!
//! mat  !!mat  !     !     !     !												!
//! -----++-----+-----+-----+-----+												!
//! r_vec!!     !r_vec!     !     !												!
//! -----++-----+-----+-----+-----+												!
//! c_vec!!     !     !c_vec!     !												!
//! -----++-----+-----+-----+-----+												!
//! float!!     !     !     !     !												!
//! -----++-----+-----+-----+-----+												!
//+-----------------------------------------------------------------------------+

// mat + mat = mat
template<uint16_t _R, uint16_t _C>
Matrix<_R,_C> operator+(Matrix<_R,_C>& p_matM1, Matrix<_R,_C>& p_matM2)
{
	Matrix<_R,_C> matRes;

	for(uint16_t nR=0; nR<_R; nR++)
	{	
		for(uint16_t nC=0; nC<_C; nC++)
		{

			matRes.m_adData[nR][nC] = p_matM1.m_adData[nR][nC] + p_matM2.m_adData[nR][nC];
		}
	}

	return matRes;
}

// mat - mat = mat
template<uint16_t _R, uint16_t _C>
Matrix<_R,_C> operator-(Matrix<_R,_C>& p_matM1, Matrix<_R,_C>& p_matM2)
{
	Matrix<_R,_C> matRes;

	for(uint16_t nR=0; nR<_R; nR++)
	{	
		for(uint16_t nC=0; nC<_C; nC++)
		{

			matRes.m_adData[nR][nC] = p_matM1.m_adData[nR][nC] - p_matM2.m_adData[nR][nC];
		}
	}

	return matRes;
}

// rvec + rvec = rvec
// cvec + cvec = cvec
template<template<uint16_t> class _T, uint16_t _RC>
_T<_RC> operator+(_T<_RC>& p_vec1, _T<_RC>& p_vec2)
{
	_T<_RC> vecRes;

	for(uint16_t nRC=0; nRC<_RC; nRC++)
		vecRes.m_adData[nRC] = p_vec1.m_adData[nRC] + p_vec2.m_adData[nRC];

	return vecRes;
}

// rvec - rvec = rvec
// cvec - cvec = cvec
template<template<uint16_t> class _T, uint16_t _RC>
_T<_RC> operator-(_T<_RC>& p_vec1, _T<_RC>& p_vec2)
{
	_T<_RC> vecRes;

	for(uint16_t nRC=0; nRC<_RC; nRC++)
		vecRes.m_adData[nRC] = p_vec1.m_adData[nRC] - p_vec2.m_adData[nRC];

	return vecRes;
}

//+-----------------------------------------------------------------------------+
//!  *=  !!mat  !r_vec!c_vec!float!												!
//! -----++-----+-----+-----+-----+												!
//! -----++-----+-----+-----+-----+												!
//! mat  !!mat* !     !     !mat  !	* only square matrix						!
//! -----++-----+-----+-----+-----+												!
//! r_vec!!     !     !     !r_vec!												!
//! -----++-----+-----+-----+-----+												!
//! c_vec!!     !     !     !c_vec!												!
//! -----++-----+-----+-----+-----+												!
//! float!!     !     !     !     !												!
//! -----++-----+-----+-----+-----+												!
//+-----------------------------------------------------------------------------+

// mat *= mat
template<uint16_t _RC>
Matrix<_RC,_RC>& operator*=(Matrix<_RC,_RC>& p_matM1, Matrix<_RC,_RC>& p_matM2)
{
	Matrix<_RC,_RC> matRes;

	for(uint16_t nR=0; nR<_RC; nR++)
	{	
		for(uint16_t nC=0; nC<_RC; nC++)
		{
			for(uint16_t nRC=0; nRC<_RC; nRC++)
			{
				matRes.m_adData[nR][nC] += p_matM1.m_adData[nR][nRC] * p_matM2.m_adData[nRC][nC];
			}
		}
	}

	p_matM1 = matRes;
	return p_matM1;
}

// mat *= float
template<uint16_t _R, uint16_t _C>
Matrix<_R,_C>& operator*=(Matrix<_R,_C>& p_mat, double p_d)
{
	for(uint16_t nR=0; nR<_R; nR++)
	{	
		for(uint16_t nC=0; nC<_C; nC++)
		{
			p_mat.m_adData[nR][nC] *= p_d;
		}
	}

	return p_mat;
}

// rvec *= float
// cvec *= float
template<template<uint16_t> class _T, uint16_t _RC>
_T<_RC>& operator*=(_T<_RC>& p_vec, double p_d)
{
	for(uint16_t nRC=0; nRC<_RC; nRC++)	
		p_vec.m_adData[nRC] *= p_d;

	return p_vec;
}

//+-----------------------------------------------------------------------------+
//! +=/-=!!mat  !r_vec!c_vec!float!												!
//! -----++-----+-----+-----+-----+												!
//! -----++-----+-----+-----+-----+												!
//! mat  !!mat  !     !     !     !												!
//! -----++-----+-----+-----+-----+												!
//! r_vec!!     !r_vec!     !     !												!
//! -----++-----+-----+-----+-----+												!
//! c_vec!!     !     !c_vec!     !												!
//! -----++-----+-----+-----+-----+												!
//! float!!     !     !     !     !												!
//! -----++-----+-----+-----+-----+												!
//+-----------------------------------------------------------------------------+

// mat += mat
template<uint16_t _R, uint16_t _C>
Matrix<_R,_C>& operator+=(Matrix<_R,_C>& p_matM1, Matrix<_R,_C>& p_matM2)
{
	for(uint16_t nR=0; nR<_R; nR++)
	{	
		for(uint16_t nC=0; nC<_C; nC++)
		{
			p_matM1.m_adData[nR][nC] += p_matM2.m_adData[nR][nC];
		}
	}

	return p_matM1;
}

// mat -= mat
template<uint16_t _R, uint16_t _C>
Matrix<_R,_C>& operator-=(Matrix<_R,_C>& p_matM1, Matrix<_R,_C>& p_matM2)
{
	for(uint16_t nR=0; nR<_R; nR++)
	{	
		for(uint16_t nC=0; nC<_C; nC++)
		{
			p_matM1.m_adData[nR][nC] -= p_matM2.m_adData[nR][nC];
		}
	}

	return p_matM1;
}

// rvec += rvec
// cvec += cvec
template<template<uint16_t> class _T, uint16_t _RC>
_T<_RC>& operator+=(_T<_RC>& p_vecV1, _T<_RC>& p_vecV2)
{
	for(uint16_t nRC=0; nRC<_RC; nRC++)
		p_vecV1.m_adData[nRC] += p_vecV2.m_adData[nRC];

	return p_vecV1;
}

// rvec -= rvec
// cvec -= cvec
template<template<uint16_t> class _T, uint16_t _RC>
_T<_RC>& operator-=(_T<_RC>& p_vecV1, _T<_RC>& p_vecV2)
{
	for(uint16_t nRC=0; nRC<_RC; nRC++)
		p_vecV1.m_adData[nRC] -= p_vecV2.m_adData[nRC];

	return p_vecV1;
}

} // namespace

//+-----------------------------------------------------------------------------+
//! defines																		!
//+-----------------------------------------------------------------------------+
#define MAT2D	math::Matrix<2,2>
#define MAT3D	math::Matrix<3,3>
#define MAT4D	math::Matrix<4,4>

#define VEC2D	math::RowVector<2>
#define RVEC2D	math::RowVector<2>
#define CVEC2D	math::ColumnVector<2>

#define VEC3D	math::RowVector<3>
#define RVEC3D	math::RowVector<3>
#define CVEC3D	math::ColumnVector<3>

#define VEC4D	math::RowVector<4>
#define RVEC4D	math::RowVector<4>
#define CVEC4D	math::ColumnVector<4>