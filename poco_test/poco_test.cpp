// poco_test.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "ErrorHandlingAndDebugging.h"
#include "MemoryManagement.h"

int _tmain(int argc, _TCHAR* argv[])
{	
	//-- MemoryManagement --//
	//- SingletonHolder : refer to MySingleton class in MemoryManagement.h

	//- Buffer Mgt.& Memory Pool
	//testMemoryPool();
	//testBuffer();

	//- Dynamic Class Factory
	//testDynamicFactoryInstanciator();
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
