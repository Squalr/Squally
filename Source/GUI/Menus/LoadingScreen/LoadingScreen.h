#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "GUI/Menus/MenuBackground.h"
#include "GUI/Components/CProgressBar.h"
#include "GUI/Components/FadeScene.h"
#include "Utils/StrUtils.h"
#include "Level/Parser/Parser.h"
#include <mutex>

using namespace cocos2d;
using namespace cocos_experimental;

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
	void onFileEnumerationComplete(std::vector<std::string> files);
	void onTextureAssetLoaded(Texture2D* asset);
	void onSoundAssetLoaded();
	void incrementLoadedFileCount();
	void initializePositions();

	static bool isPreloadableImage(std::string filePath);
	static bool isPreloadableSound(std::string filePath);

	Node* background;
	Sprite* loadingWindow;
	CProgressBar* progressBar;

	int totalFileCount;
	std::atomic_int loadedFileCount;
	std::string currentLevelFile;
};

