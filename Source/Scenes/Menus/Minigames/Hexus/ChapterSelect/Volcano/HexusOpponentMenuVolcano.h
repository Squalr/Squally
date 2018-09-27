#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponents.h"
#include "Scenes/Menus/Minigames/Hexus/ChapterSelect/HexusOpponentMenuBase.h"
#include "Scenes/Menus/Minigames/Hexus/ChapterSelect/HexusOpponentPreview.h"

using namespace cocos2d;

class HexusOpponentMenuVolcano : public HexusOpponentMenuBase
{
public:
	static HexusOpponentMenuVolcano * create();

protected:
	HexusOpponentMenuVolcano();
	~HexusOpponentMenuVolcano();

private:
	static const std::string StringKeyProgressSave;
};

