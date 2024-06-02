#pragma once
// [MAJOR].[MINOR].[REVISION].[BUILD]

// support macros
#define VERSION_NAME(arg) #arg								// return string macro name
#define VERSION_VALUE(arg) VERSION_NAME(arg)				// return string macro value

// version
#define VERSION_MAJOR		0								// compatibility
#define VERSION_MINOR		0								// feature / functional add on
#define VERSION_REVISION	0								// bugfix
#define VERSION_BUILD		0								// build / clean up / process / ...


#define VERSION_STRING		VERSION_VALUE(VERSION_MAJOR) "." VERSION_VALUE(VERSION_MINOR) "." \
							VERSION_VALUE(VERSION_REVISION) "." VERSION_VALUE(VERSION_BUILD)