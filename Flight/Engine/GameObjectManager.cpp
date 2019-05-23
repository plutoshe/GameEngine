#include "GameObjectManager.h"



GameObjectManager::GameObjectManager()
{
}


GameObjectManager::~GameObjectManager()
{
}

void GameObjectManager::Start() {
	for (int i = 0; i < GameobjectList.get_size(); i++)
		GameobjectList[i]->Start();
}

void GameObjectManager::Update() {
	for (int i = 0; i < GameobjectList.get_size(); i++)
		if (GameobjectList[i]->Active && !GameobjectList[i]->willDelete)
			GameobjectList[i]->Update(); 
	for (int i = GameobjectList.get_size() - 1; i >= 0; i--)
		if (GameobjectList[i]->willDelete)
			GameobjectList.remove(i);
}

void GameObjectManager::RemoveGameObject(Engine::ObservingPointer<GameObject> p) {
	for (int i = 0; i < GameobjectList.get_size(); i++)
		if (GameobjectList[i] == p) {
			//GameobjectList.erase(GameobjectList.begin() + i);
			GameobjectList[i]->willDelete = true;
			break;
		}
}

void GameObjectManager::Release() {

}
