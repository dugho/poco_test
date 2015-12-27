#include "MemoryManagement.h"

void ReferencCountedObject_test()
{
	AutoPtr<ReferencCountedObject> pRCO(new ReferencCountedObject);

	pRCO->greet(); // AutoPtr has -> operator
	(*pRCO).greet(); // AutoPtr has * operator
	std::cout << "refcount: " << pRCO->referenceCount() << std::endl;
	ReferencCountedObject* p1 = pRCO; // AutoPtr supports conversion to plain pointer
	ReferencCountedObject* p2 = pRCO.get();
}

void ReferencCounting_test()
{
	ReferencCounting* pNew = new ReferencCounting; // _rc == 1
	pNew->print_refCount();

	AutoPtr<ReferencCounting> p1(pNew); // _rc == 1
	pNew->print_refCount();

	AutoPtr<ReferencCounting> p2(p1); // _rc == 2
	pNew->print_refCount();

	AutoPtr<ReferencCounting> p3(pNew, true); // _rc == 3
	pNew->print_refCount();

	p2 = 0; // _rc == 2
	pNew->print_refCount();

	p3 = 0; // _rc == 1
	pNew->print_refCount();

	ReferencCounting* pReferencCounting = p1; // _rc == 1
	pNew->print_refCount();

	p1 = 0; // _rc == 0 -> deleted
	pNew->print_refCount();

	// pReferencCounting and pNew now invalid!
	p1 = new ReferencCounting; // _rc == 1
	pNew->print_refCount();

	return;
}