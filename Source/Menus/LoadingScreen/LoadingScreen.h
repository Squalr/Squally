#pragma once
#include <chrono>
#include <mutex>
#include <thread>
#include <future> 

#include "cocos2d.h"

#include "Engine/GlobalScene.h"
#include "Engine/Maps/SerializableMap.h"
#include "Engine/UI/Controls/CProgressBar.h"
#include "Engine/Utils/StrUtils.h"
#include "Events/NavigationEvents.h"
#include "Menus/MenuBackground.h"
#include "Resources/UIResources.h"

using namespace cocos2d;
using namespace cocos_experimental;

class LoadingScreen : public GlobalScene
{
public:
	static void registerGlobalScene();

	void loadLevel(std::string levelFile, std::function<void(SerializableMap*)> onLoadCallback);

protected:
	LoadingScreen();
	~LoadingScreen();

private:
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onFileEnumerationComplete(std::vector<std::string> files);
	void onTextureAssetLoaded(Texture2D* asset);
	void onSoundAssetLoaded();
	void incrementLoadedFileCount();
	bool levelIsLoaded();
	void enterLevelIfDoneLoading();

	static bool isPreloadableImage(std::string filePath);
	static bool isPreloadableSound(std::string filePath);

	Node* backgroundNode;
	CProgressBar* progressBar;
	SerializableMap* map;
	std::function<void(SerializableMap*)> onLoadCallback;

	int totalFileCount;
	std::atomic_int loadedFileCount;
	std::string currentLevelFile;

	static LoadingScreen* instance;
};

