#pragma once
#include "cocos2d.h"

#include "Engine/Utils/GameUtils.h"
#include "Resources.h"

using namespace cocos2d;

class SaveManager
{
public:
	// While not the best design, it's much easier to simply expose the save file value map and expect that calling classes insert data appropriately
	static ValueMap* getValueMap();

	static void setActiveSave(int index);
	static void save();

private:
	static SaveManager* getInstance();
	SaveManager();
	~SaveManager();

	ValueMap saveData;
	std::string saveFile;

	static SaveManager* saveManagerInstance;
	static const std::string saveFileName;
};
