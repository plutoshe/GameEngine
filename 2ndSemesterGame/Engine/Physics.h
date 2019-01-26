#pragma once
#include "GameManager.h"

namespace Physcis {
	void AddForce(GameObject& gameobject, Vector3D & i_Force, double i_dt)
	{
		Vector3D acceleration = i_Force / gameobject.mass;
		gameobject.position = gameobject.position + gameobject.velocity * (float)i_dt + acceleration * (float)(i_dt * i_dt / 2);
		gameobject.velocity = gameobject.velocity + acceleration * (float)i_dt;

	}
}
