#include "LoadingScreen.h"

LoadingScreen * LoadingScreen::create()
{
	LoadingScreen* loadingScreen = new LoadingScreen();

	loadingScreen->autorelease();

	return loadingScreen;
}

LoadingScreen::LoadingScreen()
{
	this->background = Node::create();
	this->progressBar = CProgressBar::create();

	this->addChild(this->background);
	this->addChild(this->progressBar);

	this->setFadeSpeed(0.0f);
}

LoadingScreen::~LoadingScreen()
{
}

void LoadingScreen::onEnter()
{
	FadeScene::onEnter();

	this->background->addChild(MenuBackground::claimInstance());

	this->addChild(Mouse::claimInstance());

	this->initializePositions();
}

void LoadingScreen::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->progressBar->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 480.0f));
}

void LoadingScreen::loadLevel(std::string levelFile)
{
	this->totalFileCount = 0;
	this->loadedFileCount = 0;
	this->currentLevelFile = levelFile;

	// Asyncronously get all files under the game, and load them
	FileUtils::getInstance()->listFilesRecursivelyAsync("./Resources/", CC_CALLBACK_1(LoadingScreen::onFileEnumerationComplete, this));
}

void LoadingScreen::onFileEnumerationComplete(std::vector<std::string> files)
{
	auto textureLoadCallback = CC_CALLBACK_1(LoadingScreen::onTextureAssetLoaded, this);
	auto soundLoadCallback = CC_CALLBACK_0(LoadingScreen::onSoundAssetLoaded, this);

	for (auto it = files.begin(); it != files.end(); it++)
	{
		std::string file = *it;

		if (LoadingScreen::isPreloadableImage(file) ||
			LoadingScreen::isPreloadableSound(file))
		{
			this->totalFileCount++;
			break;
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
		break;
	}
}

void LoadingScreen::onTextureAssetLoaded(Texture2D* asset)
{
	this->incrementLoadedFileCount();
}

void LoadingScreen::onSoundAssetLoaded()
{
	this->incrementLoadedFileCount();
}

void LoadingScreen::incrementLoadedFileCount()
{
	this->progressBar->setProgress(this->totalFileCount == 0 ? 0.0f : (float)this->loadedFileCount / (float)this->totalFileCount);

	if (this->loadedFileCount.fetch_add(1) >= this->totalFileCount - 1)
	{
		cocos_experimental::TMXTiledMap* mapRaw = cocos_experimental::TMXTiledMap::create(this->currentLevelFile);
		LevelMap::mapSize = Size(mapRaw->getMapSize().width * mapRaw->getTileSize().width, mapRaw->getMapSize().height * mapRaw->getTileSize().height);

		LevelMap* map = Parser::parseMap(mapRaw);
		NavigationEvents::enterLevel(map);
	}
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
