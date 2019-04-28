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
	Engine::ObservingPointer<Obstacle> AddNewObstacle(int width, int height);

	std::string SpriteName;
	int StrideLength = 30;
	double LastTime = 0;
};

