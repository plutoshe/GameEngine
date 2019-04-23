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
	// ignore density and area right now
	Vector3f airDrag = (velocity * velocity * DragCof) / 2;
	if (HasGravity)
		velocity += gravityAcceleration * (deltaTime - UpdateTime);
	velocity += acceleration * (deltaTime - UpdateTime);
	ParentGameObject->BasicAttr.Position += (deltaTime - UpdateTime) * velocity;
	UpdateTime = 0;
	acceleration -= airDrag / Mass;
	

}
//void AddForce(Vector3f & i_Force, double i_dt)
	//{
	//	/*Vector3f acceleration = i_Force / gameobject.mass;
	//	gameobject.position = gameobject.position + gameobject.velocity * (float)i_dt + acceleration * (float)(i_dt * i_dt / 2);
	//	gameobject.velocity = gameobject.velocity + acceleration * (float)i_dt;*/

	//}
