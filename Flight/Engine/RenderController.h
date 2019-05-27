#pragma once
#include "SmartPointer.h"
#include "RenderComponent.h"
#include <vector>
class RenderController
{
public:
    RenderController() {}


    virtual void RenderNow() {}

    void Update() {RenderNow();}
    std::vector<Engine::ObservingPointer<RenderComponent>> ListRenderComponent;

    void AddRenderController(Engine::ObservingPointer<RenderComponent> p) {
        ListRenderComponent.push_back(p);
    }

	void RemoveRenderComponent(Engine::ObservingPointer<RenderComponent> p) {
		for (size_t i = ListRenderComponent.size() - 1; i >= 0; i--) {
			if (ListRenderComponent[i] == p) {
				ListRenderComponent.erase(ListRenderComponent.begin() + i);
				break;
			}
		}
	}
};

