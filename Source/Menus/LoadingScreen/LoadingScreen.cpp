#include "LoadingScreen.h"

#include "cocos/audio/include/AudioEngine.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/platform/CCFileUtils.h"
#include "cocos/renderer/CCTextureCache.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Maps/SerializableMap.h"
#include "Engine/UI/Controls/CProgressBar.h"
#include "Engine/Utils/StrUtils.h"
#include "Events/NavigationEvents.h"
#include "Menus/MenuBackground.h"

using namespace cocos2d;
using namespace cocos_experimental;

LoadingScreen* LoadingScreen::instance = nullptr;

void LoadingScreen::registerGlobalScene()
{
	if (LoadingScreen::instance == nullptr)
	{
		LoadingScreen::instance = new LoadingScreen();

		LoadingScreen::instance->autorelease();
		LoadingScreen::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(LoadingScreen::instance);
}

LoadingScreen::LoadingScreen()
{
	this->backgroundNode = Node::create();
	this->progressBar = CProgressBar::create();

	this->addChild(this->backgroundNode);
	this->addChild(this->progressBar);
}

LoadingScreen::~LoadingScreen()
{
}

void LoadingScreen::onEnter()
{
	super::onEnter();

	this->backgroundNode->addChild(MenuBackground::claimInstance());
}

void LoadingScreen::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->progressBar->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 480.0f));
}

void LoadingScreen::initializeListeners()
{
	super::initializeListeners();

	LoadingScreen::instance->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigateLoadingScreen, [](EventCustom* args)
	{
		NavigationEvents::NavigateLoadingScreenArgs* loadArgs = static_cast<NavigationEvents::NavigateLoadingScreenArgs*>(args->getUserData());

		if (loadArgs != nullptr)
		{
			GlobalDirector::loadScene(LoadingScreen::instance);
			LoadingScreen::instance->loadLevel(loadArgs->levelFile, loadArgs->onLoadCallback);
		}
	}));
}

void LoadingScreen::loadLevel(std::string levelFile, std::function<void(SerializableMap*)> onLoadCallback)
{
	this->totalFileCount = 0;
	this->loadedFileCount = 0;
	this->currentLevelFile = levelFile;
	this->onLoadCallback = onLoadCallback;

	this->map = SerializableMap::deserialize(levelFile);
	this->map->retain();

	// Asyncronously get all files under the game, and load them
	FileUtils::getInstance()->listFilesRecursivelyAsync("Strings", CC_CALLBACK_1(LoadingScreen::onFileEnumerationComplete, this));
}

void LoadingScreen::onFileEnumerationComplete(std::vector<std::string> files)
{
	// TEMP DEBUG: Remove this to re-enable loading screen
	//if (this->onLoadCallback != nullptr)
	//{
	//	this->onLoadCallback(this->map);
	//	return;
	//}

	auto textureLoadCallback = CC_CALLBACK_1(LoadingScreen::onTextureAssetLoaded, this);
	auto soundLoadCallback = CC_CALLBACK_0(LoadingScreen::onSoundAssetLoaded, this);

	for (auto it = files.begin(); it != files.end(); it++)
	{
		std::string file = *it;

		if (LoadingScreen::isPreloadableImage(file) ||
			LoadingScreen::isPreloadableSound(file))
		{
			this->totalFileCount++;
		}
	}

	for (auto it = files.begin(); it != files.end(); it++)
	{
		std::string file = *it;

		if (LoadingScreen::isPreloadableImage(file))
		{
			// Load texture
			Director::getInstance()->getTextureCache()->addImageAsync(file, textureLoadCallback);
		}
		else if (LoadingScreen::isPreloadableSound(file))
		{
			// Load sound
			AudioEngine::preload(file, soundLoadCallback);
		}
	}

	// In case there are no assets to load we also need to check here
	this->enterLevelIfDoneLoading();
}

void LoadingScreen::onTextureAssetLoaded(Texture2D* asset)
{
	this->incrementLoadedFileCount();
	this->enterLevelIfDoneLoading();
}

void LoadingScreen::onSoundAssetLoaded()
{
	this->incrementLoadedFileCount();
	this->enterLevelIfDoneLoading();
}

void LoadingScreen::enterLevelIfDoneLoading()
{
	if (this->levelIsLoaded())
	{
		if (this->onLoadCallback != nullptr)
		{
			this->onLoadCallback(this->map);
		}
	}
}

void LoadingScreen::incrementLoadedFileCount()
{
	this->loadedFileCount.fetch_add(1);
	this->progressBar->setProgress(this->totalFileCount == 0 ? 0.0f : (float)this->loadedFileCount / (float)this->totalFileCount);
}

bool LoadingScreen::levelIsLoaded() 
{
	return this->loadedFileCount >= this->totalFileCount - 1;
}

bool LoadingScreen::isPreloadableImage(std::string filePath)
{
	if (StrUtils::endsWith(filePath, ".png", true) ||
		StrUtils::endsWith(filePath, ".jpg", true) ||
		StrUtils::endsWith(filePath, ".jpeg", true))
	{
		return true;
	}

	return false;
}

bool LoadingScreen::isPreloadableSound(std::string filePath)
{
	if (StrUtils::endsWith(filePath, ".mp3", true) ||
		StrUtils::endsWith(filePath, ".wav", true))
	{
		return true;
	}

	return false;
}
