#include "RenderComponent.h"
#include "GameObject.h"

RenderComponent::RenderComponent()
{
}


RenderComponent::~RenderComponent()
{
	GLib::Sprites::Release(Irender.OriginalPointer());
}

void RenderComponent::Render() {
	// Tell GLib to render this sprite at our calculated location
	
	auto pos = GLib::Point2D{ ParentGameObject->BasicAttr->Position.x, ParentGameObject->BasicAttr->Position.y };
	GLib::Sprites::RenderSprite(*Irender, pos, 0.0f);
}
void RenderComponent::Release() {
	GLib::Sprites::Release(Irender.OriginalPointer());
}