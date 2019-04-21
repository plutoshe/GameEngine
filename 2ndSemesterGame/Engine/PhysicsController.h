#pragma once
#include "GameObject.h"
#include "PhysicsComponent.h"
#include <vector>
#include <queue> 

struct Collision {
public:
	int colliderID1, colliderID2;
	double time;
};

class PhysicsController {
public:
	PhysicsController() {
		
	}
	~PhysicsController() {

	}

	//void AddForce(GameObject& gameobject, Vector3f & i_Force, double i_dt)
	//{
	//	/*Vector3f acceleration = i_Force / gameobject.mass;
	//	gameobject.position = gameobject.position + gameobject.velocity * (float)i_dt + acceleration * (float)(i_dt * i_dt / 2);
	//	gameobject.velocity = gameobject.velocity + acceleration * (float)i_dt;*/

	//}
	

	std::vector<Engine::ObservingPointer<PhysicsComponent>> PhysicsComponentList;
	/*std::priority_queue <Collision> Collisions;*/
	void Update(double deltaTime);
private:

	double getCollisionTime(Engine::ObservingPointer<PhysicsComponent> a, Engine::ObservingPointer<PhysicsComponent> b);
};
