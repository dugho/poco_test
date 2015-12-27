#include "MemoryManagement.h"

void rco_test()
{
	RCO* pNew = new RCO; // _rc == 1
	pNew->print_refCount();

	AutoPtr<RCO> p1(pNew); // _rc == 1
	pNew->print_refCount();

	AutoPtr<RCO> p2(p1); // _rc == 2
	pNew->print_refCount();

	AutoPtr<RCO> p3(pNew, true); // _rc == 3
	pNew->print_refCount();

	p2 = 0; // _rc == 2
	pNew->print_refCount();

	p3 = 0; // _rc == 1
	pNew->print_refCount();

	RCO* pRCO = p1; // _rc == 1
	pNew->print_refCount();

	p1 = 0; // _rc == 0 -> deleted
	pNew->print_refCount();

	// pRCO and pNew now invalid!
	p1 = new RCO; // _rc == 1
	pNew->print_refCount();

	return;
}