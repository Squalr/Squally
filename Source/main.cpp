#include "Main.h"
#include "Window.h"
#include "cocos2d.h"

using namespace cocos2d;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Create the application instance
	Window app;
	return Application::getInstance()->run();
}
