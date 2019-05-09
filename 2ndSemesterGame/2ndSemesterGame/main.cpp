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
#include "SSERedef.h"
#include "Player.h"
#include "ObstacleManager.h"
#include "Collider2D.h"

extern GameManager CurrentGameManager = GameManager();

void runGame(HINSTANCE i_hInstance, int i_nCmdShow) {
	CurrentGameManager.Initialization(i_hInstance, i_nCmdShow, "GLibTest", -1, 800, 600);
	Engine::ObservingPointer<Player> ch1 = CurrentGameManager.AddGameObject(Player());
	ch1->BasicAttr.Position = Vector3f(-180.f, 0.f, 0);
	ch1->NewRenderComponent();
	ch1->GetRenderComponent()->CreateSprite("data\\charactor.dds", 100, 100);
	ch1->NewPhysicsComponent();
	ch1->physicsComponent->Mass = 10;
	ch1->physicsComponent->DragCof = 1;
	ch1->physicsComponent->AddCollider(BoxCollider2D(Vector2f(0,0), Vector2f(100,100)));

	Engine::ObservingPointer<GameObject> ch2 = CurrentGameManager.GetNewGameObject();
	ch2->BasicAttr.Position = Vector3f(180.f, 30.f, 0);
	ch2->NewRenderComponent();
	ch2->GetRenderComponent()->CreateSprite("data\\BadGuy.dds", 100, 100);
	ch2->NewPhysicsComponent();
	ch2->physicsComponent->AddCollider(BoxCollider2D(Vector2f(0, 0), Vector2f(100, 100)));
	/*ch1.mass = 10;
	ch1.dragCof = 1;*/
	//ch1.CreateSprite("data\\GoodGuy.dds");
	//CurrentGameManager.AddGameObject(ch1);
	CurrentGameManager.Run();
	return;
}


void myGame(HINSTANCE i_hInstance, int i_nCmdShow) {
	
	CurrentGameManager.Initialization(i_hInstance, i_nCmdShow, "GLibTest", -1, 800, 600);
	Engine::ObservingPointer<Player> ch1 = CurrentGameManager.AddGameObject(Player());
	ch1->BasicAttr.Position = Vector3f(-180.f, 100.f, 0);
	ch1->NewRenderComponent();
	ch1->GetRenderComponent()->CreateSprite("data\\charactor.dds");

	Engine::ObservingPointer<ObstacleManager> ch2 = CurrentGameManager.AddGameObject(ObstacleManager());
	ch2->SpriteName = "data\\BadGuy.dds";
	//ch2->AddONewbstacle();
	/*ch1.mass = 10;
	ch1.dragCof = 1;*/
	//ch1.CreateSprite("data\\GoodGuy.dds");
	//CurrentGameManager.AddGameObject(ch1);
	CurrentGameManager.Run();
	return;
}
extern void CollisionApp(HINSTANCE i_hInstance, int i_nCmdShow);

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	//runGame(i_hInstance, i_nCmdShow);
	CollisionApp(i_hInstance, i_nCmdShow);
	#if defined _DEBUG
		_CrtDumpMemoryLeaks();
	#endif // _DEBUG

}

