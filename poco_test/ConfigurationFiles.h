#include "Poco/AutoPtr.h"
#include "Poco/Util/IniFileConfiguration.h"
using Poco::AutoPtr;
using Poco::Util::IniFileConfiguration;

void testIniFileConfiguration()
{
	AutoPtr<IniFileConfiguration> pConf(new IniFileConfiguration("test.ini"));
	std::string path = pConf->getString("MyApplication.somePath");
	int value = pConf->getInt("MyApplication.someValue");
	value = pConf->getInt("myapplication.SomeValue");
	value = pConf->getInt("myapplication.SomeOtherValue", 456);
}

#include "Poco/AutoPtr.h"
#include "Poco/Util/PropertyFileConfiguration.h"
using Poco::AutoPtr;
using Poco::Util::PropertyFileConfiguration;

void testPropertyFileConfiguration()
{
	AutoPtr<PropertyFileConfiguration> pConf;
	pConf = new PropertyFileConfiguration("test.properties");

	std::string key1 = pConf->getString("key1");
	int value = pConf->getInt("key2");
	std::string longVal = pConf->getString("key3.longValue");
}

#include "Poco/AutoPtr.h"
#include "Poco/Util/XMLConfiguration.h"
using Poco::AutoPtr;
using Poco::Util::XMLConfiguration;

void testXMLConfiguration()
{
	AutoPtr<XMLConfiguration> pConf(new XMLConfiguration("test_ini.xml"));

	std::string prop1 = pConf->getString("prop1");
	int prop2 = pConf->getInt("prop2");
	std::string prop3 = pConf->getString("prop3"); // ""
	std::string prop4 = pConf->getString("prop3.prop4"); // ""
	prop4 = pConf->getString("prop3.prop4[@attr]"); // "value3"
	prop4 = pConf->getString("prop3.prop4[1][@attr]"); // "value4"
}