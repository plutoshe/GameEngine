#pragma once
#include "VectorUtil.h"

class GameObjectBasicAttr
{
public:
	GameObjectBasicAttr();
	~GameObjectBasicAttr();

	void Clear() {
		Position.Clear();
		Rotation.Clear();
		Scale.x = Scale.y = Scale.z = 1;
	}

	Vector3f Position;
	Vector3f Rotation;
	Vector3f Scale;
};
