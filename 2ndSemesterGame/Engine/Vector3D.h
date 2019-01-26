#pragma once
#include <iostream>
class Vector3D
{

public:
	Vector3D();
	Vector3D(float x, float y, float z);
	~Vector3D();
	inline friend std::ostream& operator<<(std::ostream& os, const Vector3D p) {
		os << "(" << p._x << "," << p._y << "," << p._z << ")";
		return os;
	}
	Vector3D operator+(const Vector3D& addend);
	Vector3D operator-(const Vector3D& minus);
	Vector3D operator*(const float mul);
	bool operator==(const Vector3D& comp) const;
	void operator=(const Vector3D& origin);

	const float& x() const { return _x; }
	const float& y() const { return _y; }
	const float& z() const { return _z; }
	inline void x(const float &px) { _x = px; }
	inline void y(const float &py) { _y = py; }
	inline void z(const float &pz) { _y = pz; }
private:
	float _x, _y, _z;
};

