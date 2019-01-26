#pragma once
#include "Vector3D.h"
class GameObject
{
public:
	
	GameObject();
	~GameObject();

	Vector3D position;
	Vector3D velocity;
	float mass;
	float drag;
};

