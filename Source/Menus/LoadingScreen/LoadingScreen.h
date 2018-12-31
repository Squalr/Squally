#pragma once
#include <chrono>
#include <mutex>
#include <thread>
#include <future> 

#include "Engine/GlobalScene.h"

class CProgressBar;
class SerializableMap;

class LoadingScreen : public GlobalScene
{
public:
	static void registerGlobalScene();

	void loadLevel(std::string levelFile, std::function<void(SerializableMap*)> onLoadCallback);

protected:
	LoadingScreen();
	~LoadingScreen();

private:
	typedef GlobalScene super;
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onFileEnumerationComplete(std::vector<std::string> files);
	void onTextureAssetLoaded(cocos2d::Texture2D* asset);
	void onSoundAssetLoaded();
	void incrementLoadedFileCount();
	bool levelIsLoaded();
	void enterLevelIfDoneLoading();

	static bool isPreloadableImage(std::string filePath);
	static bool isPreloadableSound(std::string filePath);

	cocos2d::Node* backgroundNode;
	CProgressBar* progressBar;
	SerializableMap* map;
	std::function<void(SerializableMap*)> onLoadCallback;

	int totalFileCount;
	std::atomic_int loadedFileCount;
	std::string currentLevelFile;

	static LoadingScreen* instance;
};

