// poco_test.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Poco/Bugcheck.h"
#include "MyException.h"

void assertionTest();
void myExceptionTest();
void exceptionTest();

int _tmain(int argc, _TCHAR* argv[])
{	
	assertionTest();
	//myExceptionTest();
	//exceptionTest();

	getchar();
	return 0;
}

void assertionTest()
{
	int i = 0;

	poco_assert (i >= 1 && i < 3);

	switch (i)
	{
	case 1:
			break;
	case 2:
			break;
	default:
		poco_bugcheck_msg("i has invalid value");
	}
}

void myExceptionTest()
{
	try
	{
		throw MyException();
	}
	catch (MyException& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}
	
}

void exceptionTest()
{
	Poco::Exception* pExc = 0;
	try
	{
		throw Poco::ApplicationException("just testing");
	}
	catch (Poco::Exception& exc)
	{
		pExc = exc.clone();
	}
	try
	{
		pExc->rethrow();
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}
	delete pExc;
}