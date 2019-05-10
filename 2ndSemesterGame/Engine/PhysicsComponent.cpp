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
	CurrentForce = ContinuousForces;
	// ignore density and area right now
	Vector3f airDrag = (velocity * velocity * DragCof) / 2;
	/*DEBUG_LOG("velocity: %.2f %.2f %.2f", velocity.x, velocity.y, velocity.z);
	DEBUG_LOG("ariDrag: %.2f", airDrag.Length());*/
	if (velocity.x > 0)
		airDrag.x *= -1;
	if (velocity.y > 0)
		airDrag.y *= -1;
	if (velocity.z > 0)
		airDrag.z *= -1;
	CurrentForce += airDrag;

	if (HasGravity) {
		//velocity += gravityAcceleration * deltaTime;
		CurrentForce += gravityAcceleration * PixelRatio * Mass;
	}
	if (!IsStatic) {
		acceleration = CurrentForce / Mass;
		Vector3f oldVelocity = velocity;
		velocity += acceleration * deltaTime;
		if (oldVelocity.x * velocity.x < 0)
			velocity.x = 0;
		if (oldVelocity.y * velocity.y < 0)
			velocity.x = 0;
		if (oldVelocity.z * velocity.z < 0)
			velocity.x = 0;
		DEBUG_LOG("%.3f %.3f %.3f || %.3f %.3f %.3f", 
			acceleration.x, 
			acceleration.y,
			acceleration.z,
			velocity.x,
			velocity.y,
			velocity.z);
	}
	
	checkExertingForces(deltaTime);
}

void PhysicsComponent::UpdatePos(double deltaTime) {
	//DEBUG_LOG("%.2f %.2f %.2f", velocity.Length(), acceleration.Length(), ContinuousForces.Length());
	if (!IsStatic) {
		ParentGameObject->BasicAttr.Position += (deltaTime - UpdateTime) * velocity;
		/*DEBUG_LOG("%.2f", UpdateTime);
		DEBUG_LOG("===%.3f %.3f %.3f || %.3f %.3f %.3f",
			ParentGameObject->BasicAttr.Position.x,
			ParentGameObject->BasicAttr.Position.y,
			ParentGameObject->BasicAttr.Position.z,
			velocity.x,
			velocity.y,
			velocity.z);*/
	}
	UpdateTime = 0;
}

void PhysicsComponent::checkExertingForces(float deltaTime) {
	for (int i = ExextForces.get_size() - 1; i >= 0; i--) {
		ExextForces[i].ExertingTime -= deltaTime;
		if (ExextForces[i].ExertingTime < 0) {
			ContinuousForces -= ExextForces[i].Magnitute;
			ExextForces.remove(i);
		}
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
	ContinuousForces += i_Force;
	/*Vector3f acceleration = i_Force / gameobject.mass;
	gameobject.position = gameobject.position + gameobject.velocity * (float)i_dt + acceleration * (float)(i_dt * i_dt / 2);
	gameobject.velocity = gameobject.velocity + acceleration * (float)i_dt;*/

}
