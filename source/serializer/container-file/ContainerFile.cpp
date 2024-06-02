#include "PcHeader.h"

#include "Trace.h"
#include "TraceSys.h"
#include "TraceCStd.h"
#include "SystemTrace.h"

#include "WrapperCStd.h"

#include "ContainerFile.h"

using namespace std;
using namespace core;
using namespace wrap_cstd;

namespace serial_cf 
{
//+-----------------------------------------------------------------------------+
//! SCFP_INFO																	!
//+-----------------------------------------------------------------------------+
SCFP_INFO::SCFP_INFO()
{
	Clear();
}

SCFP_INFO::~SCFP_INFO()
{
	Clear();
}

SCFP_INFO::SCFP_INFO(const SCFP_INFO& p_gr)
{
	(*this) = p_gr;
}

SCFP_INFO& SCFP_INFO::operator=(const SCFP_INFO& p_gr)
{
	m_stTextId = p_gr.m_stTextId;
	m_nCfByteOffset = p_gr.m_nCfByteOffset;
	m_nDataByteSize = p_gr.m_nDataByteSize;

	return (*this);
}


void SCFP_INFO::Clear()
{
	m_stTextId.clear();
	m_nCfByteOffset = 0;
	m_nDataByteSize = 0;
}

//+-----------------------------------------------------------------------------+
//! container file functions													!
//+-----------------------------------------------------------------------------+
uint32_t PackData(FILE* p_pCf, const TCHAR* p_pcTextId, void* p_pData, const CFT_DB& p_nDataByteSize)
{
	uint32_t nError = 0;
	int nCmpRes = 0;
	string stUtf8 = T2U8(p_pcTextId);

	CFT_TB nTextByteSize = strlen(stUtf8.c_str());
	CFT_DB nDataByteSize = p_nDataByteSize;

	if(!nError) nError = ASSERTION_POINTER(p_pCf);
	if(!nError && p_nDataByteSize) nError = ASSERTION_POINTER(p_pData);
	if(!nError) nError = FileSeek(p_pCf, 0, SEEK_END);
	if(!nError && nTextByteSize > SERIAL_CF_TEXT_MAX_BYTE) nError = TRACE_SYS(STE_CF,_T("SERIAL_CF_TEXT_MAX_BYTE"));

	// write text size
	if(!nError) nError = FileWrite(&nTextByteSize, sizeof(CFT_TB), 1, p_pCf);
	// write text
	if(!nError && nTextByteSize) nError = FileWrite(stUtf8.c_str(), 1, nTextByteSize, p_pCf);

	// write data size
	if(!nError) nError = FileWrite(&p_nDataByteSize, sizeof(CFT_DB), 1, p_pCf);
	// write data
	if(!nError && p_nDataByteSize) nError = FileWrite(p_pData, 1, (size_t)p_nDataByteSize, p_pCf);

	return nError;
}

uint32_t ParseConatinerFileInfo(FILE* p_pCf, STL_SCFP_INFO& p_stlCfInfo)
{
	uint32_t nError = 0;
	int nEof = 0;
	size_t nReadCount = 0;
	CFT_TB nTextByteSize = 0;
	CFT_DB nDataByteSize = 0;
	CFT_DB nOffset = 0;

	p_stlCfInfo.clear();

	if(!nError) nError = ASSERTION_POINTER(p_pCf);
	if(!nError) nError = FileSeek(p_pCf, 0, SEEK_SET);

	char* pcText = new char[SERIAL_CF_TEXT_MAX_BYTE];

	while(!nError)
	{
		// read text size
		if(!nError) nError = FileRead(&nTextByteSize, sizeof(CFT_TB), sizeof(CFT_TB), 1, p_pCf, &nReadCount);
		if(!nError) nError = FileEof(p_pCf, nEof);
		if(!nError && nEof) break;
		if(!nError && nReadCount != 1) nError = TRACE_SYS(STE_ASSERT, _T(""));
		if(!nError && nTextByteSize > SERIAL_CF_TEXT_MAX_BYTE) nError = TRACE_SYS(STE_CF, _T("SERIAL_CF_TEXT_MAX_BYTE"));

		// read text
		memset(pcText,0,SERIAL_CF_TEXT_MAX_BYTE);
		if(!nError) nError = FileRead(pcText, SERIAL_CF_TEXT_MAX_BYTE, sizeof(char), nTextByteSize, p_pCf, &nReadCount);
		if(!nError && nReadCount != nTextByteSize) nError = TRACE_SYS(STE_ASSERT, _T(""));

		// read data size
		if(!nError) nError = FileRead(&nDataByteSize, sizeof(CFT_DB), sizeof(CFT_DB), 1, p_pCf, &nReadCount);
		if(!nError && nReadCount != 1) nError = TRACE_SYS(STE_ASSERT, _T(""));
		if(!nError) nError = FileSeek(p_pCf, (size_t)nDataByteSize, SEEK_CUR);

		if(!nError) nOffset += sizeof(CFT_TB);
		if(!nError) nOffset += nTextByteSize;
		if(!nError) nOffset += sizeof(CFT_DB);

		if(!nError)
		{ // remember info
			SCFP_INFO grCF;
			grCF.m_stTextId = U82T(pcText);
			grCF.m_nCfByteOffset = nOffset;
			grCF.m_nDataByteSize = nDataByteSize;
			p_stlCfInfo.push_back(grCF);
		}

		if(!nError) nOffset += nDataByteSize;
	}
		
	DELETE_ARRAY(pcText);
	return nError;
}

uint32_t UnpackData(FILE* p_pCf, const SCFP_INFO& p_grInfo, void* p_pStore, const CFT_DB& p_nStoreByteSize)
{
	uint32_t nError = 0;
	size_t nReadCount = 0;

	if(!nError) nError = ASSERTION_POINTER(p_pCf);
	if(!nError && p_grInfo.m_nDataByteSize) nError = ASSERTION_POINTER(p_pStore);
	if(!nError && p_nStoreByteSize < p_grInfo.m_nDataByteSize) nError = TRACE_SYS(STE_ARRAY, _T(""));

	if(!nError && p_grInfo.m_nDataByteSize) nError = FileSeek(p_pCf, (size_t)p_grInfo.m_nCfByteOffset, SEEK_SET);
	if(!nError && p_grInfo.m_nDataByteSize) nError = FileRead(p_pStore, (size_t)p_nStoreByteSize, 1, (size_t)p_grInfo.m_nDataByteSize, p_pCf, &nReadCount);
	if(!nError && p_grInfo.m_nDataByteSize && nReadCount != p_grInfo.m_nDataByteSize) nError = TRACE_SYS(STE_ASSERT, _T(""));

	return nError;
}

} // namespace