#include <string>
#include <string.h>
#include <iostream>
#include "SmartPointer.h"
using namespace Engine;

class GameObject {
public:
	GameObject() { i_data = ""; }
	GameObject(std::string data, int flag) : i_data(data), i_flag(flag) {}
	std::string i_data;
	int i_flag = 0;
	void SetFlag(int flag) { i_flag = flag; }
};

class TestHeri : public GameObject{
public:
	TestHeri() { i_data = ""; own = 1; i_flag = 4; }
	int own = 1;
};

bool TestStrongPointer() {
	// test constructor
	OwningPointer<GameObject> MyPtr1(new GameObject("Joe", 1));
	OwningPointer<GameObject> MyPtr2(MyPtr1);
	if (!(MyPtr2 == MyPtr1) || MyPtr2 != MyPtr1) {
		std::cout << "Test constructor method equality failed!" << std::endl;
		return false;
	}

	GameObject* myObject = new GameObject("test1", 2);
	OwningPointer<GameObject> MyPtr3, MyPtr4;
	// test bool() 
	if (MyPtr3 || !MyPtr1) {
		std::cout << "Test bool() error!" << std::endl;
		return false;
	}
	
	// test assignment
	MyPtr3 = myObject;
	MyPtr4 = MyPtr3;
	if (!(MyPtr3 == MyPtr4) || MyPtr3 != MyPtr4) {
		std::cout << "Test assignment method equality failed!" << std::endl;
		return false;
	}

	// test self assignment
	auto countRef = MyPtr3.GetReferenceCounters();
	auto oldOwnerValue = countRef.OwnerReferences;
	MyPtr3 = MyPtr3;
	if (oldOwnerValue != countRef.OwnerReferences) {
		std::cout << "Test self assignment method equality failed!" << std::endl;
		return false;
	}

	// test owning object method
	MyPtr1->SetFlag(10);
	if (MyPtr1->i_flag != 10) {
		std::cout << "Test accessing the method of owning object failed!" << std::endl;
		return false;
	}

	// test inheritance
	OwningPointer<TestHeri> MyPtr5(new TestHeri());
	OwningPointer<GameObject> MyPtr6(MyPtr5);
	MyPtr3 = MyPtr5;
	if (!(MyPtr5 == MyPtr6) || !(MyPtr6 == MyPtr5) || (MyPtr5 != MyPtr6) ||
		!(MyPtr3 == MyPtr6) || (MyPtr3 != MyPtr6)  ||
		!(MyPtr3 == MyPtr5) || !(MyPtr5 == MyPtr3) || (MyPtr3 != MyPtr5)) {
		std::cout << "Test inheritance equality failed!" << std::endl;
		return false;
	}	
	if (MyPtr4.GetReferenceCounters().OwnerReferences != 1) {
		std::cout << "Test reassignment failed!" << std::endl;
		return false;
	}
	MyPtr6->i_data = "test 123";
	if (MyPtr5->i_data != "test 123") {
		std::cout << "Test assignment in base class failed!" << std::endl;
		return false;
	}
	MyPtr6 = nullptr;
	return true;
}


bool SmartPtrUnitTest() {
	return TestStrongPointer();
}