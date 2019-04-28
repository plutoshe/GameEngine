#include "ObstacleManager.h"
#include "GameManager.h"

extern GameManager CurrentGameManager;

void ObstacleManager::Start() {
	for (int i = 0; i < 10; i++) {
		Engine::ObservingPointer<GameObject> newObstacle = CurrentGameManager.GetNewGameObject();
		obstaclesList.push(newObstacle);
	}
}

void ObstacleManager::Update() {
	for (int i = 0; i < obstaclesList.get_size(); i++) {
		// update obstacles

	}
}

void ObstacleManager::AddObstacle() {
	Engine::ObservingPointer<Obstacle> ch2 = CurrentGameManager.AddGameObject(Obstacle());
	ch2->NewPhysicsComponent();
	ch2->physicsComponent->AddCollider(BoxCollider2D(Vector2f(0, 0), Vector2f(100, 100)));
	ch2->NewRenderComponent();
	ch2->renderComponent->CreateSprite(SpriteName.c_str());
}
