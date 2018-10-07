#include "GameWindow.h"

using namespace cocos2d;
using namespace cocos2d::cocos_experimental;

GameWindow::GameWindow()
{
}

GameWindow::~GameWindow()
{
	AudioEngine::end();
}

// If you want a different context, modify the value of glContextAttrs it will affect all platforms
void GameWindow::initGLContextAttrs()
{
	// Set OpenGL context attributes: red, green, blue, alpha, depth, stencil
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };

	GLView::setGLContextAttrs(glContextAttrs);
}

bool GameWindow::applicationDidFinishLaunching()
{
	Director* director = Director::getInstance();
	GLViewImpl* glView;

	Size resolutionSize = ConfigManager::getResolutionSize();

	if (ConfigManager::getIsFullScreen())
	{
		glView = GLViewImpl::createWithFullScreen(this->GameWindowTitle);
		glView->setDesignResolutionSize(1920, 1080, ResolutionPolicy::SHOW_ALL);
	}
	else
	{
		glView = GLViewImpl::createWithRect(this->GameWindowTitle, Rect(0, 0, resolutionSize.width, resolutionSize.height));
		glView->setDesignResolutionSize(1920, 1080, ResolutionPolicy::SHOW_ALL);
	}

	director->setOpenGLView(glView);
	glView->setCursorVisible(false);

	// Initialize the game
	Bootstrapper::initialize();

	#ifdef _WIN32
		Analytics::sendEvent("GameStart", "Windows");
	#elif __APPLE__
		Analytics::sendEvent("GameStart", "OS X");
	#elif __linux__
		Analytics::sendEvent("GameStart", "Linux");
	#endif

	return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void GameWindow::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();
	AudioEngine::pauseAll();
}

// This function will be called when the app is active again
void GameWindow::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();
	AudioEngine::resumeAll();
}
