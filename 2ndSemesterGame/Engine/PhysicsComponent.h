#pragma once
#include "SmartPointer.h"
#include "Collider2D.h"
class GameObject;
class PhysicsComponent
{
public:
	PhysicsComponent();
	~PhysicsComponent();
		
	Engine::ObservingPointer<GameObject> ParentGameObject;

	float mass = 1;
	float dragCof = 1;
	double CurrentActionTime;
	Engine::OwningPointer<Collider> ControlCollider;

	void Update(double deltaTime);
private:
		
};