#pragma once
#include "SmartPointer.h"
#include "SSERedef.h"
#include "List.h"
#include "GeoLine.h"
#include "GeoPoint.h"
class PhysicsComponent;
enum ColliderType
{
	Box = 0,
	/*Circle,
	Capsule,
	Edge,
	Polygon,*/
};

class Collider {
public:
	ColliderType type;
	Engine::ObservingPointer<PhysicsComponent> ParentGameObject;
	Collider() {}
	~Collider() {}
};

class Collider2D: public Collider
{
public:
	Collider2D();
	~Collider2D();
};
// TODO: Add collider
// 2D_Collider: 5 Type
// Box, Circle, Capsule, Edge, Polygon
class BoxCollider2D: public Collider2D {
public:
	Vector2f Center;
	Vector2f Size;

	BoxCollider2D() { type = Box; }
	BoxCollider2D(Vector2f _center, Vector2f _size) {
		type = Box;
		Center = _center; 
		Size = _size;
	}
	DataStructure::List<GeoPoint2D> GetBorderPoints();
	DataStructure::List<GeoLine2D> GetBorderLines();
	

};

// 3D Collider: 3 Type
// Cube, Sphere, Capsule
