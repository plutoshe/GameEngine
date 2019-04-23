#include "Player.h"

extern GameManager CurrentGameManager;

Player::Player()
{
}


Player::~Player()
{
}

void Player::Update() {
	if (CurrentGameManager.Input->KeyStatus.Has('J')) {
		physicsComponent.AddForce(new Vector3f(0,10,0));
	}
		
}
