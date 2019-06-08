#include "GameObject.h"
#include "GameManager.h"

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

    physicsComponent = Engine::OwningPointer<PhysicsComponent>(new PhysicsComponent());
	physicsComponent->ParentGameObject = selfPointer;
    GameManager::Instance->Physics->AddPhysicsComponent(physicsComponent);
	/*ParentManager->Physics->AddRenderController(physicsComponent);*/
}

void GameObject::AddRenderComponent(RenderComponent *r) {
    renderComponent = Engine::OwningPointer<RenderComponent>(r);
	renderComponent->ParentGameObject = selfPointer;
    GameManager::Instance->Render->AddRenderController(renderComponent);
}

void GameObject::UpdatePhysicsComponent(PhysicsComponent *p) {
    physicsComponent = Engine::OwningPointer<PhysicsComponent>(p);
}
void GameObject::UpdateRenderComponent(RenderComponent *r) {
    renderComponent = Engine::OwningPointer<RenderComponent>(r);
}

Engine::ObservingPointer<PhysicsComponent> GameObject::GetPhysicsComponent() {
	return physicsComponent;
}

Engine::ObservingPointer<RenderComponent> GameObject::GetRenderComponent() {
	return renderComponent;
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
