#pragma once

namespace sys
{
//+-----------------------------------------------------------------------------+
//! math tracer error defines													!
//+-----------------------------------------------------------------------------+
#define MTE_NONE		0
#define MTE_ASSERT		1

// unexpected
#define MTE_VECTOR		1000
#define MTE_MATRIX		1001
#define MTE_NORM		1002	
#define MTE_DOMAIN		1003
#define MTE_INDEX		1004
#define MTE_DIMENSION	1005


//+-----------------------------------------------------------------------------+
//! system tracer																!
//+-----------------------------------------------------------------------------+
struct TraceMath : public SystemTracer
{
public:
	TraceMath(const uint32_t&, const _TCHAR*, const _TCHAR*, const _TCHAR*, const uint32_t&);
	~TraceMath();

private:	
	TraceMath() = delete;	
	TraceMath(const TraceMath&) = delete;
	TraceMath& operator=(const TraceMath&) = delete;

public:
	uint32_t	m_nCode;
	tstring			m_stText;

public:
	virtual uint32_t Source();	
	virtual tstring Detailed();

private:
	tstring GetCodeString();
};

} // namespace