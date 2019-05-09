#include <iostream>
#include <cstdio>

#include "GameObject.h"
#include "Engine.h"

class CollisionObject: public GameObject {
	void Update() {
		AddForce(Vector3f(rand() % 1000 - 500, rand() % 1000 - 500, 0));
	}
};

extern GameManager CurrentGameManager;
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
	std::string collisionSpriteName = "a";
	AddCollisionObject(Vector3f(0, -screenHeight / 2, 0), screenWidth, 10, collisionSpriteName);
	AddCollisionObject(Vector3f(0, screenHeight / 2, 0), screenWidth, 10, collisionSpriteName);
	AddCollisionObject(Vector3f(-screenWidth / 2, 0, 0), 10, screenHeight, collisionSpriteName);
	AddCollisionObject(Vector3f(screenWidth / 2, 0, 0), 10, screenHeight, collisionSpriteName);

	// add collision objects
	int posX = 20;
	int posY = 20;
	for (int i = 0; i < (screenWidth / 10 * screenHeight / 10) / 100; i++) {
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
	int screenWidth = 1024;
	int screenHeight = 768;
	CurrentGameManager.Initialization(i_hInstance, i_nCmdShow, "CollisionTest", -1, screenWidth, screenHeight);
	CollisionTest(screenWidth, screenHeight);
}