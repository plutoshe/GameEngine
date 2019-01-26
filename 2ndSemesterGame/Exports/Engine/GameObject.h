#pragma once
#include "Vector3D.h"
#include "GLib.h"
#include "assert.h"
#include "Log.h"

class GameObject
{
public:
	
	GameObject();
	~GameObject();

	Vector3D position;
	Vector3D velocity;
	float mass;
	float drag;
	GLib::Sprites::Sprite * irender;
	void CreateSprite(const char * i_pFilename);
	void * LoadFile(const char * i_pFilename, size_t & o_sizeFile);
	void CheckInput(unsigned int i_VKeyID);
};

