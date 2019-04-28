#include "PhysicsController.h"
#include "GeoMethod.h"

double PhysicsController::GetCollisionTime(Engine::ObservingPointer<PhysicsComponent> a, Engine::ObservingPointer<PhysicsComponent> b, double limitTime) {
	// Get Collision Time by Collision	
	if (a->ControlCollider->type == Box && b->ControlCollider->type == Box) {
		Engine::ObservingPointer<BoxCollider2D> colliderA = a->ControlCollider;
		Engine::ObservingPointer<BoxCollider2D> colliderB = b->ControlCollider;
	    Matrix4f matrixAtoB = b->ParentGameObject->WorldToLocalMatrix() * a->ParentGameObject->LocalToWorldMatrix();
		DataStructure::List<GeoPoint2D> ColliderAPoints = colliderA->GetBorderPoints();
		DataStructure::List<GeoLine2D> ColliderBLines = colliderB->GetBorderLines();
		double collisionTime = limitTime + 1;

		for (int i = 0; i < 4; i++) {
			Vector4f conversionVector4f = ColliderAPoints[i];
			conversionVector4f.w = 1;
			GeoPoint2D currentPoint =  matrixAtoB * conversionVector4f;
			// TODO: embed in acceleration
			conversionVector4f = a->velocity;
			conversionVector4f.w = 1;
			auto s1 = matrixAtoB * conversionVector4f + b->velocity;
			auto s = s1 * limitTime;
			GeoPoint2D nextPoint = currentPoint + (matrixAtoB * conversionVector4f + b->velocity) * limitTime;
			//+(a->acceleration * matrixAtoB + b->acceleration) * limitTime * limitTime / 2;
			GeoLine2D intersectLine = GeoLine2D(currentPoint, nextPoint);
			for (int j = 0; j < 4; j++) {
				GeoPoint2D crossover;
				if (GeoMethod::Line2DIntersect(intersectLine, ColliderBLines[j], crossover)) {
					DEBUG_LOG("~~~~~~~~~");
					GeoMethod::IsLine2DIntersect(intersectLine, ColliderBLines[j]);
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
	ColliderPhysicsA->UpdateTime = collisionTime;
	ColliderPhysicsA->UpdateTime = collisionTime;
}

void PhysicsController::Update(double deltaTime) {
	for (int i = 0; i < PhysicsComponentList.get_size(); i++) {
		PhysicsComponentList[i]->UpdateTime = 0;
	}
	while (true) {
		double minimumCollisionTime = deltaTime;
		int selectionObjectIDA = -1, selectionObjectIDB = -1;
		for (int i = 0; i < PhysicsComponentList.get_size(); i++) {
			for (int j = i + 1; j < PhysicsComponentList.get_size(); j++) {
				if (PhysicsComponentList[i] && PhysicsComponentList[j] &&
					PhysicsComponentList[i]->ControlCollider && PhysicsComponentList[j]->ControlCollider &&
					PhysicsComponentList[i] != PhysicsComponentList[j]) {
					double currentCollisionTime = GetCollisionTime(PhysicsComponentList[i], PhysicsComponentList[j], deltaTime);
					if (currentCollisionTime < minimumCollisionTime) {
						minimumCollisionTime = currentCollisionTime;
						selectionObjectIDA = i; selectionObjectIDB = j;
					}
				}
			}
		}
		if (selectionObjectIDA >= 0) {
			// Update A && B after collision
			CollisionImpact(PhysicsComponentList[selectionObjectIDA], PhysicsComponentList[selectionObjectIDB], minimumCollisionTime);
		}
		else break;
	}
	for (int i = 0; i < PhysicsComponentList.get_size(); i++) {
		PhysicsComponentList[i]->Update(deltaTime);
	}
}

void PhysicsController::AddPhysicsComponent(Engine::ObservingPointer<PhysicsComponent> p) {
	PhysicsComponentList.push(p);
}

void PhysicsController::RemovePhysicsComponent(Engine::ObservingPointer<PhysicsComponent> p) {
	for (int i = 0; i < PhysicsComponentList.get_size(); i++) {
		if (PhysicsComponentList[i] == p)
			PhysicsComponentList.remove(i);
	}
}

