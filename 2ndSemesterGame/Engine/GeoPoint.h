#pragma once
#include "VectorUtil.h"
//class GeoPoint
//{
//public:
//	GeoPoint();
//	~GeoPoint();
//};
//
//class GeoPoint2D
//{
//public:
//	GeoPoint2D();
//	~GeoPoint2D(); 
//	GeoPoint2D(float x, float y) { Position.x = x; Position.y = y; }
//	GeoPoint2D(Vector2f _position) { Position = _position; }
//	GeoPoint2D(const GeoPoint2D &p) {
//		this->Equal(p);
//	}
//
//	void operator =(const GeoPoint2D &p) {
//		this->Equal(p);
//	}
//
//	void Equal(const GeoPoint2D &p) {
//		Position = p.Position;
//	}
//
//
//	Vector2f Position;
//};
typedef Vector3f GeoPoint3D;
typedef Vector2f GeoPoint2D;