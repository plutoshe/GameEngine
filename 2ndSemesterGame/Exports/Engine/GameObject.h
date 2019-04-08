#pragma once
#include "Vector3D.h"
#include "GLib.h"
#include "assert.h"
#include "Log.h"
#include "SmartPointer.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "GameObject3DBasicAttr.h"
#include "Status.h"
#include <vector>


class GameObject
{
public:

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

	bool HasPhysicsComponent();
	bool HasRenderComponent();

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
		physicsComponent = Engine::OwningPointer<PhysicsComponent>(*(g.physicsComponent));
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


