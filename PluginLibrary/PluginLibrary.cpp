// PluginLibrary.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//

#include "stdafx.h"

#include "AbstractPlugin.h"
#include "Poco/ClassLibrary.h"
#include <iostream>

class PluginA: public AbstractPlugin
{
public:
	std::string name() const
	{
		return "PluginA";
	}
};

class PluginB: public AbstractPlugin
{
public:
	std::string name() const
	{
		return "PluginB";
	}
};

POCO_BEGIN_MANIFEST(AbstractPlugin)
	POCO_EXPORT_CLASS(PluginA)
	POCO_EXPORT_CLASS(PluginB)
POCO_END_MANIFEST

// optional set up and clean up functions
	void pocoInitializeLibrary()
{
	std::cout << "PluginLibrary initializing" << std::endl;
}

void pocoUninitializeLibrary()
{
	std::cout << "PluginLibrary UNinitializing" << std::endl;
}