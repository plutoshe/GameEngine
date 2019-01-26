#pragma once
#include <iostream>
class Vector2D
{

public:
	Vector2D();
	Vector2D(int x, int y);
	~Vector2D();
	inline friend std::ostream& operator<<(std::ostream& os, const Vector2D p) {
		os << "(" << p._x << "," << p._y << ')';
		return os;
	}
	Vector2D operator+(const Vector2D& addend);
	Vector2D operator-(const Vector2D& minus);
	Vector2D operator*(const int mul);
	bool operator==(const Vector2D& comp) const;
	void operator=(const Vector2D& origin);

	const int& x() const { return _x; }
	const int& y() const { return _y; }
	inline void x(const int &px) { _x = px; }
	inline void y(const int &py) { _y = py; }
private:
	int _x, _y;
};

