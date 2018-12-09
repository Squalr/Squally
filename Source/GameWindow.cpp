#include "GameWindow.h"

#include "cocos2d.h"
#include "cocos/audio/include/AudioEngine.h"

#include "steam_api.h"

#include "Analytics/AnalyticsCategories.h"
#include "Bootstrapper.h"
#include "Engine/Analytics/Analytics.h"
#include "Engine/Config/ConfigManager.h"
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

	if (Steam::isSteamEnabled())
	{
		if (SteamAPI_RestartAppIfNecessary(Steam::SteamAppId))
		{
			return false;
		}

		if (!SteamAPI_Init())
		{
			return false;
		}

		LogUtils::log("Steam initialized");
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
		glView = GLViewImpl::createWithRect(GameWindow::GameWindowTitle, Rect(0, 0, resolutionSize.width, resolutionSize.height));
		glView->setDesignResolutionSize(1920, 1080, ResolutionPolicy::SHOW_ALL);
	}

	director->setOpenGLView(glView);
	glView->setCursorVisible(false);

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
void GameWindow::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();
	AudioEngine::pauseAll();
}

// This function will be called when the app is active again
void GameWindow::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();
	AudioEngine::resumeAll();
}
