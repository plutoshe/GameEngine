#include "Collider2D.h"

Collider2D::Collider2D()
{
}


Collider2D::~Collider2D()
{
}
DataStructure::List<GeoPoint2D> BoxCollider2D::GetBorderPoints() {
	DataStructure::List<GeoPoint2D> geoPointList;
	const float Direction[4][2] = { {0.5, 0.5}, {-0.5, 0.5}, {-0.5, -0.5}, {0.5, -0.5}};
	for (int i = 0; i < 4; i++) 
		geoPointList.push(GeoPoint2D(Center.x + Direction[i][0] * Size.x, Center.y + Direction[i][1] * Size.y));
	
	return geoPointList;

}

DataStructure::List<GeoLine2D> BoxCollider2D::GetBorderLines() {
	DataStructure::List<GeoPoint2D> geoPointList;
	const float Direction[4][2] = { {0.5, 0.5}, {-0.5, 0.5}, {-0.5, -0.5}, {0.5, -0.5}};
	for (int i = 0; i < 4; i++)
		geoPointList.push(GeoPoint2D(Center.x + Direction[i][0] * Size.x, Center.y + Direction[i][1] * Size.y));
	DataStructure::List<GeoLine2D> geoLineList;
	for (int i = 0; i < 4; i++)
		geoLineList.push(GeoLine2D(geoPointList[i], geoPointList[(i + 1) % 4]));
	return geoLineList;
}

