#pragma once

#define SERIAL_CF_TEXT_MAX_BYTE		512

namespace serial_cf  // serialize container file
{
//+-----------------------------------------------------------------------------+
//! container file typedef														!
//+-----------------------------------------------------------------------------+
typedef uint32_t	CFT_TB; // container file type _ text byte
typedef uintmax_t	CFT_DB; // container file type _ data byte

//+-----------------------------------------------------------------------------+
//! SCFP_INFO serialize container file parser info								!
//+-----------------------------------------------------------------------------+
struct SCFP_INFO
{
public:
	SCFP_INFO();
	~SCFP_INFO();

	SCFP_INFO(const SCFP_INFO&);
	SCFP_INFO& operator=(const SCFP_INFO&);

	void Clear();

public:
	tstring		m_stTextId;
	CFT_DB		m_nCfByteOffset;
	CFT_DB		m_nDataByteSize;
};

typedef std::list<SCFP_INFO> STL_SCFP_INFO;

//+-----------------------------------------------------------------------------+
//! container file parser functions												!
//+-----------------------------------------------------------------------------+
uint32_t PackData(FILE*, const TCHAR*, void*, const CFT_DB&);
uint32_t ParseConatinerFileInfo(FILE*, STL_SCFP_INFO&);
uint32_t UnpackData(FILE*, const SCFP_INFO&, void*, const CFT_DB&);

} // namespace