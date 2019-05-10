#pragma once
#include "Engine.h"
#include "ObstacleManager.h"
class BirdPlayer: public GameObject
{
public:
	BirdPlayer(Engine::ObservingPointer<ObstacleManager> _obstacleManager) : obstacleManager(_obstacleManager) {}
	BirdPlayer(
		Engine::ObservingPointer<ObstacleManager> _obstacleManager,
		Engine::ObservingPointer<GameObject> _displayMessage) : obstacleManager(_obstacleManager), DisplayMessage(_displayMessage) {}
	BirdPlayer();
	~BirdPlayer();
	bool live = true;
	
	void Restart();
	void ShowMessage();
	void Dead();
	virtual void OnCollisionEnter(Engine::ObservingPointer<GameObject> other);
	virtual void Update();
	virtual void Start();

	Engine::ObservingPointer<GameObject> DisplayMessage;
	Engine::ObservingPointer<ObstacleManager> obstacleManager;
	Vector3f StartPosition = Vector3f(-180,100,0);
};

