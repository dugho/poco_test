// TestLibrary.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//

#include "stdafx.h"

#include <iostream>

#if defined(_WIN32)
#define LIBRARY_API __declspec(dllexport)
#else
#define LIBRARY_API
#endif

// 아래 두 줄을 사용하면 컴파일시 lib에서 hello()를 링크시키지 못한다.
//extern "C" void LIBRARY_API hello();
//void hello() { std::cout << "Hello, world!" << std::endl;}

LIBRARY_API void hello()
{
	std::cout << "Hello, world!" << std::endl;
}

/*-- http://exportidea.blogspot.kr/2013/08/windows-dll.html 참고함
#include <iostream>

__declspec(dllexport) void hello()
{
	std::cout << "Hello, world!" << std::endl;
}
*/