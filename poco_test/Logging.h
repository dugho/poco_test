#include "Poco/Logger.h"
using Poco::Logger;

void testLogger()
{
	Logger& logger = Logger::get("TestLogger");

	logger.information("This is an informational message");
	logger.warning("This is a warning message");
}


#include "Poco/SimpleFileChannel.h"
#include "Poco/Logger.h"
#include "Poco/AutoPtr.h"
using Poco::SimpleFileChannel;
using Poco::Logger;
using Poco::AutoPtr;

void testSimpleFileChannel()
{
	AutoPtr<SimpleFileChannel> pChannel(new SimpleFileChannel);

	pChannel->setProperty("path", "testSimpleFileChannel.log");	// 로그파일이 기록되지 않네??? 왜지?? 
																// 해결 ==> Logger::get() 호출시 testLogger()에서 사용했던 source name과 같은 명칭을 사용했기 때문이다.
	pChannel->setProperty("rotation", "2 M");

	Logger::root().setChannel(pChannel);
	Logger& logger = Logger::get("testSimpleFileChannel"); // inherits root channel

	for (int i = 0; i < 100; ++i)
		logger.information("Testing SimpleFileChannel");
}

#include "Poco/Logger.h"
#include "Poco/FileChannel.h"
#include "Poco/AutoPtr.h"
using Poco::Logger;
using Poco::FileChannel;
using Poco::AutoPtr;

void testFileChannel()
{
	AutoPtr<FileChannel> pChannel(new FileChannel);

	pChannel->setProperty("path", "testFileChannel.log");
	pChannel->setProperty("rotation", "2 M");
	pChannel->setProperty("archive", "timestamp");

	Logger::root().setChannel(pChannel);

	Logger& logger = Logger::get("testFileChannel"); // inherits root channel

	for (int i = 0; i < 100; ++i)
		logger.information("Testing FileChannel");
}

#include "Poco/Logger.h"
#include "Poco/AsyncChannel.h"
#include "Poco/ConsoleChannel.h"
#include "Poco/AutoPtr.h"
using Poco::Logger;
using Poco::AsyncChannel;
using Poco::ConsoleChannel;
using Poco::AutoPtr;

void testAsyncChannel()
{
	AutoPtr<ConsoleChannel> pCons(new ConsoleChannel);
	AutoPtr<AsyncChannel> pAsync(new AsyncChannel(pCons));

	Logger::root().setChannel(pAsync);
	Logger::root().setChannel(pCons);
	Logger& logger = Logger::get("testAsyncChannel");
	
	for (int i = 0; i < 10; ++i)
		logger.information("testAsyncChannel : This is a test");
}

#include "Poco/Logger.h"
#include "Poco/SplitterChannel.h"
#include "Poco/ConsoleChannel.h"
#include "Poco/FileChannel.h"
#include "Poco/AutoPtr.h"
using Poco::Logger;
using Poco::SplitterChannel;
using Poco::ConsoleChannel;
using Poco::FileChannel;
using Poco::AutoPtr;

void testSplitterChannel()
{
	AutoPtr<ConsoleChannel> pCons(new ConsoleChannel);
	AutoPtr<SimpleFileChannel> pFile(new SimpleFileChannel("testSplitterChannel.log"));
	AutoPtr<SplitterChannel> pSplitter(new SplitterChannel);

	pSplitter->addChannel(pCons);
	pSplitter->addChannel(pFile);

	Logger::root().setChannel(pSplitter);
	Logger& logger = Logger::get("testSplitterChannel");
	for (int i=0; i<10; ++i)
		logger.information("testSplitterChannel : This is a test");
}

#include "Poco/LogStream.h"
#include "Poco/Logger.h"
using Poco::Logger;
using Poco::LogStream;

void testLogStream()
{
	Logger& logger = Logger::get("TestLogger");
	LogStream lstr(logger);

	lstr << "This is a test" << std::endl;
}

#include "Poco/ConsoleChannel.h"
#include "Poco/FormattingChannel.h"
#include "Poco/PatternFormatter.h"
#include "Poco/Logger.h"
#include "Poco/AutoPtr.h"
using Poco::ConsoleChannel;
using Poco::FormattingChannel;
using Poco::PatternFormatter;
using Poco::Logger;
using Poco::AutoPtr;

void testFormatter()
{
	AutoPtr<ConsoleChannel> pCons(new ConsoleChannel);
	AutoPtr<PatternFormatter> pPF(new PatternFormatter);
	pPF->setProperty("pattern", "%Y-%m-%d %H:%M:%S %s: %t");
	AutoPtr<FormattingChannel> pFC(new FormattingChannel(pPF, pCons));

	Logger::root().setChannel(pFC);
	Logger::root().setChannel(pCons);
	Logger::get("testFormatter").information("This is a test");
}

