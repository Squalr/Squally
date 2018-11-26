#pragma once
#include "cocos2d.h"

#include "Menus/Minigames/Hexus/ChapterSelect/Obelisk/HexusChapterPreviewObelisk.h"
#include "Menus/Minigames/Hexus/OpponentSelect/HexusOpponentMenuBase.h"
#include "Menus/Minigames/Hexus/OpponentSelect/HexusOpponentPreview.h"
#include "Scenes/Hexus/Opponents/Obelisk/ObeliskHexusOpponents.h"

using namespace cocos2d;

class HexusOpponentMenuObelisk : public HexusOpponentMenuBase
{
public:
	static HexusOpponentMenuObelisk * create();

protected:
	HexusOpponentMenuObelisk();
	~HexusOpponentMenuObelisk();
};

