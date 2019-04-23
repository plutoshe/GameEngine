#pragma once
#include "VectorUtil.h"
#include "GeoLine.h"

class GeoMethod
{
public:
	GeoMethod();
	~GeoMethod();

	static bool IsLine2DIntersect(GeoLine2D a, GeoLine2D b) {
		float p1 = ((a.End - a.Start) * (b.Start - a.Start)) ^ ((a.End - a.Start) * (b.End - a.Start));
		float p2 = ((b.End - b.Start) * (a.Start - b.Start)) ^ ((b.End - b.Start) * (a.End - b.Start));
		return (p1 < 0) && (p2 < 0);
	}

	static Vector3f GenerateEquationForGeoLine2D(const GeoLine2D &a) {
		return Vector3f(1, (a.Start.x - a.End.x) / (a.End.y - a.Start.y), (a.Start.y * a.End.x - a.Start.x * a.End.y) / (a.End.y - a.Start.y));
	}

	static bool Line2DIntersect(const GeoLine2D &a, const GeoLine2D &b, GeoPoint2D intersection) {
		if (IsLine2DIntersect(a, b)) {
			Vector3f paramA = GenerateEquationForGeoLine2D(a);
			Vector3f paramB = GenerateEquationForGeoLine2D(b);
			float m = paramA.x * paramB.y - paramB.x * paramA.y;
			intersection.x = (paramB.z*paramA.y - paramA.z * paramB.y) / m;
			intersection.y = (paramA.z*paramB.x - paramB.z * paramA.x) / m;
			return true;
		}
		return false;
	}

};

