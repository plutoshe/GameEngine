#pragma once
#include "SSERedef.h"
#include "assert.h"
#include "SSERedef.h"
#include "GameObjectBasicAttr.h"
#include "Status.h"
#include "RenderComponent.h"
#include "PhysicsComponent.h"

class GameManager;
class GameObject
{
public:
    //Engine::ObservingPointer<GameManager> belongedGameManager;
    Matrix4f LocalToWorldMatrix() {
		Matrix4f a = Matrix4f::GetTranslationMatrix(Vector4f(BasicAttr.Position)) * Matrix4f::GetRotationMatrix(BasicAttr.Rotation);
		return a;
	}

	Matrix4f RotationMatrix() {
		return Matrix4f::GetRotationMatrix(BasicAttr.Rotation);
	}

	Matrix4f WorldToLocalMatrix() {
		return Matrix4f::GetRotationMatrix(BasicAttr.Rotation).Inversion() * Matrix4f::GetTranslationMatrix(BasicAttr.Position).Inversion();
	}
	Engine::ObservingPointer<GameObject> parentGameObject;
	Engine::ObservingPointer<GameObject> selfPointer;
	GameObject();
    virtual ~GameObject();
	GameObject(const GameObject &g) {
		this->equal(g);
	}
	void operator =(const GameObject &g) {
		this->equal(g);
	}

	//Interface
	virtual void Start() {}
	virtual void Update() {}

	virtual void OnCollisionEnter(Engine::ObservingPointer<GameObject> other) {}

	void UpdateConnectionPointer(Engine::ObservingPointer<GameObject> g);

	bool HasPhysicsComponent();
	bool HasRenderComponent();

	void NewPhysicsComponent();
    void AddRenderComponent(RenderComponent *r);

    void UpdatePhysicsComponent(PhysicsComponent *p);
    void UpdateRenderComponent(RenderComponent *r);

	Engine::ObservingPointer<PhysicsComponent> GetPhysicsComponent();
	Engine::ObservingPointer<RenderComponent> GetRenderComponent();
	/*template<typename T>
	T GetComponent();*/
		
	GameObjectBasicAttr BasicAttr;

	Engine::OwningPointer<PhysicsComponent> physicsComponent;
	Engine::OwningPointer<RenderComponent> renderComponent;
	bool Active = true;
	bool willDelete = false;

	// TODO: Add collider
	// 2D_Collider: 5 Type
	// Box, Circle, Capsule, Edge, Polygon
	// 3D Collider: 3 Type
	// Cube, Sphere, Capsule


	void AddForce(Vector3f force);

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
};
