// poco_test.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "ErrorHandlingAndDebugging.h"
#include "MemoryManagement.h"

int _tmain(int argc, _TCHAR* argv[])
{	
	//-- MemoryManagement --//
	// AutoPtr Operators and Semantics
	assignAutoPtr2PlainPtr();
	//cast_test();
	//ReferencCountedObject_test();
	//ReferencCounting_test();

	//-- ErrorHandlingAndDebugging --//
	//f2();
	//assertionTest();
	//myExceptionTest();
	//exceptionTest();

	getchar();
	return 0;
}
