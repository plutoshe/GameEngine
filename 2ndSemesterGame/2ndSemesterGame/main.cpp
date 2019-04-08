#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <Windows.h>
#include <conio.h>
#include <ctime>


#include "GLib.h"
#include "Log.h"
#include "Timing.h"
#include "GameObject.h"
#include "GameManager.h"
#include "Vector3D.h"

void runGame(HINSTANCE i_hInstance, int i_nCmdShow) {

	GameManager myGame;
	myGame.Initialization(i_hInstance, i_nCmdShow, "GLibTest", -1, 800, 600);
	GameObject ch1;
	ch1.BasicAttr->Position = Vector3f(-180.f, 100.f, 0);
	/*ch1.mass = 10;
	ch1.dragCof = 1;*/
	//ch1.CreateSprite("data\\GoodGuy.dds");
	myGame.AddGameObject(ch1);
	myGame.Run();
	return;
}

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	runGame(i_hInstance, i_nCmdShow);
	#if defined _DEBUG
		_CrtDumpMemoryLeaks();
	#endif // _DEBUG

}


