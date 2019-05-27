#pragma once
#include <set>


class InputController
{
public:
	InputController();
	~InputController();

		
	void Update();
		 
	// Input Status
	std::set<unsigned int> KeyStatus;
	bool IsKeyDown(unsigned int keyCode);

private:
	void GetInput();
};


