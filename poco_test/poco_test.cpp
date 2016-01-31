// poco_test.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "ErrorHandlingAndDebugging.h"
#include "MemoryManagement.h"

int _tmain(int argc, _TCHAR* argv[])
{	
	//-- MemoryManagement --//
	//- Dynamic Class Factory
	testDynamicFactoryInstanciator();
	//testDynamicFactory();

	//- SharedPtr Operators and Semantics
	//testArrayRelease();
	//testCastOfSharedPtr();
	//testSharedPtr();

	//- AutoPtr Operators and Semantics
	//testAutoReleasePool();
	//assignAutoPtr2PlainPtr();
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
