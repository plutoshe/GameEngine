#pragma once
#include "GameObject.h"
class Player: GameObject
{
public:
	Player();
	~Player();

	void Update() {
		printf("!!!");
	}
};

