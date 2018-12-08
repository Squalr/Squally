#pragma once
#include "cocos2d.h"

#include "Menus/Minigames/Hexus/ChapterSelect/Castle/HexusChapterPreviewCastle.h"
#include "Menus/Minigames/Hexus/OpponentSelect/HexusOpponentMenuBase.h"
#include "Menus/Minigames/Hexus/OpponentSelect/HexusOpponentPreview.h"
#include "Scenes/Hexus/Opponents/Castle/CastleHexusOpponents.h"

using namespace cocos2d;

class HexusOpponentMenuCastle : public HexusOpponentMenuBase
{
public:
	static void registerGlobalScene();

protected:
	HexusOpponentMenuCastle();
	~HexusOpponentMenuCastle();

private:
	static HexusOpponentMenuCastle* instance;
};

