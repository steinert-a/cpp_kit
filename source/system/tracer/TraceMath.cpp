#include "PcHeader.h"

#include "Trace.h"
#include "TraceMath.h"

using namespace std;

namespace sys
{

//+-----------------------------------------------------------------------------+
//! system tracer																!
//+-----------------------------------------------------------------------------+
TraceMath::TraceMath(const uint32_t &p_nStc, const _TCHAR *p_pcText, const _TCHAR *p_pcFile, const _TCHAR *p_pcFunc, const uint32_t &p_nLine)
{	
	m_nCode			= p_nStc;
	m_stText		= p_pcText;
	m_stFile		= p_pcFile;
	m_stFunction	= p_pcFunc;
	m_nLine			= p_nLine;
}

TraceMath::~TraceMath()
{}

uint32_t TraceMath::Source()
{	
	return STES_SYS;
}

tstring TraceMath::GetCodeString()
{
	tstring stError(_T(""));

	switch(m_nCode)
	{	
	case MTE_NONE:
		stError	= _T("Succeed / No Error");
		break;	
	case MTE_ASSERT:
		stError	= _T("Assertion Failed");
		break;	

	case MTE_VECTOR:
		stError	= _T("Unexpected Vector");
		break;	
	case MTE_MATRIX:
		stError	= _T("Unexpected Matrix");
		break;	
	case MTE_NORM:
		stError	= _T("Unexpected Norm");
		break;	
	case MTE_DOMAIN:
		stError	= _T("Domain of Definition");
		break;	
	case MTE_INDEX:
		stError	= _T("Unexpected Index");
		break;	
	case MTE_DIMENSION:
		stError	= _T("Unexpected Dimension");
		break;	

	case UNDEF:
	default:
		stError	= _T("Unknown Error Code");
		break;
	}

	return stError;
}

tstring TraceMath::Detailed()
{
	tstring stDetails = _T("");

	stDetails	+= _T("ROOT: ");
	stDetails	+= to_tstring(Source());
	stDetails	+= _T(" - ");
	stDetails	+= GetSourceString();

	stDetails	+= _T("\nCODE: ");
	stDetails	+= to_tstring(m_nCode);
	stDetails	+= _T(" - ");
	stDetails	+= GetCodeString();

	if(m_stText.size() != 0)
	{
		stDetails	+= _T("\nTEXT: ");
		stDetails	+= m_stText;
	}

	stDetails	+= _T("\nFILE: ");
	stDetails	+= m_stFile;

	stDetails	+= _T("\nTASK: ");
	stDetails	+= m_stFunction;

	stDetails	+= _T("\nLINE: ");
	stDetails	+= to_tstring(m_nLine);

	return stDetails;
}

} // namespace