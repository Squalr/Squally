#pragma once
#include "cocos2d.h"

#include "Menus/Minigames/Hexus/ChapterSelect/Mech/HexusChapterPreviewMech.h"
#include "Menus/Minigames/Hexus/OpponentSelect/HexusOpponentMenuBase.h"
#include "Menus/Minigames/Hexus/OpponentSelect/HexusOpponentPreview.h"
#include "Resources.h"
#include "Scenes/Hexus/Opponents/Mech/MechHexusOpponents.h"

using namespace cocos2d;

class HexusOpponentMenuMech : public HexusOpponentMenuBase
{
public:
	static HexusOpponentMenuMech * create();

protected:
	HexusOpponentMenuMech();
	~HexusOpponentMenuMech();
};

