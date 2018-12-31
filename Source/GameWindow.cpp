#include "GameWindow.h"

#include "cocos/audio/include/AudioEngine.h"
#include "cocos/base/CCDirector.h"
#include "cocos/platform/desktop/CCGLViewImpl-desktop.h"

#include "Analytics/AnalyticsCategories.h"
#include "Bootstrapper.h"
#include "Engine/Analytics/Analytics.h"
#include "Engine/Config/ConfigManager.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Steam/Steam.h"
#include "Engine/Utils/LogUtils.h"
#include "Menus/Title/TitleScreen.h"

using namespace cocos2d;
using namespace cocos2d::cocos_experimental;

const std::string GameWindow::GameWindowTitle = "Squally";

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
	if (!LogUtils::redirectStandardOutputToFile())
	{
		LogUtils::logError("failed to redirect standard output to file.");
	}

	if (!Steam::init())
	{
		return false;
	}

	Director* director = Director::getInstance();
	GLViewImpl* glView;

	Size resolutionSize = ConfigManager::getResolutionSize();

	if (ConfigManager::getIsFullScreen())
	{
		glView = GLViewImpl::createWithFullScreen(GameWindow::GameWindowTitle);
		glView->setDesignResolutionSize(1920, 1080, ResolutionPolicy::SHOW_ALL);
	}
	else
	{
		glView = GLViewImpl::createWithRect(GameWindow::GameWindowTitle, Rect(0, 0, resolutionSize.width, resolutionSize.height), 1, true);
		glView->setDesignResolutionSize(1920, 1080, ResolutionPolicy::SHOW_ALL);
	}
	
	glView->setCursorVisible(false);
	director->setOpenGLView(glView);

	// Initialize the game
	Bootstrapper::initialize();

	#ifdef _WIN32
		Analytics::sendEvent(AnalyticsCategories::GameStart, "Windows");
	#elif __APPLE__
		Analytics::sendEvent(AnalyticsCategories::GameStart, "OS X");
	#elif __linux__
		Analytics::sendEvent(AnalyticsCategories::GameStart, "Linux");
	#endif

	// load into the title screen first
	GlobalDirector::loadScene(TitleScreen::getInstance());

	return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void GameWindow::applicationDidEnterBackground()
{
	Director::getInstance()->stopAnimation();
	AudioEngine::pauseAll();
}

// This function will be called when the app is active again
void GameWindow::applicationWillEnterForeground()
{
	Director::getInstance()->startAnimation();
	AudioEngine::resumeAll();
}
