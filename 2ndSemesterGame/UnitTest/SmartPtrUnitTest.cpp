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

bool TestStrongPointer() {
	GameObject* myObject = new GameObject("test1", 2);
	OwningPointer<GameObject> MyPtr1(new GameObject("Joe", 1));
	OwningPointer<GameObject> MyPtr2(myObject);
	OwningPointer<GameObject> MyPtr3;
	MyPtr3 = myObject;

	MyPtr1->SetFlag(10);
	if (MyPtr1->i_flag != 10) {
		std::cout << "Test accessing the method of owning object failed!" << std::endl;
		return false;
	}
}


bool SmartPtrUnitTest() {
	return TestStrongPointer();
}