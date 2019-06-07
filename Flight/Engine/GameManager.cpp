#include "GameManager.h"
#include "Timing.h"
#include <Qdebug>
GameManager::GameManager()
{
	PSGameObjectManager = new GameObjectManager();
	Physics = new PhysicsController();
	Input = new InputController();
}


GameManager::~GameManager() {}
Engine::OwningPointer<GameManager> GameManager::Instance = nullptr;

bool GameManager::Initialization() {
    return true;

}
void GameManager::Run() {
	// Start Phase for controllers
	PSGameObjectManager->Start();
	//Render->Start();

	DeltaTime = 0; frameID = 0;
	while (!bQuit) {
		DeltaTime += Timing::CalcLastFrameTime_ms();
        if (DeltaTime < 100) continue;
		frameID++;
        Input->Update();
		PSGameObjectManager->Update();
		Physics->Update(DeltaTime / 1000);
        Render->Update();
		if (Input->IsKeyDown(27)) break;
	}

	Release();
}

Engine::ObservingPointer<GameObject> GameManager::GetNewGameObject() {
	return PSGameObjectManager->GetNewGameObject();
}


void GameManager::Release() {
}
