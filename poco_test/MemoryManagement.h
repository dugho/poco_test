#ifndef MemoryManagement_INCLUDED
#define MemoryManagement_INCLUDED

#include "Poco/AutoPtr.h"
using Poco::AutoPtr;

void rco_test();

class RCO
{
public:
	RCO(): _refCount(1)
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