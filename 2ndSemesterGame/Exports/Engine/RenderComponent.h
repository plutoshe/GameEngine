#pragma once
#include "SmartPointer.h"
#include "GLib.h"
class GameObject;
class RenderComponent
{
public:
	RenderComponent();
	~RenderComponent();
	// parent
	Engine::ObservingPointer<GameObject> ParentGameObject;

	// textures
	Engine::OwningPointer<GLib::Sprites::Sprite> Irender;

	// materials

	// shaders

	// functions
	void Render();
	void Release();
	//void CreateSprite(const char * i_pFilename);
	//void *LoadFile(const char * i_pFilename, size_t & o_sizeFile);



};

