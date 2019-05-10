#include "RenderController.h"
#include "GameObject.h"

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

	GLib::BeginRendering();
	// Tell GLib that we want to render some sprites
	GLib::Sprites::BeginRendering();
	//GLib::Service(bQuit);

		// IMPORTANT: Tell GLib that we want to start rendering
	GLib::BeginRendering();
	// Tell GLib that we want to render some sprites
	GLib::Sprites::BeginRendering();
	//for (int id = 0; id < gameobjects.get_size(); id++)
	//	if (gameobjects[id]->irender)
	//	{

	//		static float moveDist = .01f;
	//		static float moveDir = moveDist;

	//		// Tell GLib to render this sprite at our calculated location
	//		auto pos = GLib::Point2D{ gameobjects[id]->position.x, gameobjects[id]->position.y };
	//		GLib::Sprites::RenderSprite(*gameobjects[id]->irender, pos, 0.0f);
	//	}
	for (int i = 0; i < ListRenderComponent.size(); i++) {
		if (!(ListRenderComponent[i])->ParentGameObject->Active) continue;
		ListRenderComponent[i]->Update();
	}

	// Tell GLib we're done rendering sprites
	GLib::Sprites::EndRendering();
	// IMPORTANT: Tell GLib we're done rendering
	GLib::EndRendering();

	
	
}
