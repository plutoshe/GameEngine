#pragma once
#include "Engine.h"
#include "ObstacleManager.h"
class BirdPlayer: public GameObject
{
public:
	BirdPlayer(Engine::ObservingPointer<ObstacleManager> _obstacleManager) : obstacleManager(_obstacleManager) {}
	BirdPlayer(
		Engine::ObservingPointer<ObstacleManager> _obstacleManager,
		Engine::ObservingPointer<GameObject> _message1,
		Engine::ObservingPointer<GameObject> _message2) : obstacleManager(_obstacleManager), Message1(_message1), Message2(_message2) {}
	BirdPlayer();
	~BirdPlayer();
	bool live = true;
	
	void Restart();
	void ShowMessage();
	void Dead();
	virtual void OnCollisionEnter(Engine::ObservingPointer<GameObject> other);
	virtual void Update();
	virtual void Start();

	Engine::ObservingPointer<GameObject> Message1;
	Engine::ObservingPointer<GameObject> Message2;
	Engine::ObservingPointer<ObstacleManager> obstacleManager;
	Vector3f StartPosition = Vector3f(-180,100,0);
};

