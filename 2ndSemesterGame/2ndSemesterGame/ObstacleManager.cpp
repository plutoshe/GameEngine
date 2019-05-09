#include <time.h>
#include "Env.h"
#include "ObstacleManager.h"
#include "GameManager.h"

void ObstacleManager::Start() {
	srand(time(NULL));
	/*for (int i = 0; i < 10; i++) {
		Engine::ObservingPointer<GameObject> newObstacle = CurrentGameManager.GetNewGameObject();
		obstaclesList.push(newObstacle);
	}*/
}

void ObstacleManager::Clear() {
	for (int i = obstaclesList.get_size() - 1; i >= 0; i--) 
		CurrentGameManager.RemoveGameObject(obstaclesList[i]);
	obstaclesList.Clear();
}

void ObstacleManager::Update() {
	for (int i = obstaclesList.get_size() - 1; i >= 0; i--) {
		// update obstacles
		obstaclesList[i]->BasicAttr.Position.x -= 200.f * CurrentGameManager.DeltaTime / 1000;
		if (obstaclesList[i]->BasicAttr.Position.x < -300 -StrideLength / 2) {
			CurrentGameManager.RemoveGameObject(obstaclesList[i]);
			obstaclesList.remove(i);
		}
	}
	LastTime += CurrentGameManager.DeltaTime / 1000;
	if (LastTime > 0.5f && rand() % 10000 < 3) {
		Vector2f startPoint;
		Vector2f stride;
		if (rand() % 2 == 0) {
			startPoint = Vector2f(400 + StrideLength / 2, 300 - StrideLength / 2);
			stride = Vector2f(0, -StrideLength);
		}
		else {
			startPoint = Vector2f(400 + StrideLength / 2, -300 + StrideLength / 2);
			stride = Vector2f(0, StrideLength);
		}
		Engine::ObservingPointer<Obstacle> newOne = AddNewObstacle(StrideLength, (rand() % 5 * 2 + 7) * StrideLength);
		newOne->BasicAttr.Position = startPoint;
		LastTime = 0;
	}
}

Engine::ObservingPointer<Obstacle> ObstacleManager::AddNewObstacle(int width, int height) {
	Engine::ObservingPointer<Obstacle> ch2 = CurrentGameManager.AddGameObject(Obstacle());
	//ch2->BasicAttr.Position = 
	ch2->NewPhysicsComponent();
	ch2->physicsComponent->AddCollider(BoxCollider2D(Vector2f(0, 0), Vector2f(width, height)));
	ch2->NewRenderComponent();
	ch2->renderComponent->CreateSprite(SpriteName.c_str(), width, height);
	obstaclesList.push(ch2);
	return ch2;
}
