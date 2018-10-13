#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/Forest/ForestHexusOpponents.h"
#include "Scenes/Menus/Minigames/Hexus/ChapterSelect/Forest/HexusChapterPreviewForest.h"
#include "Scenes/Menus/Minigames/Hexus/OpponentSelect/HexusOpponentMenuBase.h"
#include "Scenes/Menus/Minigames/Hexus/OpponentSelect/HexusOpponentPreview.h"

using namespace cocos2d;

class HexusOpponentMenuForest : public HexusOpponentMenuBase
{
public:
	static HexusOpponentMenuForest * create();

protected:
	HexusOpponentMenuForest();
	~HexusOpponentMenuForest();
};

