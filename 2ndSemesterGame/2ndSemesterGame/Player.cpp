#include "Env.h"
#include "Player.h"
#include "GameManager.h"
#include "PhysicsComponent.h"
#include "Log.h"

Player::Player()
{
}


Player::~Player()
{
}

void Player::Update() {
	if (CurrentGameManager.Input->IsKeyDown('W')) {
		physicsComponent->AddForce(Vector3f(0, 100000, 0));
	}
	if (CurrentGameManager.Input->IsKeyDown('A')) {
		physicsComponent->AddForce(Vector3f(-100000, 0, 0));
	}
	if (CurrentGameManager.Input->IsKeyDown('S')) {
		physicsComponent->AddForce(Vector3f(0, -100000, 0));
	}
	if (CurrentGameManager.Input->IsKeyDown('D')) {
		physicsComponent->AddForce(Vector3f(100000, 0, 0));
	}

	// Mouse Press
	/*if (CurrentGameManager.Input->IsMouseDown(0)) {
		physicsComponent->AddForce(Vector3f(0, 100000, 0));
	}*/

	//physicsComponent->AddForce(Vector3f(0, -20, 0));
}
