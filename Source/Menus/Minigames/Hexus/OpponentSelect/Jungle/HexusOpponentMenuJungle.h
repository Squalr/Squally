#pragma once
#include "cocos2d.h"

#include "Menus/Minigames/Hexus/ChapterSelect/Jungle/HexusChapterPreviewJungle.h"
#include "Menus/Minigames/Hexus/OpponentSelect/HexusOpponentMenuBase.h"
#include "Menus/Minigames/Hexus/OpponentSelect/HexusOpponentPreview.h"
#include "Scenes/Hexus/Opponents/Jungle/JungleHexusOpponents.h"

using namespace cocos2d;

class HexusOpponentMenuJungle : public HexusOpponentMenuBase
{
public:
	static void registerGlobalScene();

protected:
	HexusOpponentMenuJungle();
	~HexusOpponentMenuJungle();

private:
	static HexusOpponentMenuJungle* instance;
};

