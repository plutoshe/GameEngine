#pragma once
#include "Vector.h"
#include <iostream>

template<typename TYPE>
class Vector3D;
template<typename TYPE>
class Vector4D;


template<typename TYPE>
class Vector2D
{
public:
	TYPE x, y;

	Vector2D() { Clear(); }
	Vector2D(TYPE _x, TYPE _y) { x = _x; y = _y; }

	void operator=(const Vector2D& p);
	void operator=(const Vector3D<TYPE>& p);
	void operator=(const Vector4D<TYPE>& p);
	Vector2D(const Vector2D& p);
	Vector2D(const Vector3D<TYPE>& p);
	Vector2D(const Vector4D<TYPE>& p);


	void Equal(const Vector2D& p);
	void Equal(const Vector3D<TYPE>& p);
	void Equal(const Vector4D<TYPE>& p);

	~Vector2D() {}
	inline friend std::ostream& operator<<(std::ostream& os, const Vector2D &p) {
		os << "(" << p.x << "," << p.y << ')';
		return os;
	}

	friend Vector2D operator +(const TYPE v, const Vector2D &p) {
		return p + v;
	}
	friend Vector2D operator -(const TYPE v, const Vector2D &p) {
		return p - v;
	}
	friend Vector2D operator *(const TYPE v, const Vector2D &p) {
		return p * v;
	}

	Vector2D operator + (const Vector2D &p) const { return Vector2D(x + p.x, y + p.y); }
	Vector2D operator - (const Vector2D &p) const { return Vector2D(x - p.x, y - p.y); }
	Vector2D operator * (const Vector2D &p) const { return Vector2D(x * p.x, y * p.y); }
	Vector2D operator / (const Vector2D &p) const { return Vector2D(x / p.x, y / p.y); }
	Vector2D operator + (const TYPE v) const { return Vector2D(x + v, y + v); }
	Vector2D operator - (const TYPE v) const { return Vector2D(x - v, y - v); }
	Vector2D operator * (const TYPE v) const { return Vector2D(x * v, y * v); }
	Vector2D operator / (const TYPE v) const { return Vector2D(x / v, y / v); }

	//!@name Assignment operators

	const Vector2D& operator += (const Vector2D &p) { x += p.x; y += p.y; return *this; }
	const Vector2D& operator -= (const Vector2D &p) { x -= p.x; y -= p.y; return *this; }
	const Vector2D& operator *= (const Vector2D &p) { x *= p.x; y *= p.y; return *this; }
	const Vector2D& operator /= (const Vector2D &p) { x /= p.x; y /= p.y; return *this; }
	const Vector2D& operator += (const TYPE v) { x += v; y += v; return *this; }
	const Vector2D& operator -= (const TYPE v) { x -= v; y -= v; return *this; }
	const Vector2D& operator *= (const TYPE v) { x *= v; y *= v; return *this; }
	const Vector2D& operator /= (const TYPE v) { if (v == 0) return Vector2D(); x /= v; y /= v; return *this; }


	bool operator==(const Vector2D& p) const { return (x == p.x) && (y == p.y); }
	bool operator!=(const Vector2D& p) const { return (x != p.x) || (y != p.y); }

	TYPE&		operator [] (int i) { return Element(i); }
	const TYPE& operator [] (int i) const { return Element(i); }

	TYPE&       Element(int i) { return (&x)[i]; }
	const TYPE& Element(int i) const { return (&x)[i]; }

	TYPE*       Data() { return &x; }
	const TYPE* Data() const { return &x; }


	TYPE Cross(const Vector2D& p) const {
		return x * p.y - y * p.x;
	}
	TYPE operator ^ (const Vector2D &p) const { return this->Cross(p); }

	Vector2D Dot(const Vector2D& p) const {
		return Vector2D(x * p.x, y * p.y);
	}
	TYPE operator % (const Vector2D &p) const { return this->Dot(p); }

	void Clear() {}
	TYPE Length() { return sqrt((x * x) + (y * y)); }


};


template<typename TYPE>
class Vector3D
{
public:

	TYPE x, y, z;

	Vector3D() { Clear();  }
	Vector3D(TYPE _x, TYPE _y, TYPE _z) { x = _x; y = _y; z = _z; }

	void operator=(const Vector2D<TYPE>& p);
	void operator=(const Vector3D& p);
	void operator=(const Vector4D<TYPE>& p);
	Vector3D(const Vector2D<TYPE>& p);
	Vector3D(const Vector3D& p);
	Vector3D(const Vector4D<TYPE>& p);


	void Equal(const Vector2D<TYPE>& p);
	void Equal(const Vector3D& p);
	void Equal(const Vector4D<TYPE>& p);

	~Vector3D() {}

	inline friend std::ostream& operator<<(std::ostream& os, const Vector3D &p) {
		os << "(" << p.x << "," << p.y << "," << p.z << ")";
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

	Vector3D operator + (const Vector3D &p) const { return Vector3D(x + p.x, y + p.y, z + p.z); }
	Vector3D operator - (const Vector3D &p) const { return Vector3D(x - p.x, y - p.y, z - p.z); }
	Vector3D operator * (const Vector3D &p) const { return Vector3D(x * p.x, y * p.y, z * p.z); }
	Vector3D operator / (const Vector3D &p) const { return Vector3D(x / p.x, y / p.y, z / p.z); }
	Vector3D operator + (const TYPE v) const { return Vector3D(x + v, y + v, z + v); }
	Vector3D operator - (const TYPE v) const { return Vector3D(x - v, y - v, z - v); }
	Vector3D operator * (const TYPE v) const { return Vector3D(x * v, y * v, z * v); }
	Vector3D operator / (const TYPE v) const { return Vector3D(x / v, y / v, z / v); }

	//!@name Assignment operators

	const Vector3D& operator += (const Vector3D &p) { x += p.x; y += p.y; z += p.z; return *this; }
	const Vector3D& operator -= (const Vector3D &p) { x -= p.x; y -= p.y; z -= p.z; return *this; }
	const Vector3D& operator *= (const Vector3D &p) { x *= p.x; y *= p.y; z *= p.z; return *this; }
	const Vector3D& operator /= (const Vector3D &p) { x /= p.x; y /= p.y; z /= p.z; return *this; }
	const Vector3D& operator += (const TYPE v) { x += v; y += v; z += v; return *this; }
	const Vector3D& operator -= (const TYPE v) { x -= v; y -= v; z -= v; return *this; }
	const Vector3D& operator *= (const TYPE v) { x *= v; y *= v; z *= v; return *this; }
	const Vector3D& operator /= (const TYPE v) { if (v == 0) return Vector3D(); x /= v; y /= v; z /= v; return *this; }


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

template<typename TYPE>
class Vector4D
{
public:
	TYPE x, y, z, w;

	Vector4D() { Clear();  }
	Vector4D(TYPE _x, TYPE _y, TYPE _z, TYPE _w) { x = _x; y = _y; z = _z; w = _w; }
	void operator=(const Vector4D& p) { this->Equal(p); }
	void operator=(const Vector3D<TYPE> &p) { this->Equal(p); }
	void operator=(const Vector2D<TYPE> &p) { this->Equal(p); }
	Vector4D(const Vector4D& p) { this->Equal(p); }
	Vector4D(const Vector3D<TYPE> &p) { this->Equal(p); }
	Vector4D(const Vector2D<TYPE> &p) { this->Equal(p); }
	void Equal(const Vector4D& p) { x = p.x; y = p.y; z = p.z; w = p.w; }
	void Equal(const Vector3D<TYPE> &p) { x = p.x; y = p.y; z = p.z; w = 0; }
	void Equal(const Vector2D<TYPE> &p) { x = p.x; y = p.y; z = 0; w = 0; }


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

	Vector4D operator + (const Vector4D &p) const { return Vector4D(x + p.x, y + p.y, z + p.z, w + p.w); }
	Vector4D operator - (const Vector4D &p) const { return Vector4D(x - p.x, y - p.y, z - p.z, w - p.w); }
	Vector4D operator * (const Vector4D &p) const { return Vector4D(x * p.x, y * p.y, z * p.z, w * p.w); }
	Vector4D operator / (const Vector4D &p) const { return Vector4D(x / p.x, y / p.y, z / p.z, w / p.w); }
	Vector4D operator + (const TYPE v) const { return Vector4D(x + v, y + v, z + v, w + v); }
	Vector4D operator - (const TYPE v) const { return Vector4D(x - v, y - v, z - v, w - v); }
	Vector4D operator * (const TYPE v) const { return Vector4D(x * v, y * v, z * v, w * v); }
	Vector4D operator / (const TYPE v) const { if (v == 0) return Vector4D(); return Vector4D(x / v, y / v, z / v, w / v); }

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
	
	TYPE Length() { return sqrt(x * x + y * y + z * z + w * w); }
};

template<typename TYPE> void Vector2D<TYPE>::operator=(const Vector2D<TYPE>& p) { this->Equal(p); }
template<typename TYPE> void Vector2D<TYPE>::operator=(const Vector3D<TYPE>& p) { this->Equal(p); }
template<typename TYPE> void Vector2D<TYPE>::operator=(const Vector4D<TYPE>& p) { this->Equal(p); }
template<typename TYPE> Vector2D<TYPE>::Vector2D(const Vector2D<TYPE>& p) { this->Equal(p); }
template<typename TYPE> Vector2D<TYPE>::Vector2D(const Vector3D<TYPE>& p) { this->Equal(p); }
template<typename TYPE> Vector2D<TYPE>::Vector2D(const Vector4D<TYPE>& p) { this->Equal(p); }
template<typename TYPE> void Vector2D<TYPE>::Equal(const Vector2D<TYPE>& p) { x = p.x; y = p.y;}
template<typename TYPE> void Vector2D<TYPE>::Equal(const Vector3D<TYPE>& p) { x = p.x; y = p.y; }
template<typename TYPE> void Vector2D<TYPE>::Equal(const Vector4D<TYPE>& p) { x = p.x; y = p.y; }

template<typename TYPE> void Vector3D<TYPE>::operator=(const Vector2D<TYPE>& p) { this->Equal(p); }
template<typename TYPE> void Vector3D<TYPE>::operator=(const Vector3D<TYPE>& p) { this->Equal(p); }
template<typename TYPE> void Vector3D<TYPE>::operator=(const Vector4D<TYPE>& p) { this->Equal(p); }
template<typename TYPE> Vector3D<TYPE>::Vector3D(const Vector2D<TYPE>& p) { this->Equal(p); }
template<typename TYPE> Vector3D<TYPE>::Vector3D(const Vector3D<TYPE>& p) { this->Equal(p); }
template<typename TYPE> Vector3D<TYPE>::Vector3D(const Vector4D<TYPE>& p) { this->Equal(p); }
template<typename TYPE> void Vector3D<TYPE>::Equal(const Vector2D<TYPE>& p) { x = p.x; y = p.y; }
template<typename TYPE> void Vector3D<TYPE>::Equal(const Vector3D<TYPE>& p) { x = p.x; y = p.y; z = p.z; }
template<typename TYPE> void Vector3D<TYPE>::Equal(const Vector4D<TYPE>& p) { x = p.x; y = p.y; z = p.z; }
typedef Vector4D<float> Vector4f;
typedef Vector4D<int> Vector4i;
typedef Vector2D<float> Vector2f;
typedef Vector3D<float> Vector3f;
