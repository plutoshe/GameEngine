#include "GameManager.h"
#include "Timing.h"
#include <Qdebug>
GameManager::GameManager()
{
	PSGameObjectManager = new GameObjectManager();
	Physics = new PhysicsController();
	Input = new InputController();
    bQuit = false;
}


GameManager::~GameManager() {}
Engine::OwningPointer<GameManager> GameManager::Instance = nullptr;

bool GameManager::Initialization() {
    return true;

}
void GameManager::Run() {
    // Start Phase
    //Input->Start();
    //Physics->Start();
    Render->Start();
	PSGameObjectManager->Start();
	DeltaTime = 0; frameID = 0;
    while (!bQuit) {

        DeltaTime += Timing::CalcLastFrameTime_ms();
        qDebug() << DeltaTime;
        if (DeltaTime < 10) continue;
        DeltaTime = 0;
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
