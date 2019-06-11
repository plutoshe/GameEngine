#pragma once
#include <set>
#include "Engine/SSERedef.h"

struct MouseStatus {
	bool exist;
	int m_keyID;
	int m_keyStatus;
	Vector2f m_pos;
	void Clear() {
		exist = 0;
	}
};

class InputController
{
public:
	InputController();
	~InputController();

		
	void Update();
		 
	// Input Status
	std::set<unsigned int> KeyStatus;
	MouseStatus m_mouseStatus;
	bool IsKeyDown(unsigned int keyCode);

private:
	void GetInput();
};


