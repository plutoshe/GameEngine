#include "PhysicsController.h"
#include "GeoMethod.h"

double PhysicsController::GetCollisionTime(Engine::ObservingPointer<PhysicsComponent> a, Engine::ObservingPointer<PhysicsComponent> b, double limitTime) {
	// Get Collision Time by Collision	
	if (a->ControlCollider->type == Box && b->ControlCollider->type == Box) {
		Engine::ObservingPointer<BoxCollider2D> colliderA = a->ControlCollider;
		Engine::ObservingPointer<BoxCollider2D> colliderB = b->ControlCollider;
	    Matrix4f matrixAtoB = b->ParentGameObject->WorldToLocalMatrix() * a->ParentGameObject->LocalToWorldMatrix();
		Matrix4f velocityMatrixAtoB = b->ParentGameObject->RotationMatrix().Inversion() * a->ParentGameObject->RotationMatrix();
		DataStructure::List<GeoPoint2D> ColliderAPoints = colliderA->GetBorderPoints();
		DataStructure::List<GeoPoint2D> ColliderBPoints = colliderB->GetBorderPoints();
		DataStructure::List<GeoLine2D> ColliderBLines = colliderB->GetBorderLines();
		double collisionTime = limitTime + 1;

		for (int i = 0; i < 4; i++) {
			Vector4f conversionVector4f = ColliderAPoints[i];
			conversionVector4f.w = 1;
			GeoPoint2D currentPoint =  matrixAtoB * conversionVector4f;
			// TODO: embed in acceleration
			conversionVector4f = a->velocity;
			conversionVector4f.w = 1;
			auto ta = matrixAtoB * conversionVector4f;
			auto s1 = ta + b->velocity;
			
			auto s = s1 * limitTime;
			GeoPoint2D nextPoint = currentPoint + (velocityMatrixAtoB * conversionVector4f + b->velocity) * limitTime;
			//+(a->acceleration * matrixAtoB + b->acceleration) * limitTime * limitTime / 2;
			GeoLine2D intersectLine = GeoLine2D(currentPoint, nextPoint);
			if (GeoMethod::IsPointInPoly(nextPoint, ColliderBPoints)) {
				for (int j = 0; j < 4; j++) {
					GeoPoint2D crossover;
					if (GeoMethod::IsLine2DIntersect(intersectLine, ColliderBLines[j])) {
						
						GeoMethod::Line2DIntersect(intersectLine, ColliderBLines[j], crossover);
						// TODO: embed in acceleration to calculate time
						double intersectTime = limitTime * (crossover.x - currentPoint.x) / (nextPoint.x - currentPoint.x);
						if (intersectTime < collisionTime)
							collisionTime = intersectTime;
					}
				}
			}
		}
		return collisionTime;
	}
	
}

void PhysicsController::CollisionImpact(Engine::ObservingPointer<PhysicsComponent> ColliderPhysicsA, Engine::ObservingPointer<PhysicsComponent> ColliderPhysicsB, double collisionTime) {
	// TODO: embed in acceleration to calculate impact
	auto oldVelocityA = ColliderPhysicsA->velocity;
	auto oldVelocityB = ColliderPhysicsB->velocity;
	//DEBUG_LOG("before collisiion responseL %.2f, %.2f", ColliderPhysicsA->velocity.Length(), ColliderPhysicsB->velocity.Length());
	auto massA = ColliderPhysicsA->Mass;
	auto massB = ColliderPhysicsA->Mass;
	if (!ColliderPhysicsA->IsStatic)
		ColliderPhysicsA->velocity =
			((massA - massB) * oldVelocityA + 2 * massB * oldVelocityB) /
			(massA + massB);
	if (!ColliderPhysicsB->IsStatic)
		ColliderPhysicsB->velocity =
			((massB - massA) * oldVelocityB + 2 * massA * oldVelocityA) /
			(massA + massB);
	
	DEBUG_LOG(" collisiion responseL %.2f, %.2f", ColliderPhysicsA->velocity.Length(), ColliderPhysicsB->velocity.Length());
	DEBUG_LOG(" collisiion response v: %.2f, %.2f %.2f || %.2f %.2f %.2f", 
		ColliderPhysicsA->velocity.x, ColliderPhysicsA->velocity.y, ColliderPhysicsA->velocity.z,
		ColliderPhysicsB->velocity.x, ColliderPhysicsB->velocity.y, ColliderPhysicsB->velocity.z);
	DEBUG_LOG(" collisiion response v: %.2f, %.2f %.2f || %.2f %.2f %.2f",
		ColliderPhysicsA->ParentGameObject->BasicAttr.Position.x, 
		ColliderPhysicsA->ParentGameObject->BasicAttr.Position.y,
		ColliderPhysicsA->ParentGameObject->BasicAttr.Position.z,
		ColliderPhysicsB->ParentGameObject->BasicAttr.Position.x, 
		ColliderPhysicsB->ParentGameObject->BasicAttr.Position.y, 
		ColliderPhysicsB->ParentGameObject->BasicAttr.Position.z);
}

void PhysicsController::Update(double deltaTime) {
	for (int i = 0; i < PhysicsComponentList.get_size(); i++) {
		PhysicsComponentList[i]->UpdateTime = 0;
		PhysicsComponentList[i]->Update(deltaTime);
	}
	
	int lastI = -1, lastJ = -1;
	while (true) {
		double minimumCollisionTime = deltaTime;
		int selectionObjectIDA = -1, selectionObjectIDB = -1;
		for (int i = 0; i < PhysicsComponentList.get_size(); i++) {
			for (int j = i + 1; j < PhysicsComponentList.get_size(); j++) {
				if (i == lastI && j == lastJ) continue;
				if (PhysicsComponentList[i] && PhysicsComponentList[j] &&
					PhysicsComponentList[i]->ControlCollider && PhysicsComponentList[j]->ControlCollider &&
					PhysicsComponentList[i] != PhysicsComponentList[j]) {
					double currentCollisionTime = GetCollisionTime(PhysicsComponentList[i], PhysicsComponentList[j], deltaTime);
					//DEBUG_LOG("%.2f", currentCollisionTime);
					if (currentCollisionTime < minimumCollisionTime) {
						minimumCollisionTime = currentCollisionTime;
						selectionObjectIDA = i; selectionObjectIDB = j;
					}
				}
			}
		}
		if (selectionObjectIDA >= 0) {
			for (int i = 0; i < PhysicsComponentList.get_size(); i++) {
				PhysicsComponentList[i]->ParentGameObject->BasicAttr.Position += 
					PhysicsComponentList[i]->velocity * minimumCollisionTime;
				PhysicsComponentList[i]->UpdateTime = minimumCollisionTime;
			}

			deltaTime -= minimumCollisionTime;
			// Update A && B after collision
			CollisionImpact(PhysicsComponentList[selectionObjectIDA], PhysicsComponentList[selectionObjectIDB], minimumCollisionTime);
			lastI = selectionObjectIDA, lastJ = selectionObjectIDB;
		}
		else break;
	}
	for (int i = 0; i < PhysicsComponentList.get_size(); i++) {
		PhysicsComponentList[i]->UpdatePos(deltaTime);
	}
}

void PhysicsController::AddPhysicsComponent(Engine::ObservingPointer<PhysicsComponent> p) {
	PhysicsComponentList.push(p);
}

void PhysicsController::RemovePhysicsComponent(Engine::ObservingPointer<PhysicsComponent> p) {
	for (int i = PhysicsComponentList.get_size() - 1; i >= 0; i--) 
		if (PhysicsComponentList[i] == p) {
			PhysicsComponentList.remove(i);
			break;
		}
}

