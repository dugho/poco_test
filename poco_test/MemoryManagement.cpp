#include "MemoryManagement.h"

void testAutoReleasePool()
{

}

void assignAutoPtr2PlainPtr()
{
	class A: public Poco::RefCountedObject {};

	Poco::AutoPtr<A> p1(new A);

	A* pA = p1;
	// Poco::AutoPtr<A> p2(pA); // 컴파일은 되지만 BAD! p2 assumes sole ownership
	Poco::AutoPtr<A> p2(pA, true); // Okay: p2 shares ownership with p1
	std::cout << "refcount: " << p2->referenceCount() << std::endl;

	Poco::AutoPtr<A> p3;	
	//p3 = pA; // 컴파일은 되지만 BAD! p3 assumes sole ownership
	//std::cout << "refcount: " << p3->referenceCount() << std::endl; // refcount = 2

	p3.assign(pA, true); // Okay: p3 shares ownership with p1
	std::cout << "refcount: " << p3->referenceCount() << std::endl;
}

void cast_test()
{
	class A: public Poco::RefCountedObject {};
	class B: public A {};
	class C: public Poco::RefCountedObject {};

	Poco::AutoPtr<A> pA;
	Poco::AutoPtr<B> pB(new B);
	pA = pB; // okay, pB is a subclass of pA
	pA = new B;
	
	//pB = pA; // will not compile
	pB = pA.cast<B>(); // okay
	Poco::AutoPtr<C> pC(new C);
	pA = pC.cast<A>(); // pA is null
}

void ReferencCountedObject_test()
{
	AutoPtr<ReferencCountedObject> pRCO(new ReferencCountedObject);

	pRCO->greet(); // AutoPtr has -> operator
	(*pRCO).greet(); // AutoPtr has * operator
	std::cout << "refcount: " << pRCO->referenceCount() << std::endl;

	ReferencCountedObject* p1 = pRCO; // AutoPtr supports conversion to plain pointer
	std::cout << "refcount: " << pRCO->referenceCount() << std::endl;	// plain pointer 사용시 reference count 유지

	ReferencCountedObject* p2 = pRCO.get();
	std::cout << "refcount: " << pRCO->referenceCount() << std::endl;

	AutoPtr<ReferencCountedObject> p3(pRCO);
	std::cout << "refcount: " << pRCO->referenceCount() << std::endl;	// AutoPtr 사용시 reference count 증가

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