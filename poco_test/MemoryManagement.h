#ifndef MemoryManagement_INCLUDED
#define MemoryManagement_INCLUDED

#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"
#include <iostream>

using Poco::RefCountedObject;
using Poco::AutoPtr;

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