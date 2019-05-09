#include "Env.h"
#include "BirdPlayer.h"
#include "GameManager.h"
#include "PhysicsComponent.h"
#include "Log.h"

BirdPlayer::BirdPlayer()
{
}


BirdPlayer::~BirdPlayer()
{
}

void BirdPlayer::Update() {
	if (live) {
		if (CurrentGameManager.Input->IsKeyDown('J')) {
			physicsComponent->AddForce(Vector3f(0, 1000, 0));
		}
	} else {
		if (CurrentGameManager.Input->IsKeyDown('R')) {
			Restart();
		}
	}

	// Mouse Press
	/*if (CurrentGameManager.Input->IsMouseDown(0)) {
		physicsComponent->AddForce(Vector3f(0, 100000, 0));
	}*/

	//physicsComponent->AddForce(Vector3f(0, -20, 0));
}

void BirdPlayer::Restart() {
	Message1->Active = false;
	Message2->Active = false;
	obstacleManager->Active = true;
}

void BirdPlayer::ShowMessage() {
	Message1->Active = true;
	Message2->Active = true;
}


void BirdPlayer::Dead() {
	obstacleManager->Clear();
	obstacleManager->Active = false;
	live = false;
	ShowMessage();
}

void BirdPlayer::OnCollisionEnter(GameObject other) {
	Dead();
	
}