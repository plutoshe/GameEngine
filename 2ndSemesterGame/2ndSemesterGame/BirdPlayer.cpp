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
			physicsComponent->AddForce(Vector3f(0, 1000000, 0));
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

}

void BirdPlayer::Restart() {
	Message1->Active = false;
	Message2->Active = false;
	obstacleManager->Clear();
	obstacleManager->Restart();
	live = true;
	Vector3f a = StartPosition;
	BasicAttr.Position = StartPosition;
	physicsComponent->velocity.Clear();
	physicsComponent->HasGravity = true;
}

void BirdPlayer::ShowMessage() {
	Message1->Active = true;
	Message2->Active = true;
}


void BirdPlayer::Dead() {
	obstacleManager->Stop();

	physicsComponent->velocity.Clear();
	physicsComponent->HasGravity = false;
	live = false;
	ShowMessage();
}

void BirdPlayer::OnCollisionEnter(Engine::ObservingPointer<GameObject> other) {
	Dead();
}

void BirdPlayer::Start() {
	Restart();
}