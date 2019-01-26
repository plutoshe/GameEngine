#include "Vector3D.h"

Vector3D::Vector3D() {}

Vector3D::Vector3D(int x, int y, int z) : _x(x), _y(y), _z(z) {}

Vector3D::~Vector3D() {}

Vector3D Vector3D::operator+(const Vector3D& addend) {
	return Vector3D(_x + addend.x(), _y + addend.y(), _z + addend.z());
}

Vector3D Vector3D::operator-(const Vector3D& minus) {
	return Vector3D(_x - minus.x(), _y - minus.y(), _z - minus.z());
}

Vector3D Vector3D::operator*(int mul) {
	return Vector3D(_x * mul, _y * mul, _z * mul);
}


bool Vector3D::operator==(const Vector3D& comp) const {
	return (_x == comp.x()) && (_y == comp.y()) && (_z == comp.z());
}

void Vector3D::operator=(const Vector3D& origin) {
	_x = origin.x();
	_y = origin.y();
	_z = origin.z();
}


