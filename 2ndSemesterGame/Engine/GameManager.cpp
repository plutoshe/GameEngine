#include "GameManager.h"
#include "Timing.h"

GameManager::GameManager()
{
}


GameManager::~GameManager()
{
	gameobjects.clear();
}

bool GameManager::Initialization(HINSTANCE i_hInstance, int i_nCmdShow, const char * i_pWindowName, WORD i_IconID, unsigned int i_WindowWidth, unsigned int i_WindowHeight) {
	return GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 800, 600);
}


void GameManager::Rendering() {
	// IMPORTANT: Tell GLib that we want to start rendering
	GLib::BeginRendering();
	// Tell GLib that we want to render some sprites
	GLib::Sprites::BeginRendering();
	//GLib::Service(bQuit);
	if (!bQuit)
	{
		// IMPORTANT: Tell GLib that we want to start rendering
		GLib::BeginRendering();
		// Tell GLib that we want to render some sprites
		GLib::Sprites::BeginRendering();
		for (int id = 0; id < gameobjects.get_size(); id++)
			if (gameobjects[id]->irender)
			{

				static float moveDist = .01f;
				static float moveDir = moveDist;

				// Tell GLib to render this sprite at our calculated location
				auto pos = GLib::Point2D{ gameobjects[id]->position.x, gameobjects[id]->position.y};
				GLib::Sprites::RenderSprite(*gameobjects[id]->irender, pos, 0.0f);
			}

		// Tell GLib we're done rendering sprites
		GLib::Sprites::EndRendering();
		// IMPORTANT: Tell GLib we're done rendering
		GLib::EndRendering();

	}
}

void GameManager::PhysicsUpdate(double deltaTime) {
	
	for (int id = 0; id < gameobjects.get_size(); id++) {
		gameobjects[id]->UpdatePhysics(deltaTime);
	}
}

void GameManager::UpdateKey(unsigned int i_VKeyID) {

}

void GameManager::CheckInput(unsigned int i_VKeyID, bool bWentDown)
{
	DEBUG_LOG("current click: %x, %d, %d %d %d", i_VKeyID, 1, gameobjects[0]->position.x, gameobjects[0]->position.y, gameobjects[0]->position.z);
	UpdateKey(i_VKeyID);
	
	for (int id = 0; id < gameobjects.get_size(); id++)
		gameobjects[id]->CheckInput(i_VKeyID);
}

namespace GLib {
	extern HWND	g_hWnd;
}

void GameManager::InputGet() {
	MSG mssg;
	if (PeekMessage(&mssg, GLib::g_hWnd, 0, 0, PM_REMOVE))
	{
		switch (mssg.message)
		{
		case WM_QUIT:
			PostQuitMessage(0);

			break;

		case WM_KEYDOWN:
			WPARAM param = mssg.wParam;
			unsigned int c = (unsigned int)MapVirtualKey(param, MAPVK_VK_TO_CHAR);
			this->CheckInput(c, true);
			break;
		}
		// dispatch the message
		TranslateMessage(&mssg);
		DispatchMessage(&mssg);
	}
}

void GameManager::Run() {
	//GLib::Service(bQuit);
	
	while (!bQuit) {
		InputGet();
		double delta_time = Timing::CalcLastFrameTime_ms();
		PhysicsUpdate(delta_time);
		Rendering();

	}
	Release();
}

void GameManager::AddGameObejct(GameObject *gameobject) {
	gameobjects.push(gameobject);
}

void GameManager::Release() {
	for (int id = 0; id < gameobjects.get_size(); id++)
		if (gameobjects[id]->irender)
			GLib::Sprites::Release(gameobjects[id]->irender);
	GLib::Shutdown();
}