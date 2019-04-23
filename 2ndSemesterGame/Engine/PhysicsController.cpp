#include "PhysicsController.h"
#include "GeoMethod.h"

double PhysicsController::GetCollisionTime(Engine::ObservingPointer<PhysicsComponent> a, Engine::ObservingPointer<PhysicsComponent> b, double limitTime) {
	// Get Collision Time by Collision
	if (a->ControlCollider->type == Box && b->ControlCollider->type == Box) {
		Engine::ObservingPointer<BoxCollider2D> colliderA = a->ControlCollider;
		Engine::ObservingPointer<BoxCollider2D> colliderB = b->ControlCollider;
	    Matrix4f matrixAtoB = a->ParentGameObject->LocalToWorldMatrix() * b->ParentGameObject->WorldToLocalMatrix();
		DataStructure::List<GeoPoint2D> ColliderAPoints = colliderA->GetBorderPoints();
		DataStructure::List<GeoLine2D> ColliderBLines = colliderB->GetBorderLines();
		double collisionTime = limitTime + 1;

		for (int i = 0; i < 4; i++) {
			GeoPoint2D currentPoint = ColliderAPoints[i] * matrixAtoB;
			// TODO: embed in acceleration
			GeoPoint2D nextPoint = currentPoint + (a->velocity * matrixAtoB + b->velocity) * limitTime;
			//+(a->acceleration * matrixAtoB + b->acceleration) * limitTime * limitTime / 2;
			GeoLine2D intersectLine = GeoLine2D(currentPoint, nextPoint);
			for (int j = 0; j < 4; j++) {
				Vector3f crossover;
				if (GeoMethod::IsLine2DIntersect(intersectLine, ColliderBLines[j])) {
					// TODO: embed in acceleration to calculate time
					double intersectTime = limitTime * (crossover.x - currentPoint.x) / (nextPoint.x - currentPoint.x);
					if (intersectTime < collisionTime)
						collisionTime = intersectTime;
				}
			}
		}
		return collisionTime;
	}
	
}

void PhysicsController::CollisionImpact(Engine::ObservingPointer<PhysicsComponent> ColliderPhysicsA, Engine::ObservingPointer<PhysicsComponent> ColliderPhysicsB, double collisionTime) {
	// TODO: embed in acceleration to calculate impact
	ColliderPhysicsA->ParentGameObject->BasicAttr.Position += ColliderPhysicsA->velocity * collisionTime;
	ColliderPhysicsB->ParentGameObject->BasicAttr.Position += ColliderPhysicsB->velocity * collisionTime;
	auto oldVelocityA = ColliderPhysicsA->velocity;
	auto oldVelocityB = ColliderPhysicsB->velocity;
	auto massA = ColliderPhysicsA->Mass;
	auto massB = ColliderPhysicsA->Mass;
	ColliderPhysicsA->velocity =
		((massA - massB) * oldVelocityA + 2 * massB * oldVelocityB) /
		(massA + massB);
	ColliderPhysicsB->velocity =
		((massB - massA) * oldVelocityB + 2 * massA * oldVelocityA) /
		(massA + massB);
}

void PhysicsController::Update(double deltaTime) {
	for (int i = 0; i < PhysicsComponentList.size(); i++) {
		PhysicsComponentList[i]->UpdateTime = 0;
	}
	while (true) {
		double minimumCollisionTime = deltaTime;
		int selectionObjectIDA = -1, selectionObjectIDB = -1;
		for (int i = 0; i < PhysicsComponentList.size(); i++) {
			for (int j = i + 1; j < PhysicsComponentList.size(); j++) {
				double currentCollisionTime = GetCollisionTime(PhysicsComponentList[i], PhysicsComponentList[j], deltaTime);
				if (currentCollisionTime < minimumCollisionTime) {
					minimumCollisionTime = currentCollisionTime;
					selectionObjectIDA = i; selectionObjectIDB = j;
				}
			}
		}
		if (selectionObjectIDA >= 0) {
			// Update A && B after collision
			CollisionImpact(PhysicsComponentList[selectionObjectIDA], PhysicsComponentList[selectionObjectIDB], minimumCollisionTime);
		}
		else break;
	}
	for (int i = 0; i < PhysicsComponentList.size(); i++) {
		PhysicsComponentList[i]->Update(deltaTime);
	}
}

