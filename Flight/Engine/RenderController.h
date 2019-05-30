#pragma once
#include "SmartPointer.h"
#include "RenderComponent.h"
#include <vector>
#include <QGuiApplication>
#include <Qdebug>
class RenderController
{
public:
    RenderController() { }
    virtual void Start() {}
    //virtual void RenderNow() {}

    virtual void Update() {
        qDebug() << "in wrong render of rendercontroller";
        //RenderNow(); 
    }
    virtual void test() { qDebug() << "in base";}
    std::vector<Engine::ObservingPointer<RenderComponent>> ListRenderComponent;

    void AddRenderController(Engine::ObservingPointer<RenderComponent> p) {
        ListRenderComponent.push_back(p);
    }

	void RemoveRenderComponent(Engine::ObservingPointer<RenderComponent> p) {
        for (int i = (int)(ListRenderComponent.size() - 1); i >= 0; i--) {
			if (ListRenderComponent[i] == p) {
				ListRenderComponent.erase(ListRenderComponent.begin() + i);
				break;
			}
		}
	}
};

