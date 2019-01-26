#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <Windows.h>
#include <conio.h>
#include <ctime>
#if defined _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG

#include "GLib.h"
#include "Log.h"
#include "Timing.h"
#include "GameObject.h"
#include "GameManager.h"

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	GameManager myGame;
	myGame.Initialization(i_hInstance, i_nCmdShow, "GLibTest", -1, 800, 600);
	
	GameObject ch1;
	ch1.position = Vector3D(-180.f, 100.f, 0);
	ch1.mass = 10;
	ch1.drag = 10;
	ch1.CreateSprite("data\\GoodGuy.dds");
	myGame.AddGameObejct(ch1);
	myGame.Run();
	#if defined _DEBUG
		_CrtDumpMemoryLeaks();
	#endif // _DEBUG

}


