#include "Main.h"
#include "Window.h"
#include "cocos2d.h"

USING_NS_CC;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Create the application instance
	Window app;
	return Application::getInstance()->run();
}
