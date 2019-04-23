#include "ObstacleManager.h"

extern GameManager CurrentGameManager;

ObstacleManager::ObstacleManager()
{
}


ObstacleManager::~ObstacleManager()
{
}

ObstacleManager::Start() {
	for (int i = 0; i < 10; i++) {
		Engine::ObservingPointer<GameObject> newObstacle = CurrentGameManager.GetNewGameObject();
		obstaclesList.push(newObstacle);
	}
}

ObstacleManager::Update() {
	for (int i = 0; i < obstaclesList.get_size(); i++) {
		// update obstacles

	}

}
