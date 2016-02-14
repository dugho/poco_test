// poco_test.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "ErrorHandlingAndDebugging.h"
#include "MemoryManagement.h"
#include "StringsAndFormatting.h"
#include "PlatformAndEnvironment.h"
#include "RandomNumbersAndCryptographicHashes.h"
#include "DateAndTime.h"
#include "Files.h"
#include "NotifiationAndEvent.h"
#include "Streams.h"
#include "Logging.h"

int _tmain(int argc, _TCHAR* argv[])
{	
	//-- Logging --//
	testLogger();
	testSimpleFileChannel();
	testFileChannel();
	testAsyncChannel();
	testSplitterChannel();
	testLogStream();
	testFormatter();

	//-- Streams --//
// 	testBase64Encoder();
// 	testDeflatingStream();
// 	testTeeStream();
// 	testOfstream();
// 	testBinaryWriter();
// 	testBinaryReader();
// 	testUnbufferedStreamBuf();

	//-- Notification and Event --//
// 	testNotificationPolymorphism();
// 	testNotificationQueue();
// 	testEvent();

	//-- Files --//
// 	testPath();
// 	testParsingPath();
// 	workingWithPath();
// 	testPathOperation();
// 	systemSpecificDir();
// 	pathAndEnvironmentVar();
// 	findFile();
// 	testFileOperation();
// 	testDirectoryIterator();
// 	testGlob();
// 	testTemporaryFile();

	//-- Date and Time --//	
// 	testTimeStamp();
// 	testDateTime();
// 	testLocalDateTime();
// 	testTimespan();
// 	testTimeCalculstion();
// 	testTimezone();
// 	testDateTimeFormat();
// 	testDateTimeParser();

	//-- Random Numbers and Cryptographical Hashes --//
// 	testRandom();
// 	testDigestEngine();
// 	testDigestStream();

	//-- Platform and Environment --//
	//testEnvironmentVariables();

	//-- Strings, Text and Formatting --//
// 	testString();
// 	testCaseInsensitiveComparison();
// 	testTranslate();
// 	testReplace();
// 	testConcatenate();
// 	testNumberFormatter();
// 	testFormat();
// 	testStringTokenizer();
// 	testRegularExpression();
// 	testTextConverterOfEncodings();
// 	testStreamConverter();
// 	testTextIterator_UnicodeChar();

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
