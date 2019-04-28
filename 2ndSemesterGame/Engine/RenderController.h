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

	void RemoveRenderComponent(Engine::ObservingPointer<RenderComponent> p) {
		for (int i = ListRenderComponent.size() - 1; i >= 0; i--) {
			if (ListRenderComponent[i] == p) {
				ListRenderComponent.erase(ListRenderComponent.begin() + i);
				break;
			}
		}
	}

private:
	//Engine::ObservingPointer<GameManager> gameManager;
};

