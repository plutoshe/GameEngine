#pragma once
#include <iostream>
class Vector3D
{

public:
	Vector3D();
	Vector3D(float px, float py, float pz);
	~Vector3D();
	inline friend std::ostream& operator<<(std::ostream& os, const Vector3D p) {
		os << "(" << p.x << "," << p.y << "," << p.z << ")";
		return os;
	}
	Vector3D operator+(const Vector3D& addend);
	Vector3D operator-(const Vector3D& minus);
	Vector3D operator*(const float mul);
	Vector3D operator/(const float div);
	bool operator==(const Vector3D& comp) const;
	void operator=(const Vector3D& origin);

	float x, y, z;
	Vector3D normalized();
	float length();
	void clear();
	
};

