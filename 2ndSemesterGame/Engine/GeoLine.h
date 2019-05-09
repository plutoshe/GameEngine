#pragma once
#include "SSERedef.h"
#include "GeoPoint.h"
//class GeoLine3D
//{
//public:
//	GeoLine3D();
//	~GeoLine3D();
//	GeoPoint3D Start, End;
//};

class GeoLine2D
{
public:
	GeoLine2D();
	GeoLine2D(GeoPoint2D _start, GeoPoint2D _end) {
		Start = _start; End = _end;
	}
	~GeoLine2D();
	//GetNorm();

	GeoPoint2D Start, End;	
};
