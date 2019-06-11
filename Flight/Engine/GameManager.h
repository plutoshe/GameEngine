#pragma once
#include <vector>
#include "GameObject.h"
#include <functional> 
#include "List.h"
#include "InputController.h"
#include "PhysicsController.h"
#include "GameObjectManager.h"
#include "RenderController.h"
#include "SmartPointer.h"
#include "Timing.h"

class GameManager
{
public:
    static Engine::OwningPointer<GameManager> Instance;
    GameManager();
	~GameManager();
	//Model
	Engine::OwningPointer<GameObjectManager> PSGameObjectManager;
	//Controller
	Engine::OwningPointer<PhysicsController> Physics;
    Engine::OwningPointer<InputController> Input;

	Engine::OwningPointer<RenderController> Render;
	int frameID;
	double DeltaTime;
	bool bQuit;

    bool Initialization();
	virtual bool Once();
	void Run();

	Engine::ObservingPointer<GameObject> GetNewGameObject();

	template<class T>
    Engine::ObservingPointer<GameObject> AddGameObject(Engine::OwningPointer<T> gameobject) {
		return PSGameObjectManager->AddGameObject(gameobject);
	}
    void AddRenderController(RenderController *r) {
        Render = Engine::OwningPointer<RenderController>(r);
    }

	void RemoveGameObject(Engine::ObservingPointer<GameObject> p) {
		Render->RemoveRenderComponent(p->renderComponent);
		Physics->RemovePhysicsComponent(p->physicsComponent);
		PSGameObjectManager->RemoveGameObject(p);
	}
	void Release();
};

