#pragma once
#include <iostream>
#include <filesystem>
#include "cocos2d.h"
#include "Resources.h"
#include "GUI/Menus/MenuBackground.h"
#include "GUI/Components/FadeScene.h"
#include "Utils/StrUtils.h"
#include "Level/Parser/Parser.h"
#include <mutex>

using namespace cocos2d;

class LoadingScreen : public FadeScene
{
public:
	static LoadingScreen * create();

	void loadLevel(std::string levelFile);

protected:
	LoadingScreen();
	~LoadingScreen();

private:
	void onEnter() override;
	void onAssetLoaded(Texture2D* asset);

	Node* background;
	Sprite* loadingWindow;
	int totalFileCount;
	std::atomic_int loadedFileCount;
	std::string currentLevelFile;
};

