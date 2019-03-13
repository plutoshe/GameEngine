#include <string>
#include <string.h>
#include <iostream>
#include "cmath"
#include "Vector4D.h"
#include "Matrix4x4.h"
#include "iostream"

bool TestVector4() {
	Vector4f a(1, 2, 3, 4);
	Vector4f b;
	Vector4f c;
	Vector4f e(a);
	
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
	if (c != b || e != c) {
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
	// check output of vector
	// std::cout << e << std::endl;
	return true;
}

bool TestMatrix4x4() {
	Matrix4f a(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16);
	Matrix4f b(a);
	Matrix4f c(Vector4f(1, 2, 3, 4));
	Matrix4f d(1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 0, 4);
	Matrix4f e;
	Matrix4f f;
	e[0][0] = 1;  e[0][1] = 2;  e[0][2] = 3;  e[0][3] = 4;
	e[1][0] = 5;  e[1][1] = 6;  e[1][2] = 7;  e[1][3] = 8;
	e[2][0] = 9;  e[2][1] = 10; e[2][2] = 11; e[2][3] = 12;
	e[3][0] = 13; e[3][1] = 14; e[3][2] = 15; e[3][3] = 16;

	if (b != a || c != d || e != b || a == c) {
		std::cout << "Test matrix assignment methods failed!" << std::endl;
		return false;
	}
	f = a;
	a += d;
	b = b + d;
	
	e[0][0] = 2;  e[0][1] = 2;  e[0][2] = 3;  e[0][3] = 4;
	e[1][0] = 5;  e[1][1] = 8;  e[1][2] = 7;  e[1][3] = 8;
	e[2][0] = 9;  e[2][1] = 10; e[2][2] = 14; e[2][3] = 12;
	e[3][0] = 13; e[3][1] = 14; e[3][2] = 15; e[3][3] = 20;

	if (a != e || b != e) {
		std::cout << "Test matrix addition methods failed!" << std::endl;
		return false;
	}
	b -= d;
	a = a - d;	
	if (a != f || b != f) {
		std::cout << "Test matrix minus methods failed!" << std::endl;
		return false;
	}

	a += 3;
	b = b + 3;
	a -= 2;
	b = b - 2;
	a *= 3;
	b = b * 3;
	a /= 2;
	b = b / 2;
	e = b;

	e[0][0] = 3;  e[0][1] = 4.5f;  e[0][2] = 6;  e[0][3] = 7.5;
	e[1][0] = 9;  e[1][1] = 10.5f; e[1][2] = 12; e[1][3] = 13.5;
	e[2][0] = 15; e[2][1] = 16.5f; e[2][2] = 18; e[2][3] = 19.5;
	e[3][0] = 21; e[3][1] = 22.5;  e[3][2] = 24; e[3][3] = 25.5;
	if (a != e) {
		std::cout << "Test matrix constant operation methods failed!" << std::endl;
		return false; 
	}

	f = Vector4f(4, 3, 6, 1);
	e.SetScale(4, 3, 6, 1);
	if (e != f) {
		std::cout << "Test scale methods failed!" << std::endl;
		return false;
	}
	
	a = a * Vector4f(2, 1, 1, 1);
	Matrix<float, 4, 1> r;

	r[0][0] = 2; r[1][0] = r[2][0] = r[3][0] = 1;
	r = b * r;

	if (a.GetDiag() != Vector4f(24,54,84,114)) {
		std::cout << "Test vector right multiply methods failed!" << std::endl;
		return false;
	}
	if (r[0][0] != 24 || r[1][0] != 54 || r[2][0] != 84 || r[3][0] != 114) {
		std::cout << "Test matrix right multiply methods failed!" << std::endl;
		return false;
	}

	

	Matrix<float, 1, 4> l;
	l[0][0] = 1; l[0][1] = -1; l[0][2] = 3; l[0][3] = -8;
	l = l * b;
	b = Vector4f(1, -1, 3, -8) * b;
	if (b.GetDiag() != Vector4f(-129, -136.5, -144, -151.5)) {
		std::cout << "Test vector left multiply methods failed!" << std::endl;
		return false;
	}
	if (l[0][0] != -129 || l[0][1] != -136.5 || l[0][2] != -144 || l[0][3] != -151.5) {
		std::cout << "Test matrix left multiply methods failed!" << std::endl;
		return false;
	}

	// check output of matrix
	// std::cout << e << std::endl;

	return true;
}

bool TestContainers() {
	return TestVector4() && TestMatrix4x4();
}