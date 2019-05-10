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
			
		//	auto tb = matrixAtoB * a->ParentGameObject->BasicAttr.Position;
			auto ta = velocityMatrixAtoB * conversionVector4f;
			auto s1 = ta - b->velocity;
			
			auto s = s1 * limitTime;
		/*	DEBUG_LOG("conversion:");
			
			DEBUG_LOG("%.2f %.2f", ColliderAPoints[i].x, ColliderAPoints[i].y);
			DEBUG_LOG("%.2f %.2f", currentPoint.x, currentPoint.y);
			DEBUG_LOG("%.2f %.2f", nextPoint.x, nextPoint.y);
			DEBUG_LOG("velocity: %.2f %.2f", ta.x, ta.y);
			DEBUG_LOG("%.2f %.2f", s1.x, s1.y);
			DEBUG_LOG("%.2f %.2f", a->ParentGameObject->BasicAttr.Position.x, 
				a->ParentGameObject->BasicAttr.Position.y);
			DEBUG_LOG("%.2f %.2f", b->ParentGameObject->BasicAttr.Position.x, b->ParentGameObject->BasicAttr.Position.y);
			*/
			//+(a->acceleration * matrixAtoB + b->acceleration) * limitTime * limitTime / 2;
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
				/*		Vector4f aa = crossover;
						aa.w = 1;
						auto crossover1 = colliderB->ParentGameObject->ParentGameObject->LocalToWorldMatrix() * aa;
						DEBUG_LOG("crossover: %.3f %.3f", crossover1.x, crossover1.y);
						DEBUG_LOG("a velocity: %.3f %.3f", a->velocity.x, a->velocity.y);
						DEBUG_LOG("b velocity: %.3f %.3f", b->velocity.x, b->velocity.y);
						DEBUG_LOG("s1 velocity: %.3f %.3f", s1.x, s1.y);
						auto g1 = a->ParentGameObject->BasicAttr.Position;
						auto g2 = b->ParentGameObject->BasicAttr.Position;
						Vector3f aaa1 =  a ->ParentGameObject->BasicAttr.Position +
							a->velocity * intersectTime;

						Vector3f bbb1 = b->ParentGameObject->BasicAttr.Position +
							b->velocity * intersectTime;
						DEBUG_LOG("a pos: %.3f %.3f", aaa1.x, aaa1.y);
						DEBUG_LOG("b pos: %.3f %.3f", bbb1.x, bbb1.y);
						
						collisionTimes++;
						if (collisionTimes > 1) {
							int i = 1;
							GeoMethod::IsLine2DIntersect(intersectLine, ColliderBLines[j]);
						}*/
						//DEBUG_LOG("%.6f %.6f", intersectTime, intersectTime2);
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
	/*DEBUG_LOG(" before collisiion response position: %.2f, %.2f %.2f || %.2f %.2f %.2f",
		ColliderPhysicsA->ParentGameObject->BasicAttr.Position.x,
		ColliderPhysicsA->ParentGameObject->BasicAttr.Position.y,
		ColliderPhysicsA->ParentGameObject->BasicAttr.Position.z,
		ColliderPhysicsB->ParentGameObject->BasicAttr.Position.x,
		ColliderPhysicsB->ParentGameObject->BasicAttr.Position.y,
		ColliderPhysicsB->ParentGameObject->BasicAttr.Position.z);*/
	ColliderPhysicsA->ParentGameObject->BasicAttr.Position +=
		ColliderPhysicsA->velocity * collisionTime;
	ColliderPhysicsA->UpdateTime = collisionTime;
	ColliderPhysicsB->ParentGameObject->BasicAttr.Position +=
		ColliderPhysicsB->velocity * collisionTime;
	ColliderPhysicsB->UpdateTime = collisionTime;
	/*DEBUG_LOG(" after collisiion response position: %.2f, %.2f %.2f || %.2f %.2f %.2f",
		ColliderPhysicsA->ParentGameObject->BasicAttr.Position.x,
		ColliderPhysicsA->ParentGameObject->BasicAttr.Position.y,
		ColliderPhysicsA->ParentGameObject->BasicAttr.Position.z,
		ColliderPhysicsB->ParentGameObject->BasicAttr.Position.x,
		ColliderPhysicsB->ParentGameObject->BasicAttr.Position.y,
		ColliderPhysicsB->ParentGameObject->BasicAttr.Position.z);
	DEBUG_LOG("before collisiion response v: %.2f, %.2f %.2f || %.2f %.2f %.2f",
		ColliderPhysicsA->velocity.x, ColliderPhysicsA->velocity.y, ColliderPhysicsA->velocity.z,
		ColliderPhysicsB->velocity.x, ColliderPhysicsB->velocity.y, ColliderPhysicsB->velocity.z);
*/
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
	
	//DEBUG_LOG(" collisiion responseL %.2f, %.2f", ColliderPhysicsA->velocity.Length(), ColliderPhysicsB->velocity.Length());
	/*DEBUG_LOG(" collisiion response v: %.2f, %.2f %.2f || %.2f %.2f %.2f", 
		ColliderPhysicsA->velocity.x, ColliderPhysicsA->velocity.y, ColliderPhysicsA->velocity.z,
		ColliderPhysicsB->velocity.x, ColliderPhysicsB->velocity.y, ColliderPhysicsB->velocity.z);*/
	

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
					
					//DEBUG_LOG("%.2f", currentCollisionTime);
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
				if (!PhysicsComponentList[i]->IsStatic && i != selectionObjectIDA && i != selectionObjectIDB) {
					PhysicsComponentList[i]->ParentGameObject->BasicAttr.Position +=
						PhysicsComponentList[i]->velocity * minimumCollisionTime;
					PhysicsComponentList[i]->UpdateTime = minimumCollisionTime;
				}
			}
			//DEBUG_LOG("%.4f", minimumCollisionTime);
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

