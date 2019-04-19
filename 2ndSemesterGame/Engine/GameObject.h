#pragma once
#include "Vector3D.h"
#include "GLib.h"
#include "assert.h"
#include "Log.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "GameObject3DBasicAttr.h"
#include "Status.h"

#include "SmartPointer.h"
class GameManager;
class GameObject
{
public:
	Engine::ObservingPointer<GameObject> selfPointer;
	GameObject();
	~GameObject();
	GameObject(const GameObject &g) {
		this->equal(g);
	}
	void operator =(const GameObject &g) {
		this->equal(g);
	}

	//Interface
	virtual void Start() {}
	virtual void Update() {}

	void UpdateConnectionPointer(Engine::ObservingPointer<GameObject> g);

	bool HasPhysicsComponent();
	bool HasRenderComponent();

	void NewPhysicsComponent();
	void NewRenderComponent();

	Status AddPhysicsComponent(PhysicsComponent p);
	Status AddRenderComponent(RenderComponent r);

	Status UpdatePhysicsComponent(PhysicsComponent p);
	Status UpdateRenderComponent(RenderComponent r);

	Engine::ObservingPointer<PhysicsComponent> GetPhysicsComponent();
	Engine::ObservingPointer<RenderComponent> GetRenderComponent();
	/*template<typename T>
	T GetComponent();*/
		
	Engine::OwningPointer<GameObject3DBasicAttr> BasicAttr;

	Engine::OwningPointer<PhysicsComponent> physicsComponent;
	Engine::OwningPointer<RenderComponent> renderComponent;
	void Release();

private:
	
	void equal(const GameObject& g) {
		BasicAttr = g.BasicAttr;
		if (g.physicsComponent)
			physicsComponent = Engine::OwningPointer<PhysicsComponent>(*(g.physicsComponent));
		if (g.renderComponent)
			renderComponent = Engine::OwningPointer<RenderComponent>(*(g.renderComponent));

	}


	//Engine::OwningPointer<GameObject3DBasicAttr> attr;
	//
	//Engine::OwningPointer<PhysicsComponent> physics;
	//Engine::OwningPointer<RenderComponent> render;

	//
	//Vector3f DriveForceOnCurrentFrame = Vector3f(0, 0, 0);
	//
		
	//void UpdatePhysics(double i_dt, std::vector<Vector3f> addition_Forces = std::vector<Vector3f>());
};