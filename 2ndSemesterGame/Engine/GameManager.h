#pragma once
#include <vector>
#include "GameObject.h"
#include <conio.h>
#include <functional> 
#include "List.h"
#include "GLib.h"
#include "InputController.h"
#include "PhysicsController.h"
#include "GameObjectManager.h"
#include "RenderController.h"
#include "SmartPointer.h"

class GameManager
{
public:
	GameManager();
	~GameManager();
	//Model
	Engine::OwningPointer<GameObjectManager> PSGameObejctManager;

	//Controller
	Engine::OwningPointer<PhysicsController> Physics;
	Engine::OwningPointer<InputController> Input;
	Engine::OwningPointer<RenderController> Render;
	double DeltaTime;
	bool bQuit;

	bool Initialization(HINSTANCE i_hInstance, int i_nCmdShow, const char * i_pWindowName, WORD i_IconID, unsigned int i_WindowWidth, unsigned int i_WindowHeight);

	void Run();

	Engine::ObservingPointer<GameObject> GetNewGameObject();

	template<class T>
	Engine::ObservingPointer<GameObject> AddGameObject(T gameobject) {
		return PSGameObejctManager->AddGameObject(gameobject);
	}
	
	void Release();

	//void CheckInput(unsigned int i_VKeyID);
	//void Rendering();
	//void InputGet();
	//void PhysicsUpdate(double deltaTime);
	//void AddGameObject(GameObject *gameobject);
	//void CheckInput(unsigned int i_VKeyID, bool bWentDown);
	//void UpdateKey(unsigned int i_VKeyID);
	//bool bQuit = false;

};

