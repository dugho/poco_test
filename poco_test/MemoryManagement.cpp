#include "MemoryManagement.h"

void testMemoryPool()
{
	MemoryPool pool(10); // unlimited number of 1024 byte blocks
	// MemoryPool pool(1024, 4, 16); // at most 16 blocks; 4 preallocated
	char* buffer = reinterpret_cast<char*>(pool.get());
	std::cin.read(buffer, pool.blockSize());
	std::streamsize n = std::cin.gcount();
	std::string s(buffer, n);
	pool.release(buffer);

	std::cout << s << std::endl;
}
void testBuffer()
{
	Buffer<char> buffer(10);

	std::cin.read(buffer.begin(), buffer.size());
	std::streamsize n = std::cin.gcount();
	std::string s(buffer.begin(), n);
	std::cout << s << std::endl;
}

void testDynamicFactoryInstanciator()
{
	class Base	{
	public:
		virtual int getC() = 0;
	};
	class A: public Base {
	public:
		int getC() { return 0; };
	};
	class C: public Base {
	public:
		C(int i): _i(i)	{}
		int getC() { return _i; };
	private:
		int _i;
	};

	class CInstantiator: public AbstractInstantiator<Base>
	{
	public:
		CInstantiator(int i): _i(i)	{}
		Base* createInstance() const
		{
			return new C(_i);
		}
	private:
		int _i;
	};

	DynamicFactory<Base> factory;
	factory.registerClass<A>("A");
	factory.registerClass("C", new CInstantiator(42));

	SharedPtr<Base> pA = factory.createInstance("A");
	SharedPtr<Base> pC = factory.createInstance("C");

	int i = pC->getC();
}
void testDynamicFactory()
{
	class Base	{};
	class A: public Base {};
	class B: public Base {};

	DynamicFactory<Base> factory;
	factory.registerClass<A>("Ace"); // creates Instantiator<A, Base>
	factory.registerClass<B>("B"); // creates Instantiator<B, Base>
	SharedPtr<Base> pA = factory.createInstance("Ace");
	SharedPtr<Base> pB = factory.createInstance("B");
	// you can unregister classes
	factory.unregisterClass("B");
	// you can also check for the existence of a class
	bool haveA = factory.isClass("Ace"); // true
	bool haveB = factory.isClass("B"); // false (unregistered)
	bool haveC = factory.isClass("C"); // false (never registered)
}

void testArrayRelease()
{	
	char* pStr = new char[100];
	SharedPtr<char, Poco::ReferenceCounter, Poco::ReleaseArrayPolicy<char>> p(pStr);
}
void testCastOfSharedPtr()
{
	class A
	{
	public:
		virtual ~A()
		{}
	};
	class B: public A
	{
	};
	class C: public A
	{
	};

	Poco::SharedPtr<A> pA;
	Poco::SharedPtr<B> pB(new B);
 	pA = pB; // okay, pB is a subclass of pA
 	pA = new B;
 
 	// pB = pA; // will not compile
 	pB = pA.cast<B>(); // okay
 	Poco::SharedPtr<C> pC(new C);
 	// pB = pC.cast<B>(); // pB is null --> NOT COMPILE
}
void testSharedPtr()
{
	std::string* pString = new std::string("Hello, World!!");

	Poco::SharedPtr<std::string> p1(pString);
	std::cout << "referenceCount of p1 = " << p1.referenceCount() << std::endl << std::endl;

	Poco::SharedPtr<std::string> p2(p1);
	std::cout << "referenceCount of p1 = " << p1.referenceCount() << std::endl;
	std::cout << "referenceCount of p2 = " << p2.referenceCount() << std::endl << std::endl;

	p2 = 0;
	std::cout << "referenceCount of p1 = " << p1.referenceCount() << std::endl;
	std::cout << "referenceCount of p2 = " << p2.referenceCount() << std::endl << std::endl;
	//p2 = pString;	// BAD BAD BAD: multiple owners -> multiple delete
	p2 = p1;
	std::cout << "referenceCount of p1 = " << p1.referenceCount() << std::endl;
	std::cout << "referenceCount of p2 = " << p2.referenceCount() << std::endl << std::endl;

	std::string::size_type len = p1->length();
	std::cout << *p1 << std::endl;

}
void testAutoReleasePool()
{
	class C {
	public:
		C(){};
		void release(){ delete this; }; 
	};

	AutoReleasePool<C> pool;

	C* pC = new C;
	pool.add(pC);
	pC = new C;
	pool.add(pC);
	pool.release();

	return;
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