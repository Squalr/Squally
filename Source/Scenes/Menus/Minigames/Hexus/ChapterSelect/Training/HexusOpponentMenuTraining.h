#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponents.h"
#include "Scenes/Menus/Minigames/Hexus/ChapterSelect/HexusOpponentMenuBase.h"
#include "Scenes/Menus/Minigames/Hexus/ChapterSelect/HexusOpponentPreview.h"

using namespace cocos2d;

class HexusOpponentMenuTraining : public HexusOpponentMenuBase
{
public:
	static HexusOpponentMenuTraining * create();

protected:
	HexusOpponentMenuTraining();
	~HexusOpponentMenuTraining();

private:
	static const std::string StringKeyProgressSave;
};

