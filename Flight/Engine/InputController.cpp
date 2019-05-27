#include "InputController.h"
#include "Timing.h"
#include "Log.h"
namespace GLib {
	extern HWND	g_hWnd;
}

InputController::InputController()
{
}


InputController::~InputController()
{
}

void InputController::GetInput() {
//	MSG mssg;
//	if (PeekMessage(&mssg, GLib::g_hWnd, 0, 0, PM_REMOVE))
//	{
//		switch (mssg.message)
//		{
//		case WM_QUIT:
//			PostQuitMessage(0);

//			break;

//		case WM_KEYDOWN:
//			WPARAM param = mssg.wParam;
//			unsigned int c = (unsigned int)MapVirtualKey(param, MAPVK_VK_TO_CHAR);
//			KeyStatus.insert(c);
//			break;
//		}
//		// dispatch the message
//		TranslateMessage(&mssg);
//		DispatchMessage(&mssg);
//	}
}

bool InputController::IsKeyDown(unsigned int keyCode) {
	return KeyStatus.find(keyCode) != KeyStatus.end();
}
	
void InputController::Update() {
	KeyStatus.clear();
	GetInput();
}
