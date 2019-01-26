#include "GameManager.h"
#include "Timing.h"

GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}

bool GameManager::Initialization(HINSTANCE i_hInstance, int i_nCmdShow, const char * i_pWindowName, WORD i_IconID, unsigned int i_WindowWidth, unsigned int i_WindowHeight) {
	return GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 800, 600);
}


void GameManager::Rendering() {
	// IMPORTANT: Tell GLib that we want to start rendering
	GLib::BeginRendering();
	// Tell GLib that we want to render some sprites
	GLib::Sprites::BeginRendering();
	GLib::Service(bQuit);
	if (!bQuit)
	{
		// IMPORTANT: Tell GLib that we want to start rendering
		GLib::BeginRendering();
		// Tell GLib that we want to render some sprites
		GLib::Sprites::BeginRendering();
		for (int id = 0; id < gameobjects.size(); id++)
			if (gameobjects[id].irender)
			{

				static float moveDist = .01f;
				static float moveDir = moveDist;

				// Tell GLib to render this sprite at our calculated location
				auto pos = GLib::Point2D{ gameobjects[id].position.x(), gameobjects[id].position.y()};
				GLib::Sprites::RenderSprite(*gameobjects[id].irender, pos, 0.0f);
			}

		// Tell GLib we're done rendering sprites
		GLib::Sprites::EndRendering();
		// IMPORTANT: Tell GLib we're done rendering
		GLib::EndRendering();

	}
}

void GameManager::PhysicsUpdate() {

}

void GameManager::CheckInput(unsigned int i_VKeyID, bool bWentDown)
{
	DEBUG_LOG("current click: %d", i_VKeyID);
	for (int id = 0; id < gameobjects.size(); id++)
		gameobjects[id].CheckInput(i_VKeyID);
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
			char c = MapVirtualKey(param, MAPVK_VK_TO_CHAR);
			this->CheckInput(c, true);
			break;
		}
		// dispatch the message
		TranslateMessage(&mssg);
		DispatchMessage(&mssg);
	}
}

void GameManager::Run() {
	GLib::Service(bQuit);
	
	while (!bQuit) {
		InputGet();
		double delta_time = Timing::CalcLastFrameTime_ms();
		Rendering();
	}
	Release();
}

void GameManager::AddGameObejct(GameObject gameobject) {
	gameobjects.push_back(gameobject);
}

void GameManager::Release() {
	for (int id = 0; id < gameobjects.size(); id++)
		if (gameobjects[id].irender)
			GLib::Sprites::Release(gameobjects[id].irender);
	GLib::Shutdown();
}