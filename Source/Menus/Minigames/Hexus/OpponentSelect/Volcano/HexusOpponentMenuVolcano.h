#pragma once
#include "cocos2d.h"

#include "Menus/Minigames/Hexus/ChapterSelect/Volcano/HexusChapterPreviewVolcano.h"
#include "Menus/Minigames/Hexus/OpponentSelect/HexusOpponentMenuBase.h"
#include "Menus/Minigames/Hexus/OpponentSelect/HexusOpponentPreview.h"
#include "Scenes/Hexus/Opponents/Volcano/VolcanoHexusOpponents.h"

using namespace cocos2d;

class HexusOpponentMenuVolcano : public HexusOpponentMenuBase
{
public:
	static void registerGlobalScene();

protected:
	HexusOpponentMenuVolcano();
	~HexusOpponentMenuVolcano();

private:
	static HexusOpponentMenuVolcano* instance;
};

