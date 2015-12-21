// poco_byte_order.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

// #include "Poco/ByteOrder.h"
// #include <iostream>
// using Poco::ByteOrder;
// using Poco::UInt16;
// using Poco::UInt32;

// #include "Poco/Any.h"
// #include "Poco/Exception.h"
// using Poco::Any;
// using Poco::AnyCast;
// using Poco::RefAnyCast;

#include "Poco/DynamicAny.h"
#include "Poco/Exception.h"
using Poco::DynamicAny;

int _tmain(int argc, _TCHAR* argv[])
{
// #ifdef POCO_ARCH_LITTLE_ENDIAN
// 	std::cout << "little endian" << std::endl;
// #else
// 	std::cout << "big endian" << std::endl;
// #endif
// 	UInt16 port = 80;
// 	UInt16 networkPort = ByteOrder::toNetwork(port);
// 
// 	Any any(1);
// 	int i = AnyCast<int>(any); // okay
// 	int& ri = RefAnyCast<int>(any); // okay
// 
// 	std::cout << "i = " << i << "\n";
// 	std::cout << "ri = " << ri << "\n";
// 
// 	any = std::string("any string test");
// 	std::string str = AnyCast<std::string>(any);
// 	std::cout << "any = " << str << "\n";
// 
// 	try
// 	{
// 		short s = AnyCast<short>(any); // throws BadCastException
// 	}
// 	catch (Poco::BadCastException&)
// 	{
// 		std::cout << "AnyCast to short exception...";
// 	}

	DynamicAny any(42);
	int i = any;
	std::string s(any.convert<std::string>());
	any.convert(s); // or without the need to cast
	const int& ri(any.extract<int>());
	short s = any;
	try
	{
		short s = any.extract<short>(); // throws BadCastException
	}
	catch (Poco::BadCastException&)
	{
	}

	getchar();
	return 0;
}

