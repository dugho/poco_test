#include "Poco/Environment.h"
#include <iostream>
using Poco::Environment;

void testEnvironmentVariables()
{
	std::cout
		<< "OS Name: " << Environment::osName() << std::endl
		<< "OS Version: " << Environment::osVersion() << std::endl
		<< "OS Arch: " << Environment::osArchitecture() << std::endl
		<< "Node Name: " << Environment::nodeName() << std::endl
		<< "Node ID: " << Environment::nodeId() << std::endl;

	if (Environment::has("HOME"))
		std::cout << "Home: " << Environment::get("HOME") << std::endl;

	Environment::set("POCO", "foo");
}