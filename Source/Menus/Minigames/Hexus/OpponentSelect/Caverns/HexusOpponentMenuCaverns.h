#pragma once
#include "cocos2d.h"

#include "Menus/Minigames/Hexus/ChapterSelect/Caverns/HexusChapterPreviewCaverns.h"
#include "Menus/Minigames/Hexus/OpponentSelect/HexusOpponentMenuBase.h"
#include "Menus/Minigames/Hexus/OpponentSelect/HexusOpponentPreview.h"

#include "Scenes/Hexus/Opponents/Caverns/CavernsHexusOpponents.h"

using namespace cocos2d;

class HexusOpponentMenuCaverns : public HexusOpponentMenuBase
{
public:
	static HexusOpponentMenuCaverns * create();

protected:
	HexusOpponentMenuCaverns();
	~HexusOpponentMenuCaverns();
};

