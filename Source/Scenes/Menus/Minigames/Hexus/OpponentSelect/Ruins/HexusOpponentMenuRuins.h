#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/Ruins/RuinsHexusOpponents.h"
#include "Scenes/Menus/Minigames/Hexus/ChapterSelect/Ruins/HexusChapterPreviewRuins.h"
#include "Scenes/Menus/Minigames/Hexus/OpponentSelect/HexusOpponentMenuBase.h"
#include "Scenes/Menus/Minigames/Hexus/OpponentSelect/HexusOpponentPreview.h"

using namespace cocos2d;

class HexusOpponentMenuRuins : public HexusOpponentMenuBase
{
public:
	static HexusOpponentMenuRuins * create();

protected:
	HexusOpponentMenuRuins();
	~HexusOpponentMenuRuins();
};

