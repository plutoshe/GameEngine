#pragma once
#include "GLib.h"
#include "Engine.h"

extern GameManager CurrentGameManager;

class CollisionObject : public GameObject {
	void Update() {
		AddForce(Vector3f((float)(rand() % 300 - 150), (float)(rand() % 300 - 150), 0));
	}
};

