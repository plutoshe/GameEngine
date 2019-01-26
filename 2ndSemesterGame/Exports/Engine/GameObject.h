#pragma once
#include "Vector3D.h"
#include "GLib.h"
#include "assert.h"
#include "Log.h"
#include <vector>
class GameObject
{
public:
	
	GameObject();
	~GameObject();

	Vector3D position = Vector3D(0,0,0);
	Vector3D velocity = Vector3D(0, 0, 0);
	Vector3D DriveForceOnCurrentFrame = Vector3D(0, 0, 0);
	float mass = 1;
	float dragCof = 1;

	GLib::Sprites::Sprite * irender;
	void CreateSprite(const char * i_pFilename);
	void * LoadFile(const char * i_pFilename, size_t & o_sizeFile);
	void CheckInput(unsigned int i_VKeyID);
	void UpdatePhysics(double i_dt, std::vector<Vector3D> addition_Forces = std::vector<Vector3D>());
};

