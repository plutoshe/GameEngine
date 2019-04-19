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
		Engine::ObservingPointer<GameObject> currentGameObject = GameobjectList[GameobjectList.size() - 1];
		currentGameObject->UpdateConnectionPointer(currentGameObject);
	}

	Engine::ObservingPointer<GameObject> GetNewGameObject() {
		Engine::OwningPointer<GameObject> emptyGameObject(new GameObject());
		GameobjectList.push_back(emptyGameObject);
		emptyGameObject->UpdateConnectionPointer(emptyGameObject);
		return emptyGameObject;
	}

	void Release();

private:
		
};


