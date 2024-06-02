#pragma once

namespace core
{
//+-------------------------------------------------------------+
//! dynamic array												!
//+-------------------------------------------------------------+
template <typename _T>
class CDynamicArray
{
public:
	CDynamicArray();
	CDynamicArray(const CDynamicArray<_T>&);
	~CDynamicArray();

private:
	uint32_t	m_nSize;
	_T*			m_pData;

public:
	void Clear();

	void Resize(uint32_t);
	void Fill(const _T&);
	uint32_t Size();
	_T*	Data();

	CDynamicArray<_T>& operator=(const CDynamicArray<_T>&);
};

template <typename _T>
CDynamicArray<_T>::CDynamicArray()
{
	m_pData = NULL;
	Clear();
}

template <typename _T>
CDynamicArray<_T>::CDynamicArray(const CDynamicArray<_T>& p_gr)
{
	m_pData = NULL;
	(*this) = p_gr;
}

template <typename _T>
CDynamicArray<_T>::~CDynamicArray()
{
	Clear();
}

template <typename _T>
void CDynamicArray<_T>::Clear()
{
	m_nSize = 0;
	DELETE_ARRAY(m_pData);
}

template <typename _T>
void CDynamicArray<_T>::Resize(uint32_t p_nSize)
{
	if(m_nSize != p_nSize)
	{
		Clear();

		if(p_nSize)
		{
			m_nSize = p_nSize;	
			m_pData = new _T[m_nSize];
		}
	}
}

template <typename _T>
uint32_t CDynamicArray<_T>::Size()
{
	return m_nSize;
}

template <typename _T>
void CDynamicArray<_T>::Fill(const _T& p_gr)
{
	for(uint32_t n=0; n<m_nSize; n++)
		m_pData[n] = p_gr;
}

template <typename _T>
_T* CDynamicArray<_T>::Data()
{
	return m_pData;
}

template <typename _T>
CDynamicArray<_T>& CDynamicArray<_T>::operator=(const CDynamicArray<_T>& p_gr)
{
	Resize(p_gr.m_nSize);
	for(uint32_t n=0; n<m_nSize; n++)
		m_pData[n] = p_gr.m_pData[n];

	return (*this);
}

typedef CDynamicArray<uint8_t>					ARRAY_BYTE;
typedef CDynamicArray<uint32_t>					ARRAY_UINT;
typedef CDynamicArray<CDynamicArray<uint32_t>>	ARRAY2D_UINT;
typedef CDynamicArray<float>					ARRAY_FLOAT;
typedef CDynamicArray<CDynamicArray<float>>		ARRAY2D_FLOAT;
}