#pragma once

#include "SmartPointer.h"
#include <string>
#include <QtDebug>
class GameObject;

class RenderComponent
{
public:
	RenderComponent() {}
    virtual ~RenderComponent() {}

    Engine::ObservingPointer<GameObject> ParentGameObject;
	void Clear() {
		ParentGameObject = nullptr;
	}

    virtual void CreateSprite(std::string filename) {}

    virtual void Render() {qDebug() << "In wrong place";}
    void SetWidth(float width) { m_width = width; }
    void SetHeight(float height) { m_height = height; }
    void SetSize(float width, float height) { m_width = width; m_height = height; }
    float m_width;
    float m_height;
};

