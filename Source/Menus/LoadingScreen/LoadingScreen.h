#pragma once
#include <chrono>
#include <mutex>
#include <thread>
#include <future> 

#include "cocos2d.h"

#include "Events/NavigationEvents.h"
#include "Engine/Maps/SerializableMap.h"
#include "Engine/Physics/CollisionDeserializer.h"
#include "Engine/UI/Controls/CProgressBar.h"
#include "Engine/UI/HUD/Hud.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources/UIResources.h"
#include "Sound/MusicDeserializer.h"

using namespace cocos2d;
using namespace cocos_experimental;

class LoadingScreen : public Hud
{
public:
	static LoadingScreen* create();

	void loadLevel(std::string levelFile, const std::function<void(SerializableMap*)> newOnLoadCallback);

protected:
	LoadingScreen();
	~LoadingScreen();

private:
	void onEnter() override;
	void initializePositions() override;
	void onFileEnumerationComplete(std::vector<std::string> files);
	void onTextureAssetLoaded(Texture2D* asset);
	void onSoundAssetLoaded();
	void incrementLoadedFileCount();
	bool levelIsLoaded();
	void enterLevelIfDoneLoading();

	static bool isPreloadableImage(std::string filePath);
	static bool isPreloadableSound(std::string filePath);

	Node* background;
	CProgressBar* progressBar;
	SerializableMap* map;
	std::function<void(SerializableMap*)> onLoadCallback;

	int totalFileCount;
	std::atomic_int loadedFileCount;
	std::string currentLevelFile;
};

