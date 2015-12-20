#include "StdAfx.h"
#include "MyException.h"

POCO_IMPLEMENT_EXCEPTION(MyException, Poco::Exception, "MyException : Something really bad happened...")
