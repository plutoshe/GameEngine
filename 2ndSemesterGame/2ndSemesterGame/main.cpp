#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <Windows.h>
#include <conio.h>
#include <ctime>

#include "Env.h"
#include "Player.h"
#include "ObstacleManager.h"
#include "BirdPlayer.h"

GameManager CurrentGameManager = GameManager();
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

void runGame(HINSTANCE i_hInstance, int i_nCmdShow) {
	
	CurrentGameManager.Initialization(i_hInstance, i_nCmdShow, "GLibTest", -1, 800, 600);
	int screenHeight = 600;
	int screenWidth = 800;
	std::string collisionSpriteName = "data\\Block.dds";
	AddCollisionObject(Vector3f(0, (float)(-screenHeight)/ 2, 0), screenWidth, 30, collisionSpriteName);
	AddCollisionObject(Vector3f(0, (float)(screenHeight) / 2, 0), screenWidth, 30, collisionSpriteName);
	AddCollisionObject(Vector3f((float)(-screenWidth) / 2, 0, 0), 30, screenHeight, collisionSpriteName);
	AddCollisionObject(Vector3f((float)(screenWidth) / 2, 0, 0), 30, screenHeight, collisionSpriteName);
	for (int i = 0; i < 4; i++)
		collisionObjectList[i]->physicsComponent->IsStatic = true;

	Engine::ObservingPointer<Player> ch1 = CurrentGameManager.AddGameObject(Player());
	ch1->BasicAttr.Position = Vector3f(-180.f, 0.f, 0);
	ch1->NewRenderComponent();
	ch1->GetRenderComponent()->CreateSprite("data\\charactor.dds", 100, 100);
	ch1->NewPhysicsComponent();
	ch1->physicsComponent->Mass = 10;
	ch1->physicsComponent->DragCof = 1;
	ch1->physicsComponent->AddCollider(BoxCollider2D(Vector2f(0,0), Vector2f(100,100)));

	Engine::ObservingPointer<GameObject> ch2 = CurrentGameManager.GetNewGameObject();
	ch2->BasicAttr.Position = Vector3f(180.f, 0.f, 0);
	ch2->NewRenderComponent();
	ch2->GetRenderComponent()->CreateSprite("data\\Movable.dds", 100, 100);
	ch2->NewPhysicsComponent();
	ch2->physicsComponent->AddCollider(BoxCollider2D(Vector2f(0, 0), Vector2f(100, 100)));

	Engine::ObservingPointer<GameObject> ch3 = CurrentGameManager.GetNewGameObject();
	ch3->BasicAttr.Position = Vector3f(180.f, -150.f, 0);
	ch3->NewRenderComponent();
	ch3->GetRenderComponent()->CreateSprite("data\\Stationary.dds", 100, 100);
	ch3->NewPhysicsComponent();
	ch3->physicsComponent->AddCollider(BoxCollider2D(Vector2f(0, 0), Vector2f(100, 100)));
	ch3->physicsComponent->IsStatic = true;

	/*ch1.mass = 10;
	ch1.dragCof = 1;*/
	//ch1.CreateSprite("data\\GoodGuy.dds");
	//CurrentGameManager.AddGameObject(ch1);
	CurrentGameManager.Run();
	return;
}


void myGame(HINSTANCE i_hInstance, int i_nCmdShow) {
	
	CurrentGameManager.Initialization(i_hInstance, i_nCmdShow, "GLibTest", -1, 800, 600);
	std::string collisionSpriteName = "data\\Block.dds";
	int screenHeight = 600;
	int screenWidth = 800;
	AddCollisionObject(Vector3f(0, -screenHeight / 2, 0), screenWidth, 30, collisionSpriteName);
	AddCollisionObject(Vector3f(0, screenHeight / 2, 0), screenWidth, 30, collisionSpriteName);
	AddCollisionObject(Vector3f(-screenWidth / 2, 0, 0), 30, screenHeight, collisionSpriteName);
	AddCollisionObject(Vector3f(screenWidth / 2, 0, 0), 30, screenHeight, collisionSpriteName);
	for (int i = 0; i < 4; i++)
		collisionObjectList[i]->physicsComponent->IsStatic = true;

	Engine::ObservingPointer<ObstacleManager> ch2 = CurrentGameManager.AddGameObject(ObstacleManager());
	ch2->SpriteName = "data\\Block.dds";

	Engine::ObservingPointer<Player> message1 = CurrentGameManager.AddGameObject(GameObject());
	message1->BasicAttr.Position = Vector3f(0.f, 100.f, 0);
	message1->NewRenderComponent();
	message1->GetRenderComponent()->CreateSprite("data\\DiedMessage.dds", 100, 100);

	/*Engine::ObservingPointer<Player> message2 = CurrentGameManager.AddGameObject(GameObject());
	message2->BasicAttr.Position = Vector3f(0.f, -100.f, 0);
	message2->NewRenderComponent();
	message2->GetRenderComponent()->CreateSprite("data\\GoodGuy.dds", 100, 100);
*/
	Engine::ObservingPointer<BirdPlayer> ch1 = CurrentGameManager.AddGameObject(BirdPlayer(ch2, message1));
	ch1->StartPosition = Vector3f(-200.f, 100.f, 0);
	ch1->NewRenderComponent();
	ch1->GetRenderComponent()->CreateSprite("data\\charactor.dds", 50, 50);
	ch1->NewPhysicsComponent();
	ch1->physicsComponent->AddCollider(BoxCollider2D(Vector2f(0, 0), Vector2f(50, 50)));
	ch1->physicsComponent->HasGravity = true;
	ch1->physicsComponent->DragCof = 0;
	ch1->physicsComponent->Mass = 100;

	
	//ch2->AddONewbstacle();
	/*ch1.mass = 10;
	ch1.dragCof = 1;*/
	//ch1.CreateSprite("data\\GoodGuy.dds");
	//CurrentGameManager.AddGameObject(ch1);
	CurrentGameManager.Run();
	return;
}

void CollisionTest(int screenWidth, int screenHeight) {
	// add border
	//
	std::string collisionSpriteName = "data\\Block.dds";
	AddCollisionObject(Vector3f(0, (float)(-screenHeight / 2), 0), screenWidth, 30, collisionSpriteName);
	AddCollisionObject(Vector3f(0, (float)(screenHeight / 2), 0), screenWidth, 30, collisionSpriteName);
	AddCollisionObject(Vector3f((float)(-screenWidth / 2), 0, 0), 30, screenHeight, collisionSpriteName);
	AddCollisionObject(Vector3f((float)(screenWidth / 2), 0, 0), 30, screenHeight, collisionSpriteName);
	for (int i = 0; i < 4; i++)
		collisionObjectList[i]->physicsComponent->IsStatic = true;
	// add collision objects
	float posX = -400.f + 50.f;
	float posY = -300.f + 50.f;
	for (int i = 0; i < 30; i++) {
		AddCollisionObject(
			Vector3f(posX, posY, 0),
			10, 10, collisionSpriteName);
		posY += 20;
		if (posY > screenHeight / 2 - 50) {
			posX += 20;
			posY = -300 + 50;
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
	//myGame(i_hInstance, i_nCmdShow);
	// runGame(i_hInstance, i_nCmdShow);
	CollisionApp(i_hInstance, i_nCmdShow);
	#if defined _DEBUG
		_CrtDumpMemoryLeaks();
	#endif // _DEBUG

}

