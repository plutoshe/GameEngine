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

bool GameManager::Initialization() {
	frameID = 0;
    return true;

}
void GameManager::Run() {
	PSGameObjectManager->Start();
	DeltaTime = 0;

	while (!bQuit) {
		DeltaTime += Timing::CalcLastFrameTime_ms();
		if (DeltaTime < 10) continue;
		frameID++;
		qDebug() << frameID;
		Input->Update();
		PSGameObjectManager->Update();
		Physics->Update(DeltaTime / 1000);
		Render->Update();
		DeltaTime = 0;
		if (Input->IsKeyDown(27)) break;
	}

	Release();
}

Engine::ObservingPointer<GameObject> GameManager::GetNewGameObject() {
	return PSGameObjectManager->GetNewGameObject();
}


void GameManager::Release() {
}
