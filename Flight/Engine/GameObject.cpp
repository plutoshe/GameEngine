#include "GameObject.h"
#include "GameManager.h"

extern GameManager CurrentGameManager;

GameObject::GameObject() {
	BasicAttr.Clear();
}
GameObject::~GameObject() {}

bool GameObject::HasPhysicsComponent() {
	return physicsComponent != nullptr;
}

bool GameObject::HasRenderComponent() {
	return renderComponent != nullptr;
}

void GameObject::NewPhysicsComponent() {
	// TODO: Finish the new function of Physics system

	physicsComponent = Engine::OwningPointer<PhysicsComponent>(PhysicsComponent());
	physicsComponent->ParentGameObject = selfPointer;
	CurrentGameManager.Physics->AddPhysicsComponent(physicsComponent);
	/*ParentManager->Physics->AddRenderController(physicsComponent);*/
}

void GameObject::NewRenderComponent() {
	if (HasRenderComponent())
		return;
	renderComponent = Engine::OwningPointer<RenderComponent>(RenderComponent());
	renderComponent->ParentGameObject = selfPointer;
	CurrentGameManager.Render->AddRenderController(renderComponent);
}

//Status GameObject::AddPhysicsComponent(PhysicsComponent p) {
//	if (HasPhysicsComponent())
//		return Status(400, "Already has a component");
//	physicsComponent = Engine::OwningPointer<PhysicsComponent>(&p);
//	return NoError;
//}
//
//Status GameObject::AddRenderComponent(RenderComponent r) {
//	if (HasRenderComponent())
//		return Status(400, "Already has a component");
//	renderComponent = Engine::OwningPointer<RenderComponent>(&r);
//	return NoError;
//}

Status GameObject::UpdatePhysicsComponent(PhysicsComponent p) {
	if (physicsComponent == nullptr)
		return NullPointerError;
	*physicsComponent = p;
	return NoError;
}
Status GameObject::UpdateRenderComponent(RenderComponent r) {
	if (renderComponent == nullptr)
		return NullPointerError;
	*renderComponent = r;
	return NoError;
}

Engine::ObservingPointer<PhysicsComponent> GameObject::GetPhysicsComponent() {
	return physicsComponent;
}

Engine::ObservingPointer<RenderComponent> GameObject::GetRenderComponent() {
	return renderComponent;
}

void GameObject::Release() {
	/*if (physicsComponent != nullptr)
		physicsComponent->Release();*/
	if (renderComponent != nullptr)
		renderComponent->Release();
}

void GameObject::UpdateConnectionPointer(Engine::ObservingPointer<GameObject> g) {
	selfPointer = g;
	if (renderComponent)
		renderComponent->ParentGameObject = g;
	if (physicsComponent)
		physicsComponent->ParentGameObject = g;
}

void GameObject::AddForce(Vector3f force) {
	if (physicsComponent)
		physicsComponent->AddForce(force);
}
