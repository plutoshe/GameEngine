#include "GameManager.h"

GameManager::GameManager()
{
	PSGameObjectManager = new GameObjectManager();
	selfPointer = this;
	PSGameObjectManager->belongedGameManager = selfPointer;
	Physics = new PhysicsController();
	Input = new InputController();
    bQuit = false;
}


GameManager::~GameManager() {}

bool GameManager::Initialization() {
	// Start Phase
	//Input->Start();
	//Physics->Start();
	Render->Start();
	PSGameObjectManager->Start();
	DeltaTime = 0; frameID = 0;
	return true;

}

bool GameManager::Once() {
	DeltaTime += Timing::CalcLastFrameTime_ms();
	if (DeltaTime < 10) return true;
	DeltaTime = 0;
	frameID++;
	Input->Update();
	PSGameObjectManager->Update();
	Physics->Update(DeltaTime / 1000);
	Render->Update();
	//Render->
	if (Input->IsKeyDown(27)) return true;
	return false;
}

void GameManager::Run() {
	Initialization();
    while (!bQuit) {
		if (Once()) {
			break;
		}
    }

	Release();
}

Engine::ObservingPointer<GameObject> GameManager::GetNewGameObject() {
	return PSGameObjectManager->GetNewGameObject();
}


void GameManager::Release() {
}
