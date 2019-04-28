#pragma once
#include "VectorUtil.h"
#include "GeoLine.h"

class GeoMethod
{
public:
	GeoMethod();
	~GeoMethod();

	static bool IsLine2DIntersect(GeoLine2D a, GeoLine2D b) {
		float p1 = ((a.End - a.Start) ^ (b.Start - a.Start)) * ((a.End - a.Start) ^ (b.End - a.Start));
		float p2 = ((b.End - b.Start) ^ (a.Start - b.Start)) * ((b.End - b.Start) ^ (a.End - b.Start));
		if (p1 == 0 && p2 == 0) {

			if ((b.Start - a.Start).Length() <= (a.End - a.Start).Length() &&
				(b.Start - a.End).Length() <= (a.End - a.Start).Length())
				return true;
			if ((b.End - a.Start).Length() <= (a.End - a.Start).Length() &&
				(b.End - a.End).Length() <= (a.End - a.Start).Length())
				return true;
			if ((a.Start - b.Start).Length() <= (b.End - b.Start).Length() &&
				(a.Start - b.End).Length() <= (b.End - b.Start).Length())
				return true;
			if ((a.End - b.Start).Length() <= (b.End - b.Start).Length() &&
				(a.End - b.End).Length() <= (b.End - b.Start).Length())
				return true;

		}
		return (p1 < 0) && (p2 < 0) || (p1 == 0) && (p2 < 0) || (p2 == 0) && (p1 < 0);
	}

	static Vector3f GenerateEquationForGeoLine2D(const GeoLine2D &a) {
		return Vector3f(1, (a.Start.x - a.End.x) / (a.End.y - a.Start.y), (a.Start.y * a.End.x - a.Start.x * a.End.y) / (a.End.y - a.Start.y));
	}

	static bool Line2DIntersect(const GeoLine2D &a, const GeoLine2D &b, GeoPoint2D &intersection) {
		if (IsLine2DIntersect(a, b)) {
			double intersection1 = ((b.Start - a.Start).Dot(a.End - a.Start)).Length() / (a.End - a.Start).Length();
			double intersection2 = ((b.End - a.Start).Dot(a.End - a.Start)).Length() / (a.End - a.Start).Length();
			if (intersection1 > intersection2)
				intersection = a.Start + intersection2 / (a.End - a.Start).Length() * (a.End - a.Start);
			else
				intersection = a.Start + intersection1 / (a.End - a.Start).Length() * (a.End - a.Start);
			return true;
		}
		return false;
	}

};

