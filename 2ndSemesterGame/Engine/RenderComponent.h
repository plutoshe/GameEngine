#pragma once
#include "GLib.h"
#include "SmartPointer.h"
class GameObject;

typedef GLib::Sprites::Sprite SpriteType;
class RenderComponent
{
public:
	RenderComponent() {}
	RenderComponent(const RenderComponent &r) {
		Clear();
		// TODO: r.Irender is reference to pointer, change to value, has error with undefined type Sprite
		if (r.Irender)
			Irender = Engine::OwningPointer<GLib::Sprites::Sprite>(r.Irender);
		/*GLib::Sprites::Sprite *a = new GLib::Sprites::Sprite(b->);
		a = Irender.OriginalPointer();
		auto b = Engine::OwningPointer<GLib::Sprites::Sprite>(a);*/
		//Irender = Engine::OwningPointer<GLib::Sprites::Sprite>(*Irender);
	}

	~RenderComponent() {
		/*if (Irender)
			GLib::Sprites::Release(Irender.OriginalPointer());*/
	}

	void Clear() {
		ParentGameObject = nullptr;
		Irender = nullptr;
	}

	// parent
	Engine::ObservingPointer<GameObject> ParentGameObject;

	// textures
	Engine::OwningPointer<GLib::Sprites::Sprite> Irender;

	// materials

	// shaders

	// functions
	virtual void Update();
	void Render();
	void Release();
	void CreateSprite(const char * i_pFilename);
	void CreateSprite(const char * i_pFilename, int _width, int _height);
	void* LoadFile(const char * i_pFilename, size_t & o_sizeFile);
};

