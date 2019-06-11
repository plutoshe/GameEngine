#pragma once
#include "Engine/Engine.h"

class QtGameManager: public GameManager
{
public:
	QGuiApplication* m_app;
	QtGameManager() : GameManager() {}

	~QtGameManager() {  }

	bool Once() {
		DeltaTime += Timing::CalcLastFrameTime_ms();
		qDebug() << DeltaTime;
		if (DeltaTime < 10) return true;
		DeltaTime = 0;
		frameID++;
		Input->Update();
		PSGameObjectManager->Update();
		Physics->Update(DeltaTime / 1000);
		Render->Update();
		if (Input->IsKeyDown(27)) return true;
	}
};

