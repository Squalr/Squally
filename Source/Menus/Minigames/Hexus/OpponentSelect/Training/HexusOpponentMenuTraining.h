#pragma once
#include "cocos2d.h"

#include "Menus/Minigames/Hexus/ChapterSelect/Training/HexusChapterPreviewTraining.h"
#include "Menus/Minigames/Hexus/OpponentSelect/HexusOpponentMenuBase.h"
#include "Menus/Minigames/Hexus/OpponentSelect/HexusOpponentPreview.h"
#include "Resources.h"
#include "Scenes/Hexus/Opponents/Tutorial/TutorialHexusOpponents.h"

using namespace cocos2d;

class HexusOpponentMenuTraining : public HexusOpponentMenuBase
{
public:
	static HexusOpponentMenuTraining * create();

protected:
	HexusOpponentMenuTraining();
	~HexusOpponentMenuTraining();
};

