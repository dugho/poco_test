#ifndef PocoException_INCLUDED
#define PocoException_INCLUDED

#include "Poco/Exception.h"

#if !defined(MyLib_API)
	#define MyLib_API
#endif

POCO_DECLARE_EXCEPTION(MyLib_API, MyException, Poco::Exception)

#endif	// PocoException_INCLUDED