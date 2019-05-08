#include <iostream>

#include "PhysicsComponent.h"
#include "GameObject.h"

PhysicsComponent::PhysicsComponent()
{
}


PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::Update(double deltaTime) {
	if (IsStatic) return;
	Force = ExertingForce;
	// ignore density and area right now
	Vector3f airDrag = (velocity * velocity * DragCof) / 2;
	if (velocity.x > 0)
		airDrag.x *= -1;
	if (velocity.y > 0)
		airDrag.y *= -1;
	if (velocity.z > 0)
		airDrag.z *= -1;
	Force += airDrag;

	if (HasGravity) {
		velocity += gravityAcceleration * (deltaTime - UpdateTime);
		Force += gravityAcceleration * Mass;
	}
	velocity += acceleration * (deltaTime - UpdateTime);
	std::cout << velocity;
	ParentGameObject->BasicAttr.Position += (deltaTime - UpdateTime) * velocity;
	UpdateTime = 0;
	acceleration = Force / Mass;
	Force.Clear();
	checkExertingForces();
}

void PhysicsComponent::checkExertingForces(float deltaTime) {
	for (int i = ExertingForces.size() - 1; i >= 0; i--) {
		ExertingForces[i].ExertingTime -= deltaTime;
		if (ExertingForces[i].ExertingTime < 0) 
			ExertingForces.remove(i);
	}	
}

void PhysicsComponent::UpdatePointer() {
	ControlCollider->ParentGameObject = ParentGameObject->physicsComponent;
}
void PhysicsComponent::NewCollider(ColliderType type) {
	switch (type)
	{
	case Box:
		ControlCollider = Engine::OwningPointer<BoxCollider2D>();
		break;
	default:
		break;
	}
}

void PhysicsComponent::AddForce(Vector3f i_Force)
{
	//Force = i_Force;
	ExextForces.push(Force(i_Force, 0.1f));
	ExertingForces += i_Force;
	/*Vector3f acceleration = i_Force / gameobject.mass;
	gameobject.position = gameobject.position + gameobject.velocity * (float)i_dt + acceleration * (float)(i_dt * i_dt / 2);
	gameobject.velocity = gameobject.velocity + acceleration * (float)i_dt;*/

}
