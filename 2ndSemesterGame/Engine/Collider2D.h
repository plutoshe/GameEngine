#pragma once
#include "GameObjectBasicAttr.h"
#include "GameObject.h"
#include "SmartPointer.h"
#include "Vector2D.h"

enum Collider2DType
{
	Box = 0,
	/*Circle,
	Capsule,
	Edge,
	Polygon,*/
};

class Collider {
	Collider() {}
	~Collider() {}
};

class Collider2D: public Collider
{
public:
	Engine::ObservingPointer<GameObject> ParentGameObject;

	Collider2D();
	~Collider2D();

};

class BoxCollider2D: Collider2D {
public:
	Vector2f Center;
	Vector2f Size;

};

