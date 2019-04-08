#pragma once
#include "SmartPointer.h"
class GameObject;
class PhysicsComponent
{
public:
	PhysicsComponent();
	~PhysicsComponent();
		
	Engine::ObservingPointer<GameObject> ParentGameObject;

	float mass = 1;
	float dragCof = 1;
private:
		
};