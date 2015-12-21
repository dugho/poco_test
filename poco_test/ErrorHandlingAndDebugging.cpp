#include "Poco/Debugger.h"

#include "Poco/NestedDiagnosticContext.h"
#include <iostream>

void f1()
{
	poco_ndc (f1);

	Poco::NDC::current().dump(std::cout);
	Poco::Debugger::enter("hello debugger...");
}

void f2()
{
	poco_ndc (f2);
	f1();
}

#include "ErrorHandlingAndDebugging.h"
#include "Poco/Bugcheck.h"
#include "MyException.h"
#include <string>

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