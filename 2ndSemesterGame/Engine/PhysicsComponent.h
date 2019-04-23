#pragma once
#include "SmartPointer.h"
#include "Collider2D.h"
#include "VectorUtil.h"

class GameObject;
class PhysicsComponent
{
public:
	PhysicsComponent();
	~PhysicsComponent();
	PhysicsComponent(const PhysicsComponent& p) {
		this->Equal(p);
	}

	void operator=(const PhysicsComponent &p) {
		this->Equal(p);
	}
	void Equal(const PhysicsComponent &p) {
		Mass = p.Mass;
		DragCof = p.DragCof;
		acceleration = p.acceleration;
		velocity = p.velocity;
		HasGravity = p.HasGravity;
		IsStatic = p.IsStatic;
	}
		
	Engine::ObservingPointer<GameObject> ParentGameObject;

	float Mass = 1;
	float DragCof = 1;
	Vector3f velocity;
	Vector3f acceleration;
	bool HasGravity;
	bool IsStatic;
	// TODO: AngleVelocity
	// Vector3f angleVelocity
	const Vector3f gravityAcceleration = Vector3f(0, -9.8, 0);
	
	double UpdateTime;
	Engine::OwningPointer<Collider> ControlCollider;
	//void AddCollider(Collider _collider);
	//void NewCollider(ColliderType type);
	void Update(double deltaTime);
	//void AddForce(Vector3f& i_Force);
private:
		
};