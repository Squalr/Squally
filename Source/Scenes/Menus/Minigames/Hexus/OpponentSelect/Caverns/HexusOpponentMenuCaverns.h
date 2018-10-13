#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/Caverns/CavernsHexusOpponents.h"
#include "Scenes/Menus/Minigames/Hexus/ChapterSelect/Caverns/HexusChapterPreviewCaverns.h"
#include "Scenes/Menus/Minigames/Hexus/OpponentSelect/HexusOpponentMenuBase.h"
#include "Scenes/Menus/Minigames/Hexus/OpponentSelect/HexusOpponentPreview.h"

using namespace cocos2d;

class HexusOpponentMenuCaverns : public HexusOpponentMenuBase
{
public:
	static HexusOpponentMenuCaverns * create();

protected:
	HexusOpponentMenuCaverns();
	~HexusOpponentMenuCaverns();
};

