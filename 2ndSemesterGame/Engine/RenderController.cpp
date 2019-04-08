#include "RenderController.h"


RenderController::RenderController()
{
}


RenderController::~RenderController()
{
}

void RenderController::Rendering() {
	GLib::BeginRendering();
		
	GLib::Sprites::BeginRendering();
	GLib::BeginRendering();
		// Tell GLib that we want to render some sprites
	GLib::Sprites::BeginRendering();
	for (int id = 0; id < ListRenderComponent.size(); id++)
		ListRenderComponent[id]->Render();

		// Tell GLib we're done rendering sprites
	GLib::Sprites::EndRendering();
	// IMPORTANT: Tell GLib we're done rendering
	GLib::EndRendering();

		

}

void RenderController::Update() {

}
