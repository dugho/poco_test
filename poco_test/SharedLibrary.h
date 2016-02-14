void testLoadDll()
{
	__declspec(dllimport) void hello();

	hello();
}

#include "Poco/SharedLibrary.h"
using Poco::SharedLibrary;
typedef void (*HelloFunc)(); // function pointer type

void testSharedLibrary()
{
	std::string path("..\\x64\\Debug\\TestLibrary.dll");
	//path.append(SharedLibrary::suffix()); // adds ".dll"(for Release), "d.dll"(for Debug) or ".so"

	SharedLibrary library(path); // will also load the library
	bool has = library.hasSymbol("hello");
	if (has)
	{
		HelloFunc func = (HelloFunc) library.getSymbol("hello");	// Symbol을 찾지 못하네?? 
		func();
	}	
	library.unload();
}

#include "Poco/ClassLoader.h"
#include "Poco/Manifest.h"
#include "..\PluginLibrary\AbstractPlugin.h"
#include <iostream>
typedef Poco::ClassLoader<AbstractPlugin> PluginLoader;
typedef Poco::Manifest<AbstractPlugin> PluginManifest;

void testClassLader()
{
	PluginLoader loader;
	std::string libName("..\\x64\\Debug\\PluginLibrary.dll");
	//libName += Poco::SharedLibrary::suffix(); // append .dll or .so
	loader.loadLibrary(libName);

	PluginLoader::Iterator it(loader.begin());
	PluginLoader::Iterator end(loader.end());

	for (; it != end; ++it)
	{
		std::cout << "lib path: " << it->first << std::endl;

		PluginManifest::Iterator itMan(it->second->begin());
		PluginManifest::Iterator endMan(it->second->end());

		for (; itMan != endMan; ++itMan)
			std::cout << itMan->name() << std::endl;
	}
	AbstractPlugin* pPluginA = loader.create("PluginA");
	AbstractPlugin* pPluginB = loader.create("PluginB");

	std::cout << pPluginA->name() << std::endl;
	std::cout << pPluginB->name() << std::endl;

	loader.classFor("PluginA").autoDelete(pPluginA);
	delete pPluginB;
	loader.unloadLibrary(libName);
}