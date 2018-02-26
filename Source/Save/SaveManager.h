#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Utils/GameUtils.h"

using namespace cocos2d;

class SaveManager
{
public:
	static void setActiveSave(int index);

private:
	static SaveManager * getInstance();
	SaveManager();
	~SaveManager();

	ValueMap* saveData;
	std::string saveFile;

	static SaveManager * configManagerInstance;
	static const std::string musicVolumeKey;
};
