#pragma once
#include "GLib.h"
#include "SmartPointer.h"
#include "RenderComponent.h"
#include <vector>
class RenderController
{
public:
	RenderController();
	~RenderController();

		

	void Rendering();

	void Update();
	std::vector<Engine::ObservingPointer<RenderComponent>> ListRenderComponent;

	void AddRenderController(Engine::ObservingPointer<RenderComponent> p) {
		ListRenderComponent.push_back(p);
	}

private:
	//Engine::ObservingPointer<GameManager> gameManager;
};

