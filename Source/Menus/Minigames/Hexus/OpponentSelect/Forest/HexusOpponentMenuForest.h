#pragma once
#include "cocos2d.h"

#include "Menus/Minigames/Hexus/ChapterSelect/Forest/HexusChapterPreviewForest.h"
#include "Menus/Minigames/Hexus/OpponentSelect/HexusOpponentMenuBase.h"
#include "Menus/Minigames/Hexus/OpponentSelect/HexusOpponentPreview.h"
#include "Resources.h"
#include "Scenes/Hexus/Opponents/Forest/ForestHexusOpponents.h"

using namespace cocos2d;

class HexusOpponentMenuForest : public HexusOpponentMenuBase
{
public:
	static HexusOpponentMenuForest * create();

protected:
	HexusOpponentMenuForest();
	~HexusOpponentMenuForest();
};

