#include "GameManager.h"
#include "Timing.h"

GameManager::GameManager()
{
	PSGameObejctManager = new GameObjectManager();
	Physics = new PhysicsController();
	Input = new InputController();
	Render = new RenderController();
}


GameManager::~GameManager()
{
	GLib::Shutdown();

}

bool GameManager::Initialization(HINSTANCE i_hInstance, int i_nCmdShow, const char * i_pWindowName, WORD i_IconID, unsigned int i_WindowWidth, unsigned int i_WindowHeight) {
	return GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 800, 600);
}



void GameManager::Run() {
	//GLib::Service(bQuit);
	PSGameObejctManager->Start();
	while (!bQuit) {
		DeltaTime = Timing::CalcLastFrameTime_ms();
		Input->Update();
		PSGameObejctManager->Update();
		Physics->Update(DeltaTime);
		Render->Update();
	}
	Release();
}

void GameManager::AddGameObject(GameObject gameobject) {
	PSGameObejctManager->AddGameObject(gameobject);
}

Engine::ObservingPointer<GameObject> GameManager::GetNewGameObject() {
	return PSGameObejctManager->GetNewGameObject();
}


void GameManager::Release() {
	// Component Release
	PSGameObejctManager->Release();
	/*Render->Release();
	Physics->Release();
	Input->Release();*/
	
	// Process after release
	GLib::Shutdown();
}