#pragma once

namespace core
{
//+-------------------------------------------------------------+
//! dynamic field												!
//+-------------------------------------------------------------+
template <typename _T>
class CDynamicField
{
public:
	CDynamicField();
	CDynamicField(const CDynamicField<_T>&);
	~CDynamicField();

private:
	uint32_t	m_aSize[3];
	_T*			m_pData;

public:
	void Clear();
	void Resize(uint32_t,uint32_t);
	void Fill(const _T&);
	uint32_t SizeR(); // rows
	uint32_t SizeC(); // columns
	uint32_t SizeA(); // array
	_T* Data();
	_T* Row(uint32_t);

	CDynamicField<_T>& operator=(const CDynamicField<_T>&);
};

template <typename _T>
CDynamicField<_T>::CDynamicField() : m_pData(NULL)
{
	Clear();
}

template <typename _T>
CDynamicField<_T>::CDynamicField(const CDynamicField<_T>& p_gr) : m_pData(NULL)
{
	(*this) = p_gr;
}

template <typename _T>
CDynamicField<_T>::~CDynamicField()
{
	Clear();
}

template <typename _T>
void CDynamicField<_T>::Clear()
{
	memset(m_aSize,0,3*sizeof(uint32_t));
	DELETE_ARRAY(m_pData);
}

template <typename _T>
void CDynamicField<_T>::Resize(uint32_t p_nColumns, uint32_t p_nRows)
{
	if(p_nColumns != m_aSize[0] || p_nRows != m_aSize[1])
	{
		Clear();

		if(p_nColumns && p_nRows)
		{
			m_aSize[0] = p_nColumns;	
			m_aSize[1] = p_nRows;	
			m_aSize[2] = p_nColumns*p_nRows;	
			m_pData = new _T[m_aSize[2]];
		}
	}
}

template <typename _T>
uint32_t CDynamicField<_T>::SizeC()
{
	return m_aSize[0];
}

template <typename _T>
uint32_t CDynamicField<_T>::SizeR()
{
	return m_aSize[1];
}

template <typename _T>
uint32_t CDynamicField<_T>::SizeA()
{
	return m_aSize[2];
}

template <typename _T>
void CDynamicField<_T>::Fill(const _T& p_gr)
{
	for(uint32_t n=0; n<m_aSize[2]; n++)
		m_pData[n] = p_gr;
}

template <typename _T>
_T* CDynamicField<_T>::Data()
{
	return m_pData;
}

template <typename _T>
_T* CDynamicField<_T>::Row(uint32_t p_nIdxR)
{
	if(p_nIdxR >= m_aSize[1]) return NULL;
	return &m_pData[p_nIdxR*m_aSize[0]];
}

template <typename _T>
CDynamicField<_T>& CDynamicField<_T>::operator=(const CDynamicField<_T>& p_gr)
{
	Resize(p_gr.SizeC(), p_gr.SizeR());

	for(uint32_t n=0; n< m_aSize[2]; n++)
		m_pData[n] = p_gr.m_pData[n];

	return (*this);
}

typedef CDynamicField<uint8_t>		FIELD_BYTE;
typedef CDynamicField<uint32_t>		FIELD_UINT;
typedef CDynamicField<int>			FIELD_INT;
typedef CDynamicField<float>		FIELD_FLOAT;
}