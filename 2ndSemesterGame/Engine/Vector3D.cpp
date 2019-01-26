#include "Vector3D.h"

Vector3D::Vector3D() {}

Vector3D::Vector3D(float px, float py, float pz) : x(px), y(py), z(pz) {}

Vector3D::~Vector3D() {}

Vector3D Vector3D::operator+(const Vector3D& addend) {
	return Vector3D(x + addend.x, y + addend.y, z + addend.z);
}

Vector3D Vector3D::operator-(const Vector3D& minus) {
	return Vector3D(x - minus.x, y - minus.y, z - minus.z);
}

Vector3D Vector3D::operator*(float mul) {
	return Vector3D(x * mul, y * mul, z * mul);
}

Vector3D Vector3D::operator/(float div) {
	return Vector3D(x / div, y / div, z / div);
}


bool Vector3D::operator==(const Vector3D& comp) const {
	return (x == comp.x) && (y == comp.y) && (z == comp.z);
}

void Vector3D::operator=(const Vector3D& origin) {
	x = origin.x;
	y = origin.y;
	z = origin.z;
}

Vector3D Vector3D::normalized() {
	float len = this->length();
	if (len > 0) 
		return Vector3D(x / len, y / len, z / len);
	return Vector3D(0, 0, 0);
}

float Vector3D::length() {
	return sqrt((x * x) + (y * y) + (z * z));
}

void Vector3D::clear() {
	x = y = z = 0;
}

