#pragma once
#include "SSERedef.h"
#include "GeoLine.h"
#include "GeoPoint.h"
#include "List.h"

class GeoMethod
{
public:
	GeoMethod();
	~GeoMethod();
	static bool crossLineIntersection(GeoLine2D a, GeoLine2D b) {
		float p1 = ((a.End - a.Start) ^ (b.Start - a.Start)) * ((a.End - a.Start) ^ (b.End - a.Start));
		float p2 = ((b.End - b.Start) ^ (a.Start - b.Start)) * ((b.End - b.Start) ^ (a.End - b.Start));
		if (p1 == 0 || p2 == 0) {
			int i = 1;
		}
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

	static bool dotLineIntersection(GeoLine2D a, GeoLine2D b) {
		GeoPoint2D s = b.End - b.Start;
		Vector2f norms(s.y, -s.x);
		float gEnd = (a.End - b.Start).Dot(norms).Length();
		float gStart = (a.Start - b.Start).Dot(norms).Length();
	//intersection = a.Start + (a.End - a.Start) *  gStart / (gEnd + gStart);
		return true;
	}
	static bool IsLine2DIntersect(GeoLine2D a, GeoLine2D b) {
		return crossLineIntersection(a, b);
	}

	static bool IsPointInPoly(GeoPoint2D a, DataStructure::List<GeoPoint2D> b) {
		if (b.get_size() < 3) return false;
		bool existA = (((b[b.get_size() - 1] - a) ^ (b[0] - a)) >= 0);
		bool existB = (((b[b.get_size() - 1] - a) ^ (b[0] - a)) <= 0);
		for (int i = 0; i < b.get_size() - 1; i++) {
			double dir = ((b[i] - a) ^ (b[i + 1] - a));
			if (dir > 0) 
				existB = false;
			if (dir < 0)
				existA = false;
			if (!existA && !existB)
				return false;
		}

		return true;
	}

	static Vector3f GenerateEquationForGeoLine2D(const GeoLine2D &a) {
		return Vector3f(1, (a.Start.x - a.End.x) / (a.End.y - a.Start.y), (a.Start.y * a.End.x - a.Start.x * a.End.y) / (a.End.y - a.Start.y));
	}

	static void Line2DIntersect(const GeoLine2D &a, const GeoLine2D &b, GeoPoint2D &intersection) {
		/*double intersection1 = ((b.Start - a.Start).Dot(a.End - a.Start)).Length() / (a.End - a.Start).Length();
		double intersection2 = ((b.End - a.Start).Dot(a.End - a.Start)).Length() / (a.End - a.Start).Length();
		if (intersection1 > intersection2)
			intersection = a.Start + intersection2 / (a.End - a.Start).Length() * (a.End - a.Start);
		else
			intersection = a.Start + intersection1 / (a.End - a.Start).Length() * (a.End - a.Start);*/
		GeoPoint2D s = b.End - b.Start;
		Vector2f norms(s.y, -s.x);
		float gEnd = (a.End - b.Start).Dot(norms).Length();
		float gStart = (a.Start - b.Start).Dot(norms).Length();
		if (gEnd + gStart != 0) 
			intersection = a.Start + (a.End - a.Start) *  gStart / (gEnd + gStart);
		else {
			if ((b.Start - a.Start).Length() <= (a.End - a.Start).Length() &&
				(b.Start - a.End).Length() <= (a.End - a.Start).Length())
				intersection = b.Start;

			if ((b.End - a.Start).Length() <= (a.End - a.Start).Length() &&
				(b.End - a.End).Length() <= (a.End - a.Start).Length())
				intersection = b.End;
			if ((a.Start - b.Start).Length() <= (b.End - b.Start).Length() &&
				(a.Start - b.End).Length() <= (b.End - b.Start).Length())
				intersection = a.Start;
			if ((a.End - b.Start).Length() <= (b.End - b.Start).Length() &&
				(a.End - b.End).Length() <= (b.End - b.Start).Length())
				intersection = a.End;
		}

	}

};

