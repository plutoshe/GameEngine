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
//
//
//void GameManager::Rendering() {
//	// IMPORTANT: Tell GLib that we want to start rendering
//	GLib::BeginRendering();
//	// Tell GLib that we want to render some sprites
//	GLib::Sprites::BeginRendering();
//	//GLib::Service(bQuit);
//	if (!bQuit)
//	{
//		// IMPORTANT: Tell GLib that we want to start rendering
//		GLib::BeginRendering();
//		// Tell GLib that we want to render some sprites
//		GLib::Sprites::BeginRendering();
//		for (int id = 0; id < gameobjects.get_size(); id++)
//			if (gameobjects[id]->irender)
//			{
//
//				static float moveDist = .01f;
//				static float moveDir = moveDist;
//
//				// Tell GLib to render this sprite at our calculated location
//				auto pos = GLib::Point2D{ gameobjects[id]->position.x, gameobjects[id]->position.y};
//				GLib::Sprites::RenderSprite(*gameobjects[id]->irender, pos, 0.0f);
//			}
//
//		// Tell GLib we're done rendering sprites
//		GLib::Sprites::EndRendering();
//		// IMPORTANT: Tell GLib we're done rendering
//		GLib::EndRendering();
//
//	}
//}

void GameManager::Run() {
	//GLib::Service(bQuit);
	
	while (!bQuit) {
		DeltaTime = Timing::CalcLastFrameTime_ms();
		Input->Update();
		PSGameObejctManager->Update();
		//Physics.Update();
		Render->Update();
	}
	Release();
}

void GameManager::AddGameObject(GameObject gameobject) {
	PSGameObejctManager->AddGameObejct(gameobject);
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