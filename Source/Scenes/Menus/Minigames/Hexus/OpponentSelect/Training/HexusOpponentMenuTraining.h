#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponents.h"
#include "Scenes/Menus/Minigames/Hexus/ChapterSelect/Training/HexusChapterPreviewTraining.h"
#include "Scenes/Menus/Minigames/Hexus/OpponentSelect/HexusOpponentMenuBase.h"
#include "Scenes/Menus/Minigames/Hexus/OpponentSelect/HexusOpponentPreview.h"

using namespace cocos2d;

class HexusOpponentMenuTraining : public HexusOpponentMenuBase
{
public:
	static HexusOpponentMenuTraining * create();

protected:
	HexusOpponentMenuTraining();
	~HexusOpponentMenuTraining();
};

