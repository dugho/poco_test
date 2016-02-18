#include "Poco/LRUCache.h"

void testLRUCache()
{
	Poco::LRUCache<int, std::string> myCache(3);
	myCache.add(1, "Lousy"); // |-1-| -> first elem is the most popular one
	Poco::SharedPtr<std::string> ptrElem = myCache.get(1); // |-1-|

	myCache.add(2, "Morning"); // |-2-1-|
	myCache.add(3, "USA"); // |-3-2-1-|

	// now get rid of the most unpopular entry: "Lousy"
	myCache.add(4, "Good"); // |-4-3-2-|
	poco_assert (*ptrElem == "Lousy"); // content of ptrElem is still valid

	ptrElem = myCache.get(2); // |-2-4-3-|

	// replace the morning entry with evening
	myCache.add(2, "Evening"); // 2 Events: Remove followed by Add
}

#include "Poco/UniqueExpireCache.h"
#include "Poco/ExpirationDecorator.h"
#include "Poco/Thread.h"

void testUniqueExpirationCache()
{
	typedef Poco::ExpirationDecorator<std::string> ExpString;

	Poco::UniqueExpireCache<int, ExpString> myCache;
	myCache.add(1, ExpString("test", 500)); // expires after 500ms
	myCache.add(2, ExpString("test", 1500)); // expires after 1500ms
	poco_assert (myCache.size() == 2);

	// 1 second passes...
	Poco::Thread::sleep(1000);
	poco_assert (myCache.size() == 1);
	Poco::SharedPtr<ExpString> ptrVal = myCache.get(1);
	poco_assert (ptrVal.isNull());
}