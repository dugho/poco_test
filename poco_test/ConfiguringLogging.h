#include "Poco/ConsoleChannel.h"
#include "Poco/FileChannel.h"
#include "Poco/SplitterChannel.h"
#include "Poco/FormattingChannel.h"
#include "Poco/PatternFormatter.h"
#include "Poco/Logger.h"
#include "Poco/Util/PropertyFileConfiguration.h"
#include "Poco/Util/LoggingConfigurator.h"
#include "Poco/AutoPtr.h"

using Poco::ConsoleChannel;
using Poco::FileChannel;
using Poco::SplitterChannel;
using Poco::FormattingChannel;
using Poco::PatternFormatter;
using Poco::Logger;
using Poco::Util::PropertyFileConfiguration;
using Poco::Util::LoggingConfigurator;
using Poco::AutoPtr;

void testLoggingConfigurator()
{
	AutoPtr<PropertyFileConfiguration> pConfig;
	pConfig = new PropertyFileConfiguration("logging.properties");

	LoggingConfigurator configurator;
	configurator.configure(pConfig);

	Logger& root = Logger::get("");
	root.warning("Root Logger : warning");
	root.information("Root Logger : information");

	Logger& logger1 = Logger::get("logger1");
	logger1.information("Logger#1 : information");
	logger1.critical("Logger#1 : critical");

	Logger& logger2 = Logger::get("logger2");
	logger2.debug("Logger#2 : debug");
}