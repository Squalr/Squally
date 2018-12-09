#pragma once
#include "cocos2d.h"

#include "Menus/Minigames/Hexus/ChapterSelect/IceCaps/HexusChapterPreviewIceCaps.h"
#include "Menus/Minigames/Hexus/OpponentSelect/HexusOpponentMenuBase.h"
#include "Menus/Minigames/Hexus/OpponentSelect/HexusOpponentPreview.h"
#include "Scenes/Hexus/Opponents/Snow/SnowHexusOpponents.h"

using namespace cocos2d;

class HexusOpponentMenuIceCaps : public HexusOpponentMenuBase
{
public:
	static void registerGlobalScene();

protected:
	HexusOpponentMenuIceCaps();
	~HexusOpponentMenuIceCaps();

private:
	static HexusOpponentMenuIceCaps* instance;
};

