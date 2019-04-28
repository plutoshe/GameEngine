#pragma once
#include "GameObject.h"
#include "SmartPointer.h"
#include "Obstacle.h"
#include <string>
class ObstacleManager: public GameObject
{
public:
	ObstacleManager() {}
	ObstacleManager(std::string _spriteName) { SpriteName = _spriteName; }
	~ObstacleManager() {}
	DataStructure::List<Engine::ObservingPointer<GameObject>> obstaclesList;
	void Start();
	void Update();
	void AddObstacle();

	std::string SpriteName;
};

