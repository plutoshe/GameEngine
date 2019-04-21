#include "PhysicsController.h"

double PhysicsController::getCollisionTime(Engine::ObservingPointer<PhysicsComponent> a, Engine::ObservingPointer<PhysicsComponent> b) {
	// Get Collision Time by Collision

	return 0;
}

void PhysicsController::Update(double deltaTime) {
	for (int i = 0; i < PhysicsComponentList.size(); i++) {
		PhysicsComponentList[i]->CurrentActionTime = 0;
	}
	while (true) {
		double minimumCollisionTime = deltaTime;
		int selectionObjectIDA = -1, selectionObjectIDB = -1;
		for (int i = 0; i < PhysicsComponentList.size(); i++) {
			for (int j = i + 1; j < PhysicsComponentList.size(); j++) {
				double currentCollisionTime = getCollisionTime(PhysicsComponentList[i], PhysicsComponentList[j]);
				if (currentCollisionTime < minimumCollisionTime) {
					minimumCollisionTime = currentCollisionTime;
					selectionObjectIDA = i; selectionObjectIDB = j;
				}
			}
		}
		if (selectionObjectIDA >= 0) {
			// Update A && B after collision

		}
		else break;
	}
	for (int i = 0; i < PhysicsComponentList.size(); i++) {
		PhysicsComponentList[i]->Update(deltaTime);
	}
}

