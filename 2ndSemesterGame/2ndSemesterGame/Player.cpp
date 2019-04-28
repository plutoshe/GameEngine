#include "Player.h"
#include "GameManager.h"
#include "PhysicsComponent.h"
#include "Log.h"

extern GameManager CurrentGameManager;

Player::Player()
{
}


Player::~Player()
{
}

void Player::Update() {
	if (CurrentGameManager.Input->IsKeyDown('J')) {
		physicsComponent->AddForce(Vector3f(0,-100000,0));
	}
	//physicsComponent->AddForce(Vector3f(0, -20, 0));
}
