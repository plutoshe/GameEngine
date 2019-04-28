#include <iostream>
#include <assert.h>

extern bool SmartPtrUnitTest();
extern bool TestContainers();

int main() {
	assert(SmartPtrUnitTest());
	std::cout << "Pass smarter point test" << std::endl;
	assert(TestContainers());
	std::cout << "Pass container test" << std::endl;
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
	assert(_CrtDumpMemoryLeaks() == 0);
	std::cout << "No Memory Leak" << std::endl;
	return 0;
}

//
//#include <iostream>
//#include "SmartPointer.h"
//using namespace std;
//
//class Base
//{
//public:
//	virtual void f(float x) { cout << "Base::f(float) " << x << endl; }
//	virtual void g(float x) { cout << "Base::g(float) " << x << endl; }
//	void h(float x) { cout << "Base::h(float) " << x << endl; }
//};
//
//class Derived : public Base
//{
//public:
//	virtual void f(float x) { cout << "Derived::f(float) " << x << endl; }
//	virtual void g(int x) { cout << "Derived::g(int) " << x << endl; }
//	void h(float x) { cout << "Derived::h(float) " << x << endl; }
//};
//
//int main()
//{
//	Derived  d;
//	Base *pb = &d;
//	Derived *pd = &d;
//
//	// Good : behavior depends solely on type of the object
//	pb->f(3.14f); // Derived::f(float) 3.14
//	pd->f(3.14f); // Derived::f(float) 3.14
//
//	// Bad : behavior depends on type of the pointer
//	pb->g(3.14f); // Base::g(float) 3.14 (surprise!)
//	pd->g(3.14f); // Derived::g(int) 3
//
//	// Bad : behavior depends on type of the pointer
//	pb->h(3.14f); // Base::h(float) 3.14  (surprise!)
//	pd->h(3.14f); // Derived::h(float) 3.14
//
//	Engine::OwningPointer<Derived> ob1(d);
//	Engine::OwningPointer<Base> pb1(ob1);
//	Engine::OwningPointer<Derived> pd1(d);
//
//	// Good : behavior depends solely on type of the object
//	pb1->f(3.14f); // Derived::f(float) 3.14
//	pd1->f(3.14f); // Derived::f(float) 3.14
//
//	// Bad : behavior depends on type of the pointer
//	pb1->g(3.14f); // Base::g(float) 3.14 (surprise!)
//	pd1->g(3.14f); // Derived::g(int) 3
//
//	// Bad : behavior depends on type of the pointer
//	pb1->h(3.14f); // Base::h(float) 3.14  (surprise!)
//	pd1->h(3.14f); // Derived::h(float) 3.14
//
//	return 0;
//}