#pragma once
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "SmartPointer.h"
#include "GameObject.h"
#include "List.h"
#include "Log.h"
class GameManager;
class GameObjectManager
{
public:
	GameObjectManager() {
	}
	~GameObjectManager() {}

	Engine::ObservingPointer<GameManager> belongedGameManager;
	// TODO: lua add gameobject
	// TODO: Normal addition interface
	
	DataStructure::List<Engine::OwningPointer<GameObject>> GameobjectList;

	void updateOwningGameObjectLink(Engine::ObservingPointer<GameObject> g);

	void Update();
	template<class T>
    Engine::ObservingPointer<GameObject> AddGameObject(Engine::OwningPointer<T> gameobject) {
		
		GameobjectList.push(Engine::OwningPointer<T>(gameobject));
		Engine::ObservingPointer<GameObject> currentGameObject = GameobjectList[GameobjectList.get_size() - 1];
		currentGameObject->UpdateConnectionPointer(currentGameObject);
		updateOwningGameObjectLink(currentGameObject);
		return currentGameObject;
	}

	void RemoveGameObject(Engine::ObservingPointer<GameObject> p);

	Engine::ObservingPointer<GameObject> GetNewGameObject() {
		Engine::OwningPointer<GameObject> emptyGameObject(new GameObject());
		GameobjectList.push(emptyGameObject);
		emptyGameObject->UpdateConnectionPointer(emptyGameObject);
		updateOwningGameObjectLink(emptyGameObject);
		return emptyGameObject;
	}
	void Start();
	void Release();

private:
		
};


