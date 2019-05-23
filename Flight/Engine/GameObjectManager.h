#pragma once
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "SmartPointer.h"
#include "GameObject.h"
#include "List.h"
#include "Log.h"

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	// TODO: lua add gameobject
	// TODO: Normal addition interface

	DataStructure::List<Engine::OwningPointer<GameObject>> GameobjectList;

	void Update();
	template<class T>
	Engine::ObservingPointer<GameObject> AddGameObject(T gameobject) {
		
		GameobjectList.push(Engine::OwningPointer<T>(gameobject));
		Engine::ObservingPointer<GameObject> currentGameObject = GameobjectList[GameobjectList.get_size() - 1];
		currentGameObject->UpdateConnectionPointer(currentGameObject);
		return currentGameObject;
	}

	void RemoveGameObject(Engine::ObservingPointer<GameObject> p);


	Status AddGameObjectByLua(std::string filename) {
		Engine::ObservingPointer < GameObject > newGameObject = GetNewGameObject();
		return newGameObject->LoadDataByLua(filename);
	}

	Engine::ObservingPointer<GameObject> GetNewGameObject() {
		Engine::OwningPointer<GameObject> emptyGameObject(new GameObject());
		GameobjectList.push(emptyGameObject);
		emptyGameObject->UpdateConnectionPointer(emptyGameObject);
		return emptyGameObject;
	}
	void Start();
	void Release();

private:
		
};


