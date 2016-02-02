#ifndef MemoryManagement_INCLUDED
#define MemoryManagement_INCLUDED

#include "Poco/SingletonHolder.h"
class MySingleton
{
public:
	MySingleton()
	{
		// ...
	}
	~MySingleton()
	{
		// ...
	}
	// ...
	static MySingleton& instance()
	{
		static Poco::SingletonHolder<MySingleton> sh;
		return *sh.get();
	}
};


#include "Poco/MemoryPool.h"
#include <string>
#include <iostream>
using Poco::MemoryPool;

void testMemoryPool();


#include <Poco/Buffer.h>
#include <string>
#include <iostream>
using Poco::Buffer;

void testBuffer();


#include "Poco/DynamicFactory.h"
#include "Poco/SharedPtr.h"
using Poco::DynamicFactory;
using Poco::AbstractInstantiator;
using Poco::SharedPtr;

void testDynamicFactoryInstanciator();
void testDynamicFactory();

#include <string>
#include <iostream>
using Poco::SharedPtr;

void testArrayRelease();
void testCastOfSharedPtr();
void testSharedPtr();


#include "Poco/AutoReleasePool.h"
using Poco::AutoReleasePool;

void testAutoReleasePool();


#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"
#include <iostream>

using Poco::RefCountedObject;
using Poco::AutoPtr;

void assignAutoPtr2PlainPtr();
void cast_test();

void ReferencCountedObject_test();

class ReferencCountedObject: public RefCountedObject
{
public:
	ReferencCountedObject()
	{}

	void greet() const
	{
		std::cout << "Hello, world!" << std::endl;
	}

protected:
	~ReferencCountedObject()
	{}
};

#include "Poco/AutoPtr.h"
using Poco::AutoPtr;

void ReferencCounting_test();

class ReferencCounting
{
public:
	ReferencCounting(): _refCount(1)
	{}
	void duplicate()
	{
		++_refCount; // Warning: not thread safe!
	}
	void release()
	{
		if (--_refCount == 0) delete this; // Warning: not thread safe!
	}

	void print_refCount()
	{
		std::cout << "refCount = " << _refCount << "\n";
	}

private:
	int _refCount;
};

#endif	// MemoryManagement_INCLUDED