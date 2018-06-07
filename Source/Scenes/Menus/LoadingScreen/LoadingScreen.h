#pragma once
#include <mutex>

#include "cocos2d.h"

#include "Events/NavigationEvents.h"
#include "Engine/Rendering/Components/CProgressBar.h"
#include "Engine/Rendering/Components/FadeScene.h"
#include "Resources.h"
#include "Scenes/Level/Parser/Parser.h"
#include "Scenes/Menus/MenuBackground.h"
#include "Utils/StrUtils.h"


using namespace cocos2d;
using namespace cocos_experimental;

class LoadingScreen : public FadeScene
{
public:
	static LoadingScreen * create();

	void loadLevel(std::string levelFile, const std::function<void(LevelMap*)> newOnLoadCallback);

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
	std::function<void(LevelMap*)> onLoadCallback;

	int totalFileCount;
	std::atomic_int loadedFileCount;
	std::string currentLevelFile;
};

