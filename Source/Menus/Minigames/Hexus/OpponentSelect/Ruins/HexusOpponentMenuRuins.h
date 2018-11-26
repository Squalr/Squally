#pragma once
#include "cocos2d.h"

#include "Menus/Minigames/Hexus/ChapterSelect/Ruins/HexusChapterPreviewRuins.h"
#include "Menus/Minigames/Hexus/OpponentSelect/HexusOpponentMenuBase.h"
#include "Menus/Minigames/Hexus/OpponentSelect/HexusOpponentPreview.h"
#include "Scenes/Hexus/Opponents/Ruins/RuinsHexusOpponents.h"

using namespace cocos2d;

class HexusOpponentMenuRuins : public HexusOpponentMenuBase
{
public:
	static HexusOpponentMenuRuins * create();

protected:
	HexusOpponentMenuRuins();
	~HexusOpponentMenuRuins();
};

