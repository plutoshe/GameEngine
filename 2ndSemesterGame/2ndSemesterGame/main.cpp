#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <Windows.h>
#include <conio.h>
#include <ctime>

#include "Env.h"

#include "Player.h"
#include "ObstacleManager.h"

GameManager CurrentGameManager = GameManager();

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

class CollisionObject : public GameObject {
	void Update() {
		AddForce(Vector3f(rand() % 300 - 150, rand() % 300 - 150, 0));
	}
};

DataStructure::List<Engine::ObservingPointer<CollisionObject>> collisionObjectList;
void AddCollisionObject(Vector3f position, int width, int height, std::string spriteName) {
	Engine::ObservingPointer<CollisionObject> ch2 = CurrentGameManager.AddGameObject(CollisionObject());
	ch2->BasicAttr.Position = position;
	ch2->NewPhysicsComponent();
	ch2->physicsComponent->AddCollider(BoxCollider2D(Vector2f(0, 0), Vector2f(width, height)));
	ch2->NewRenderComponent();
	ch2->renderComponent->CreateSprite(spriteName.c_str(), width, height);
	collisionObjectList.push(ch2);
	return;
}


void CollisionTest(int screenWidth, int screenHeight) {
	// add border
	//
	std::string collisionSpriteName = "data\\BadGuy.dds";
	AddCollisionObject(Vector3f(0, -screenHeight / 2, 0), screenWidth, 30, collisionSpriteName);
	AddCollisionObject(Vector3f(0, screenHeight / 2, 0), screenWidth, 30, collisionSpriteName);
	AddCollisionObject(Vector3f(-screenWidth / 2, 0, 0), 30, screenHeight, collisionSpriteName);
	AddCollisionObject(Vector3f(screenWidth / 2, 0, 0), 30, screenHeight, collisionSpriteName);
	for (int i = 0; i < 4; i++)
		collisionObjectList[i]->physicsComponent->IsStatic = true;
	// add collision objects
	int posX = 20;
	int posY = 20;
	for (int i = 0; i < 10; i++) {
		AddCollisionObject(
			Vector3f(posX, posY, 0),
			10, 10, collisionSpriteName);
		posY += 20;
		if (posY > screenHeight) {
			posX += 20;
			posY = 20;
		}
	}
	CurrentGameManager.Run();
}

void CollisionApp(HINSTANCE i_hInstance, int i_nCmdShow) {
	int screenWidth = 800;
	int screenHeight = 600;
	CurrentGameManager.Initialization(i_hInstance, i_nCmdShow, "CollisionTest", -1, screenWidth, screenHeight);
	CollisionTest(screenWidth, screenHeight);
}
int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	//runGame(i_hInstance, i_nCmdShow);
	CollisionApp(i_hInstance, i_nCmdShow);
	#if defined _DEBUG
		_CrtDumpMemoryLeaks();
	#endif // _DEBUG

}

