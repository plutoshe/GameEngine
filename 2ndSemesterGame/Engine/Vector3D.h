#pragma once
#include <iostream>
class Vector3D
{

public:
	Vector3D();
	Vector3D(int x, int y, int z);
	~Vector3D();
	inline friend std::ostream& operator<<(std::ostream& os, const Vector3D p) {
		os << "(" << p._x << "," << p._y << "," << p._z << ")";
		return os;
	}
	Vector3D operator+(const Vector3D& addend);
	Vector3D operator-(const Vector3D& minus);
	Vector3D operator*(const int mul);
	bool operator==(const Vector3D& comp) const;
	void operator=(const Vector3D& origin);

	const int& x() const { return _x; }
	const int& y() const { return _y; }
	const int& z() const { return _z; }
	inline void x(const int &px) { _x = px; }
	inline void y(const int &py) { _y = py; }
	inline void z(const int &pz) { _y = pz; }
private:
	int _x, _y, _z;
};

