#pragma once
#include <iostream>
template<typename TYPE>
class Vector2D
{
public:
	TYPE x, y;

	Vector2D() {}
	Vector2D(TYPE _x, TYPE _y) { x = _x; y = _y; }
	void operator=(const Vector2D& p) {
		x = p.x; y = p.y;
	}
	Vector2D(const Vector2D& p) { x = p.x; y = p.y; }


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
	
	Vector2D operator + (const Vector2D &p) const { return Vector2D(x + p.x, y + p.x); }
	Vector2D operator - (const Vector2D &p) const { return Vector2D(x - p.x, y - p.x); }
	Vector2D operator * (const Vector2D &p) const { return Vector2D(x * p.x, y * p.x); }
	Vector2D operator / (const Vector2D &p) const { return Vector2D(x / p.x, y / p.x); }
	Vector2D operator + (const TYPE v) const { return Vector2D(x + v, y + v); }
	Vector2D operator - (const TYPE v) const { return Vector2D(x + v, y + v); }
	Vector2D operator * (const TYPE v) const { return Vector2D(x + v, y + v); }
	Vector2D operator / (const TYPE v) const { return Vector2D(x + v, y + v); }

	//!@name Assignment operators

	const Vector2D& operator += (const Vector2D &p) { x += p.x; y += p.y; return *this; }
	const Vector2D& operator -= (const Vector2D &p) { x -= p.x; y -= p.y; return *this; }
	const Vector2D& operator *= (const Vector2D &p) { x *= p.x; y *= p.y; return *this; }
	const Vector2D& operator /= (const Vector2D &p) { x /= p.x; y /= p.y; return *this; }
	const Vector2D& operator += (const TYPE v) { x += v; y += v; return *this; }
	const Vector2D& operator -= (const TYPE v) { x -= v; y -= v; return *this; }
	const Vector2D& operator *= (const TYPE v) { x *= v; y *= v; return *this; }
	const Vector2D& operator /= (const TYPE v) { x /= v; y /= v; return *this; }


	bool operator==(const Vector2D& p) const { return (x == p.x) && (y == p.y); }
	bool operator!=(const Vector2D& p) const { return (x != p.x) || (y != p.y); }

	TYPE&		operator [] (int i)		  { return Element(i); }
	const TYPE& operator [] (int i) const { return Element(i); }

	TYPE&       Element(int i)		 { return (&x)[i]; }
	const TYPE& Element(int i) const { return (&x)[i]; }

	TYPE*       Data()		 { return &x; }
	const TYPE* Data() const { return &x; }

	void Clear() {}
};

