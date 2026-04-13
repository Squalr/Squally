#include "GameWindow.h"

#include <algorithm>

#include <GLFW/glfw3.h>

#include "base/CCDirector.h"
#include "platform/desktop/CCGLViewImpl-desktop.h"

#include "Bootstrapper.h"
#include "Engine/Config/ConfigManager.h"
#include "Engine/Events/NavigationEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/GlobalNode.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Steam/Steam.h"
#include "Engine/Utils/LogUtils.h"
#include "Scenes/Title/TitleScreen.h"

#include "Strings/Strings.h"

using namespace cocos2d;

GameWindow::OffsetLabAutomationOptions GameWindow::offsetLabAutomationOptions = GameWindow::OffsetLabAutomationOptions();

void GameWindow::configureOffsetLabAutomationOptionsFromArgs(const std::vector<std::string>& args)
{
	GameWindow::offsetLabAutomationOptions = OffsetLabAutomationOptions();

	for (size_t index = 0; index < args.size(); index++)
	{
		const std::string& arg = args[index];

		if (arg == "--offset-lab-automation")
		{
			GameWindow::offsetLabAutomationOptions.enabled = true;
		}
		else if (arg == "--offset-lab-quit")
		{
			GameWindow::offsetLabAutomationOptions.enabled = true;
			GameWindow::offsetLabAutomationOptions.quitOnComplete = true;
		}
		else if (arg.rfind("--offset-lab-item=", 0) == 0)
		{
			GameWindow::offsetLabAutomationOptions.enabled = true;
			GameWindow::offsetLabAutomationOptions.itemKey = arg.substr(std::string("--offset-lab-item=").size());
		}
		else if (arg == "--offset-lab-item" && index + 1 < args.size())
		{
			GameWindow::offsetLabAutomationOptions.enabled = true;
			GameWindow::offsetLabAutomationOptions.itemKey = args[++index];
		}
	}
}

bool GameWindow::isOffsetLabAutomationEnabled()
{
	return GameWindow::offsetLabAutomationOptions.enabled;
}

const GameWindow::OffsetLabAutomationOptions& GameWindow::getOffsetLabAutomationOptions()
{
	return GameWindow::offsetLabAutomationOptions;
}

GameWindow::GameWindow()
{
	this->gameWindowTitleContainer = GlobalNode::create();
	this->gameWindowTitle = Strings::Common_Squally::create();

	// Listen for locale change events and update the window title
	this->gameWindowTitle->setOnStringUpdateCallback([=]()
	{
		if (this->glView != nullptr)
		{
			this->glView->setViewName(this->gameWindowTitle->getString());
			glfwSetWindowTitle(this->glView->getWindow(), this->gameWindowTitle->getString().c_str());
		}
	});

	// The string needs to be in a global node so that it can utilize the cocos event system
	this->gameWindowTitleContainer->addChild(this->gameWindowTitle);
	GlobalDirector::getInstance()->RegisterGlobalNode(this->gameWindowTitleContainer);
}

GameWindow::~GameWindow()
{
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
	LogUtils::initialize();

	if (!Steam::Init())
	{
		return false;
	}

	cocos2d::CSize resolutionSize = ConfigManager::getResolutionSize();

	if (ConfigManager::getIsFullScreen())
	{
		this->glView = GLViewImpl::createWithFullScreen(this->gameWindowTitle->getString());
		this->glView->setDesignResolutionSize(1920, 1080, ResolutionPolicy::SHOW_ALL);
	}
	else
	{
		this->glView = GLViewImpl::createWithRect(this->gameWindowTitle->getString(), cocos2d::CRect(0, 0, resolutionSize.width, resolutionSize.height), 1, true);
		this->glView->setDesignResolutionSize(1920, 1080, ResolutionPolicy::SHOW_ALL);
	}
	
	this->glView->setCursorVisible(false);
	Director::getInstance()->setOpenGLView(this->glView);

	// Initialize the game
	Bootstrapper::initialize();

	NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs([=]() { return TitleScreen::getInstance(); }));

	return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void GameWindow::applicationDidEnterBackground()
{
	Director::getInstance()->stopAnimation();
	
	/*
	AudioEngine::pauseAll();
	*/
}

// This function will be called when the app is active again
void GameWindow::applicationWillEnterForeground()
{
	Director::getInstance()->startAnimation();
	
	/*
	AudioEngine::resumeAll();
	*/
}
