#pragma once
#include "GameObject.h"
#include "SmartPointer.h"
class ObstacleManager: public GameObject
{
public:
	ObstacleManager();
	~ObstacleManager();
	DataStructure::List<Engine::ObservingPointer<GameObject>> obstaclesList;
	void Start();
	void Update();
};

