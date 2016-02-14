// TestLibrary.cpp : DLL ���� ���α׷��� ���� ������ �Լ��� �����մϴ�.
//

#include "stdafx.h"

#include <iostream>

#if defined(_WIN32)
#define LIBRARY_API __declspec(dllexport)
#else
#define LIBRARY_API
#endif

// �Ʒ� �� ���� ����ϸ� �����Ͻ� lib���� hello()�� ��ũ��Ű�� ���Ѵ�.
//extern "C" void LIBRARY_API hello();
//void hello() { std::cout << "Hello, world!" << std::endl;}

LIBRARY_API void hello()
{
	std::cout << "Hello, world!" << std::endl;
}

/*-- http://exportidea.blogspot.kr/2013/08/windows-dll.html ������
#include <iostream>

__declspec(dllexport) void hello()
{
	std::cout << "Hello, world!" << std::endl;
}
*/