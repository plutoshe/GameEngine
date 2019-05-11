#include "GameManager.h"
#include "Timing.h"

GameManager::GameManager()
{
	PSGameObjectManager = new GameObjectManager();
	Physics = new PhysicsController();
	Input = new InputController();
	Render = new RenderController();
}


GameManager::~GameManager()
{
	GLib::Shutdown();
}

bool GameManager::Initialization(HINSTANCE i_hInstance, int i_nCmdShow, const char * i_pWindowName, WORD i_IconID, unsigned int i_WindowWidth, unsigned int i_WindowHeight) {
	return GLib::Initialize(i_hInstance, i_nCmdShow, i_pWindowName, i_IconID, i_WindowWidth, i_WindowHeight);
}

void GameManager::Run() {
	PSGameObjectManager->Start();
	DeltaTime = 0;
	while (!bQuit) {
		DeltaTime += Timing::CalcLastFrameTime_ms();
		if (DeltaTime < 10) continue;
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