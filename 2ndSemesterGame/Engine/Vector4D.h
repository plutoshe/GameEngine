#pragma once
#include <iostream>
template<typename TYPE>
class Vector4D
{
public:
	TYPE x, y, z, w;

	Vector4D() {}
	Vector4D(TYPE _x, TYPE _y, TYPE _z, TYPE _w) { x = _x; y = _y; z = _z; w = _w; }
	void operator=(const Vector4D& p) {
		x = p.x; y = p.y; z = p.z; w = p.w;
	}
	Vector4D(const Vector4D& p) { x = p.x; y = p.y; z = p.z; w = p.w; }


	~Vector4D() {}

	inline friend std::ostream& operator<<(std::ostream& os, const Vector4D &p) {
		os << "(" << p.x << "," << p.y << "," << p.z << "," << p.w << ")";
		return os;
	}

	friend Vector4D operator +(const TYPE v, const Vector4D &p) {
		return p + v;
	}
	friend Vector4D operator -(const TYPE v, const Vector4D &p) {
		return p * -1 + v;
	}
	friend Vector4D operator *(const TYPE v, const Vector4D &p) {
		return p * v;
	}

	Vector4D operator + (const Vector4D &p) const { return Vector4D(x + p.x, y + p.x, z + p.z, w + p.w); }
	Vector4D operator - (const Vector4D &p) const { return Vector4D(x - p.x, y - p.x, z - p.z, w + p.w); }
	Vector4D operator * (const Vector4D &p) const { return Vector4D(x * p.x, y * p.x, z * p.z, w + p.w); }
	Vector4D operator / (const Vector4D &p) const { return Vector4D(x / p.x, y / p.x, z / p.z, w + p.w); }
	Vector4D operator + (const TYPE v) const { return Vector4D(x + v, y + v, z + v, w + v); }
	Vector4D operator - (const TYPE v) const { return Vector4D(x + v, y + v, z - v, w + v); }
	Vector4D operator * (const TYPE v) const { return Vector4D(x + v, y + v, z * v, w + v); }
	Vector4D operator / (const TYPE v) const { return Vector4D(x + v, y + v, z / v, w + v); }

	//!@name Assignment operators

	const Vector4D& operator += (const Vector4D &p) { x += p.x; y += p.y; z += p.z; w += p.w; return *this; }
	const Vector4D& operator -= (const Vector4D &p) { x -= p.x; y -= p.y; z -= p.z; w -= p.w; return *this; }
	const Vector4D& operator *= (const Vector4D &p) { x *= p.x; y *= p.y; z *= p.z; w *= p.w; return *this; }
	const Vector4D& operator /= (const Vector4D &p) { x /= p.x; y /= p.y; z /= p.z; w /= p.w; return *this; }
	const Vector4D& operator += (const TYPE v) { x += v; y += v; z += v; w += v; return *this; }
	const Vector4D& operator -= (const TYPE v) { x -= v; y -= v; z -= v; w -= v; return *this; }
	const Vector4D& operator *= (const TYPE v) { x *= v; y *= v; z *= v; w *= v; return *this; }
	const Vector4D& operator /= (const TYPE v) { x /= v; y /= v; z /= v; w /= v; return *this; }


	bool operator==(const Vector4D& p) const { return (x == p.x) && (y == p.y) && (z == p.z) && (w == p.w); }
	bool operator!=(const Vector4D& p) const { return (x != p.x) || (y != p.y) || (z != p.z) || (w != p.w); }

	TYPE&		operator [] (int i) { return Element(i); }
	const TYPE& operator [] (int i) const { return Element(i); }

	TYPE&       Element(int i) { return (&x)[i]; }
	const TYPE& Element(int i) const { return (&x)[i]; }

	TYPE*       Data() { return &x; }
	const TYPE* Data() const { return &x; }

	void Clear() { x = y = z = w = 0; }
};

typedef Vector4D<float> Vector4f;
typedef Vector4D<int> Vector4i;