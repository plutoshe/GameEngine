#pragma once
#include "GLib.h"
#include "Engine.h"

extern GameManager CurrentGameManager;

class CollisionObject : public GameObject {
	void Update() {
		AddForce(Vector3f(rand() % 300 - 150, rand() % 300 - 150, 0));
	}
};

