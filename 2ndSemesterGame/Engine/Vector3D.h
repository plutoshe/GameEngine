#pragma once
#include <iostream>
template<typename TYPE>
class Vector3D
{
public:
	TYPE x, y, z;

	Vector3D() {}
	Vector3D(TYPE _x, TYPE _y, TYPE _z) { x = _x; y = _y; z = _z; }
	void operator=(const Vector3D& p) {
		x = p.x; y = p.y; z = p.z;
	}
	Vector3D(const Vector3D& p) { x = p.x; y = p.y; z = p.z; }


	~Vector3D() {}

	inline friend std::ostream& operator<<(std::ostream& os, const Vector3D &p) {
		os << "(" << p.x << "," << p.y << "," << p.z <<  ")";
		return os;
	}

	friend Vector3D operator +(const TYPE v, const Vector3D &p) {
		return p + v;
	}
	friend Vector3D operator -(const TYPE v, const Vector3D &p) {
		return p - v;
	}
	friend Vector3D operator *(const TYPE v, const Vector3D &p) {
		return p * v;
	}

	Vector3D operator + (const Vector3D &p) const { return Vector3D(x + p.x, y + p.x, z + p.z); }
	Vector3D operator - (const Vector3D &p) const { return Vector3D(x - p.x, y - p.x, z - p.z); }
	Vector3D operator * (const Vector3D &p) const { return Vector3D(x * p.x, y * p.x, z * p.z); }
	Vector3D operator / (const Vector3D &p) const { return Vector3D(x / p.x, y / p.x, z / p.z); }
	Vector3D operator + (const TYPE v) const { return Vector3D(x + v, y + v, z + v); }
	Vector3D operator - (const TYPE v) const { return Vector3D(x + v, y + v, z - v); }
	Vector3D operator * (const TYPE v) const { return Vector3D(x + v, y + v, z * v); }
	Vector3D operator / (const TYPE v) const { return Vector3D(x + v, y + v, z / v); }

	//!@name Assignment operators

	const Vector3D& operator += (const Vector3D &p) { x += p.x; y += p.y; z += p.z; return *this; }
	const Vector3D& operator -= (const Vector3D &p) { x -= p.x; y -= p.y; z -= p.z; return *this; }
	const Vector3D& operator *= (const Vector3D &p) { x *= p.x; y *= p.y; z *= p.z; return *this; }
	const Vector3D& operator /= (const Vector3D &p) { x /= p.x; y /= p.y; z /= p.z; return *this; }
	const Vector3D& operator += (const TYPE v) { x += v; y += v; z += v; return *this; }
	const Vector3D& operator -= (const TYPE v) { x -= v; y -= v; z -= v; return *this; }
	const Vector3D& operator *= (const TYPE v) { x *= v; y *= v; z *= v; return *this; }
	const Vector3D& operator /= (const TYPE v) { x /= v; y /= v; z /= v; return *this; }


	bool operator==(const Vector3D& p) const { return (x == p.x) && (y == p.y); }
	bool operator!=(const Vector3D& p) const { return (x != p.x) || (y != p.y); }

	TYPE&		operator [] (int i) { return Element(i); }
	const TYPE& operator [] (int i) const { return Element(i); }

	TYPE&       Element(int i) { return (&x)[i]; }
	const TYPE& Element(int i) const { return (&x)[i]; }

	TYPE*       Data() { return &x; }
	const TYPE* Data() const { return &x; }

	void Clear() { x = y = z = 0; }

	Vector3D normalized() {
		TYPE len = Length();
		if (len > 0)
			return Vector3D(x / len, y / len, z / len);
		return Vector3D(0, 0, 0);
	}

	TYPE Length() { return sqrt((x * x) + (y * y) + (z * z)); }
	

};

typedef Vector3D<float> Vector3f;