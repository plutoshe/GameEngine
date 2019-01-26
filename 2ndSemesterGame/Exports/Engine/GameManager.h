#pragma once
#include <vector>
#include "GameObject.h"
#include <conio.h>
#include <functional> 
#include "Vectors.h"
class GameManager
{
public:
	GameManager();
	~GameManager();
	Vectors<GameObject*> gameobjects;
	bool Initialization(HINSTANCE i_hInstance, int i_nCmdShow, const char * i_pWindowName, WORD i_IconID, unsigned int i_WindowWidth, unsigned int i_WindowHeight);
	void Run();
	void Rendering();
	void InputGet();
	void PhysicsUpdate(double deltaTime);
	void AddGameObejct(GameObject *gameobject);
	void CheckInput(unsigned int i_VKeyID, bool bWentDown);
	void Release();
	void UpdateKey(unsigned int i_VKeyID);
	bool bQuit = false;
	
};

