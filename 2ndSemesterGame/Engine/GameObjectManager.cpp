#include "GameObjectManager.h"



GameObjectManager::GameObjectManager()
{
}


GameObjectManager::~GameObjectManager()
{
}


void GameObjectManager::Update() {
	for (int i = 0; i < GameobjectList.size(); i++)
		GameobjectList[i]->Update();
}

void GameObjectManager::Release() {
	for (int i = 0; i < GameobjectList.size(); i++)
		GameobjectList[i]->Release();
}
