#include "GameWindow.h"

#include <GLFW/glfw3.h>

#include "cocos/audio/include/AudioEngine.h"
#include "cocos/base/CCDirector.h"
#include "cocos/platform/desktop/CCGLViewImpl-desktop.h"

#include "Analytics/AnalyticsCategories.h"
#include "Bootstrapper.h"
#include "Engine/Analytics/Analytics.h"
#include "Engine/Config/ConfigManager.h"
#include "Engine/Events/NavigationEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/GlobalNode.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Steam/Steam.h"
#include "Engine/Utils/LogUtils.h"
#include "Scenes/Title/TitleScreen.h"

#include "Strings/Common/Squally.h"

using namespace cocos2d;
using namespace cocos2d::cocos_experimental;

GameWindow::GameWindow()
{
	this->gameWindowTitleContainer = GlobalNode::create();
	this->gameWindowTitle = Strings::Common_Squally::create();
	this->glView = nullptr;

	// Listen for locale change events and update the window title
	this->gameWindowTitle->setOnStringUpdateCallback([=](LocalizedString* newString)
	{
		if (this->glView != nullptr)
		{
			this->glView->setViewName(newString->getString());
			glfwSetWindowTitle(this->glView->getWindow(), newString->getString().c_str());
		}
	});

	// The string needs to be in a global node so that it can utilize the cocos event system
	this->gameWindowTitleContainer->addChild(this->gameWindowTitle);
	GlobalDirector::getInstance()->registerGlobalNode(this->gameWindowTitleContainer);
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

	cocos2d::Size resolutionSize = ConfigManager::getResolutionSize();

	if (ConfigManager::getIsFullScreen())
	{
		this->glView = GLViewImpl::createWithFullScreen(this->gameWindowTitle->getString());
		this->glView->setDesignResolutionSize(1920, 1080, ResolutionPolicy::SHOW_ALL);
	}
	else
	{
		this->glView = GLViewImpl::createWithRect(this->gameWindowTitle->getString(), cocos2d::Rect(0, 0, resolutionSize.width, resolutionSize.height), 1, true);
		this->glView->setDesignResolutionSize(1920, 1080, ResolutionPolicy::SHOW_ALL);
	}
	
	this->glView->setCursorVisible(false);
	Director::getInstance()->setOpenGLView(this->glView);

	// Initialize the game
	Bootstrapper::initialize();

	#ifdef _WIN32
		Analytics::sendEvent(AnalyticsCategories::GameStart, "Windows");
	#elif __APPLE__
		Analytics::sendEvent(AnalyticsCategories::GameStart, "OS X");
	#elif __linux__
		Analytics::sendEvent(AnalyticsCategories::GameStart, "Linux");
	#endif

	NavigationEvents2::LoadScene(TitleScreen::getInstance());

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
