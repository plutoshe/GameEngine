#include "PhysicsController.h"
#include "GeoMethod.h"
int collisionTimes = 0;
double PhysicsController::GetCollisionTime(Engine::ObservingPointer<PhysicsComponent> a, Engine::ObservingPointer<PhysicsComponent> b, double limitTime) {
	// Get Collision Time by Collision	
	if (a->ControlCollider->type == Box && b->ControlCollider->type == Box) {
		Engine::ObservingPointer<BoxCollider2D> colliderA = a->ControlCollider;
		Engine::ObservingPointer<BoxCollider2D> colliderB = b->ControlCollider;
	    Matrix4f matrixAtoB =  
			b->ParentGameObject->WorldToLocalMatrix() * a->ParentGameObject->LocalToWorldMatrix();
		Matrix4f velocityMatrixAtoB = b->ParentGameObject->RotationMatrix().Inversion() * a->ParentGameObject->RotationMatrix();
		DataStructure::List<GeoPoint2D> ColliderAPoints = colliderA->GetBorderPoints();
		DataStructure::List<GeoPoint2D> ColliderBPoints = colliderB->GetBorderPoints();
		DataStructure::List<GeoLine2D> ColliderBLines = colliderB->GetBorderLines();
		double collisionTime = limitTime + 1;

		for (int i = 0; i < 4; i++) {
			// TODO: embed in acceleration
			Vector4f conversionVector4f = ColliderAPoints[i];
			conversionVector4f.w = 1;
			GeoPoint2D currentPoint = matrixAtoB * 
				conversionVector4f;

			conversionVector4f = a->velocity;
			conversionVector4f.w = 1;
			GeoPoint2D nextPoint = currentPoint +
				(velocityMatrixAtoB * conversionVector4f - b->velocity) * limitTime;
		
			GeoLine2D intersectLine = GeoLine2D(currentPoint, nextPoint);
			if (GeoMethod::IsPointInPoly(nextPoint, ColliderBPoints)) {
				for (int j = 0; j < 4; j++) {
					GeoPoint2D crossover;
					if (GeoMethod::IsLine2DIntersect(intersectLine, ColliderBLines[j])) {
						
						GeoMethod::Line2DIntersect(intersectLine, ColliderBLines[j], crossover);
						// TODO: embed in acceleration to calculate time
						double intersectTime;
						double intersectTime2;
						if (nextPoint.x - currentPoint.x != 0) 
							intersectTime = limitTime * 
								(crossover.x - currentPoint.x) / (nextPoint.x - currentPoint.x);
						else 
							intersectTime = limitTime *
								(crossover.y - currentPoint.y) / (nextPoint.y - currentPoint.y);
				
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
}

void PhysicsController::Update(double deltaTime) {
	for (int i = 0; i < PhysicsComponentList.get_size(); i++) {
		PhysicsComponentList[i]->UpdateTime = 0;
		if (PhysicsComponentList[i]->ParentGameObject->Active)
			PhysicsComponentList[i]->Update(deltaTime);
	}
	
	int lastI = -1, lastJ = -1;
	while (true) {
		double minimumCollisionTime = deltaTime;
		int selectionObjectIDA = -1, selectionObjectIDB = -1;
		for (int i = 0; i < PhysicsComponentList.get_size(); i++) {
			if (!PhysicsComponentList[i]->ParentGameObject->Active) continue;
			for (int j = i + 1; j < PhysicsComponentList.get_size(); j++) {
				if (!PhysicsComponentList[j]->ParentGameObject->Active) continue;
				if (i == lastI && j == lastJ) continue;
				if (PhysicsComponentList[i]->IsStatic && PhysicsComponentList[j]->IsStatic)
					continue;
				if (PhysicsComponentList[i] && PhysicsComponentList[j] &&
					PhysicsComponentList[i]->ControlCollider && PhysicsComponentList[j]->ControlCollider &&
					PhysicsComponentList[i] != PhysicsComponentList[j]) {
					double currentCollisionTime = GetCollisionTime(PhysicsComponentList[i], PhysicsComponentList[j], deltaTime);
					
					if (currentCollisionTime < minimumCollisionTime) {
						minimumCollisionTime = currentCollisionTime;
						selectionObjectIDA = i; selectionObjectIDB = j;
					}
					else {
						currentCollisionTime = GetCollisionTime(PhysicsComponentList[j], PhysicsComponentList[i], deltaTime);
						if (currentCollisionTime < minimumCollisionTime) {
							minimumCollisionTime = currentCollisionTime;
							selectionObjectIDA = i; selectionObjectIDB = j;
						}
					}
				}
			}
		}
		if (selectionObjectIDA >= 0) {
			for (int i = 0; i < PhysicsComponentList.get_size(); i++) {
				if (!PhysicsComponentList[i]->ParentGameObject->Active) continue;
				if (!PhysicsComponentList[i]->IsStatic) {
					PhysicsComponentList[i]->ParentGameObject->BasicAttr.Position +=
						PhysicsComponentList[i]->velocity * minimumCollisionTime;
					PhysicsComponentList[i]->UpdateTime = minimumCollisionTime;
				}
			}
			deltaTime -= minimumCollisionTime;
			// Update A && B after collision
			CollisionImpact(PhysicsComponentList[selectionObjectIDA], PhysicsComponentList[selectionObjectIDB], minimumCollisionTime);
			PhysicsComponentList[selectionObjectIDA]->ParentGameObject->OnCollisionEnter(PhysicsComponentList[selectionObjectIDB]->ParentGameObject);
			auto c = PhysicsComponentList[selectionObjectIDB];
			auto a = c->ParentGameObject;
			//PhysicsComponentList[selectionObjectIDB]->ParentGameObject
			a->OnCollisionEnter(
				PhysicsComponentList[selectionObjectIDA]->ParentGameObject);
			lastI = selectionObjectIDA, lastJ = selectionObjectIDB;
		}
		else break;
	}
	for (int i = 0; i < PhysicsComponentList.get_size(); i++) {
		if (!PhysicsComponentList[i]->ParentGameObject->Active) continue;
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

