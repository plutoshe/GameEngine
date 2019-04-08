#pragma once
#include "Vector3D.h"

class GameObject3DBasicAttr
{
public:
	GameObject3DBasicAttr();
	~GameObject3DBasicAttr();

	Vector3f Position;
	Vector3f Rotation;
	Vector3f Scale;
};

