#pragma once
#include "SmartPointer.h"
#include "Collider2D.h"
#include "SSERedef.h"

class GameObject;

class Force {
public:
	Vector3f Magnitute;
	float ExertingTime;
	Force(Vector3f _magnitute, float _exertingTime) : Magnitute(_magnitute), ExertingTime(_exertingTime) {}
	Force() {}
};

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
	float DragCof = 0.01;
	Vector3f velocity = Vector3f(0,0,0);
	Vector3f acceleration = Vector3f(0, 0, 0);
	bool HasGravity = false;
	bool IsStatic = false;
	// TODO: AngleVelocity
	// Vector3f angleVelocity
	const Vector3f gravityAcceleration = Vector3f(0, -9.8f, 0);
	Vector3f ContinuousForces = Vector3f(0, 0, 0);
	Vector3f CurrentForce = Vector3f(0, 0, 0);
	double UpdateTime = 0;
	Engine::OwningPointer<Collider> ControlCollider = nullptr;

	void Update(double deltaTime);
	void UpdatePos(double deltaTime);
	template<class T>
	void AddCollider(T _collider) {
		ControlCollider = Engine::OwningPointer<T>(_collider);
		UpdatePointer();
	}

	void NewCollider(ColliderType type);
	void UpdatePointer();
	void AddForce(Vector3f i_Force);
	

	DataStructure::List<Force> ExextForces;
private:
	void checkExertingForces(float deltaTime);
};