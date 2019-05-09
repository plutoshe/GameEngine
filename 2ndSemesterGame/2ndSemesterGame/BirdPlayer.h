#pragma once
#include "GameObject.h"
#include "SmartPointer.h"
#include "ObstacleManager.h"
class BirdPlayer: public GameObject
{
public:
	BirdPlayer();
	~BirdPlayer();
	bool live = true;
	Engine::ObserverPointer<GameObject> Message1;
	Engine::ObserverPointer<GameObject> Message2;
	Engine::ObserverPointer<ObstacleManager> obstacleManager;
	void Restart();
	virtual void OnCollisionEnter(GameObject other);
	virtual void Update();
};

