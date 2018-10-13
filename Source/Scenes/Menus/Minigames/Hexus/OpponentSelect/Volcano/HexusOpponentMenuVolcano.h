#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/Volcano/VolcanoHexusOpponents.h"
#include "Scenes/Menus/Minigames/Hexus/ChapterSelect/Volcano/HexusChapterPreviewVolcano.h"
#include "Scenes/Menus/Minigames/Hexus/OpponentSelect/HexusOpponentMenuBase.h"
#include "Scenes/Menus/Minigames/Hexus/OpponentSelect/HexusOpponentPreview.h"

using namespace cocos2d;

class HexusOpponentMenuVolcano : public HexusOpponentMenuBase
{
public:
	static HexusOpponentMenuVolcano * create();

protected:
	HexusOpponentMenuVolcano();
	~HexusOpponentMenuVolcano();
};

