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

	this->addChild(this->background);
}

LoadingScreen::~LoadingScreen()
{
}

void LoadingScreen::onEnter()
{
	FadeScene::onEnter();

	this->background->addChild(MenuBackground::claimInstance());

	this->addChild(Mouse::claimInstance());
}

void LoadingScreen::loadLevel(std::string levelFile)
{
	auto callback = CC_CALLBACK_1(LoadingScreen::onAssetLoaded, this);
	this->totalFileCount = 0;
	this->loadedFileCount = 0;

	for (std::tr2::sys::recursive_directory_iterator it("."), end; it != end; ++it)
	{
		if (!std::tr2::sys::is_directory(it->path()))
		{
			std::string file = it->path().filename().generic_string();

			if (GameUtils::isSupportedImagePath(file))
			{
				this->totalFileCount++;
			}
		}
	}

	for (std::tr2::sys::recursive_directory_iterator it("."), end; it != end; ++it)
	{
		if (!std::tr2::sys::is_directory(it->path()))
		{
			std::string file = it->path().generic_string();

			if (GameUtils::isSupportedImagePath(file))
			{
				cocos2d::log(file.c_str());
				Director::getInstance()->getTextureCache()->addImageAsync(file, callback);
			}
		}
	}

	this->currentLevelFile = levelFile;
}

void LoadingScreen::onAssetLoaded(Texture2D* asset)
{
	if (this->loadedFileCount.fetch_add(1) == this->totalFileCount - 1)
	{
		cocos_experimental::TMXTiledMap* mapRaw = cocos_experimental::TMXTiledMap::create(this->currentLevelFile);
		LevelMap::mapSize = Size(mapRaw->getMapSize().width * mapRaw->getTileSize().width, mapRaw->getMapSize().height * mapRaw->getTileSize().height);

		LevelMap* map = Parser::parseMap(mapRaw);
		GameUtils::enterLevel(map);
	}
}
