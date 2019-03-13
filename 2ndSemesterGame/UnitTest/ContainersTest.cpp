#include <string>
#include <string.h>
#include <iostream>
#include "Vector4D.h"
#include "iostream"

bool TestVector4() {
	Vector4f a(1, 2, 3, 4);
	Vector4f b;
	Vector4f c;
	if (a[0] != 1 || a[1] != 2 || a[2] != 3 || a[3] != 4) {
		std::cout << "Test vector4d initialization failed!" << std::endl;
		return false;
	}
	b.x = 1; b.y = 2; b[2] = 3; b.w = 4;
	if (b[0] != 1 || b[1] != 2 || b[2] != 3 || b[3] != 4) {
		std::cout << "Test data assignment failed!" << std::endl;
		return false;
	}

	c = a;
	if (c != b) {
		std::cout << "Test self assignment method equality failed!" << std::endl;
		return false;
	}
	c += b;
	if (c.x != 2 || c.y != 4 || c.z != 6 || c.w != 8) {
		std::cout << "Test self addition method failed!" << std::endl;
		return false;
	}
	
	c -= 4;
	c /= 4.f;
	if (c.x != -0.5 || c.y != 0 || c.z != 0.5 || c.w != 1) {
		std::cout << "Test constant operation method failed!" << std::endl;
		return false;
	}
	
	return true;
}

bool TestMatrix4x4() {
	return true;
}

bool TestContainers() {
	return TestVector4() && TestMatrix4x4();
}