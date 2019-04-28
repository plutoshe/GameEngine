#include "GameObjectManager.h"



GameObjectManager::GameObjectManager()
{
}


GameObjectManager::~GameObjectManager()
{
}

void GameObjectManager::Start() {
	for (int i = 0; i < GameobjectList.size(); i++)
		GameobjectList[i]->Start();
}

void GameObjectManager::Update() {
	for (int i = 0; i < GameobjectList.size(); i++)
		GameobjectList[i]->Update(); 
}

void GameObjectManager::RemoveGameObject(Engine::ObservingPointer<GameObject> p) {
	for (int i = 0; i < GameobjectList.size(); i++)
		if (GameobjectList[i] == p) {
			GameobjectList.erase(GameobjectList.begin() + i);
			break;
		}
}

void GameObjectManager::Release() {

}
