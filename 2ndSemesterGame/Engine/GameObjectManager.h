#pragma once
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "SmartPointer.h"
#include "GameObject.h"
#include <vector>	

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	// TODO: lua add gameobject
	// TODO: Normal addition interface

	std::vector<Engine::OwningPointer<GameObject>> GameobjectList;
	void Update();

	void AddGameObejct(GameObject gameobject) {
		GameobjectList.push_back(Engine::OwningPointer<GameObject>(gameobject));
	}

	void Release();

private:
		
};


