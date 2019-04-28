#pragma once
#include "VectorUtil.h"
#include "GLib.h"
#include "assert.h"
#include "Log.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "GameObjectBasicAttr.h"
#include "Status.h"
#include "Matrix4x4.h"
#include "SmartPointer.h"
class GameManager;
class GameObject
{
public:
	Matrix4f LocalToWorldMatrix() {
		//Matrix4f::GetTranslationMatrix(BasicAttr.Position)
		Matrix4f a = Matrix4f::GetTranslationMatrix(Vector4f(BasicAttr.Position)) * Matrix4f::GetRotationMatrix(BasicAttr.Rotation);
		return a;
	}

	Matrix4f RotationMatrix() {
		return Matrix4f::GetRotationMatrix(BasicAttr.Rotation);
	}

	Matrix4f WorldToLocalMatrix() {
		return Matrix4f::GetRotationMatrix(BasicAttr.Rotation).Inversion() * Matrix4f::GetTranslationMatrix(BasicAttr.Position).Inversion() ;
	}

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

	/*Status AddPhysicsComponent(PhysicsComponent p);
	Status AddRenderComponent(RenderComponent r);
*/
	Status UpdatePhysicsComponent(PhysicsComponent p);
	Status UpdateRenderComponent(RenderComponent r);

	Engine::ObservingPointer<PhysicsComponent> GetPhysicsComponent();
	Engine::ObservingPointer<RenderComponent> GetRenderComponent();
	/*template<typename T>
	T GetComponent();*/
		
	GameObjectBasicAttr BasicAttr;

	Engine::OwningPointer<PhysicsComponent> physicsComponent;
	Engine::OwningPointer<RenderComponent> renderComponent;
	void Release();

	// 2D_Collider: 5 Type
	// Box, Circle, Capsule, Edge, Polygon

	void NewBoxCollider2D() {

	}


	// TODO: 3D Collider
	// Sphere Collider, Cube Collider, Capsule Collider

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