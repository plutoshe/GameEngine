#include "Vector2D.h"

Vector2D::Vector2D()
{
}

Vector2D::Vector2D(int x, int y) : _x(x), _y(y)
{
}

Vector2D::~Vector2D()
{
}

Vector2D Vector2D::operator+(const Vector2D& addend) {
	return Vector2D(_x + addend.x(), _y + addend.y());
}

Vector2D Vector2D::operator-(const Vector2D& minus) {
	return Vector2D(_x - minus.x(), _y - minus.y());
}

Vector2D Vector2D::operator*(int mul) {
	return Vector2D(_x * mul, _y * mul);
}


bool Vector2D::operator==(const Vector2D& comp) const {
	return (_x == comp.x()) && (_y == comp.y());
}

void Vector2D::operator=(const Vector2D& origin) {
	_x = origin.x();
	_y = origin.y();
}


