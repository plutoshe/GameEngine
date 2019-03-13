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
	inline friend std::ostream& operator<<(std::ostream& os, const Vector2D p) {
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

	const Vector2D& operator += (const Vector2D &p) { return *this + p; }
	const Vector2D& operator -= (const Vector2D &p) { return *this - p; }
	const Vector2D& operator *= (const Vector2D &p) { return *this * p; }
	const Vector2D& operator /= (const Vector2D &p) { return *this / p; }
	const Vector2D& operator += (const TYPE v) { return *this + v; }
	const Vector2D& operator -= (const TYPE v) { return *this - v; }
	const Vector2D& operator *= (const TYPE v) { return *this * v; }
	const Vector2D& operator /= (const TYPE v) { return *this / v; }

	bool operator==(const Vector2D& p) const { return (x == p.x) && (y == p.y); }
	bool operator!=(const Vector2D& p) const { return (x != p.x) || (y != p.y); }

};

