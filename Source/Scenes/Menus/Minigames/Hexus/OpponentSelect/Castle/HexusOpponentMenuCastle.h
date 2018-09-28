#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponents.h"
#include "Scenes/Menus/Minigames/Hexus/ChapterSelect/Castle/HexusChapterPreviewCastle.h"
#include "Scenes/Menus/Minigames/Hexus/OpponentSelect/HexusOpponentMenuBase.h"
#include "Scenes/Menus/Minigames/Hexus/OpponentSelect/HexusOpponentPreview.h"

using namespace cocos2d;

class HexusOpponentMenuCastle : public HexusOpponentMenuBase
{
public:
	static HexusOpponentMenuCastle * create();

protected:
	HexusOpponentMenuCastle();
	~HexusOpponentMenuCastle();
};

