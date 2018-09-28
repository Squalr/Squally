#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponents.h"
#include "Scenes/Menus/Minigames/Hexus/OpponentSelect/HexusOpponentMenuBase.h"
#include "Scenes/Menus/Minigames/Hexus/OpponentSelect/HexusOpponentPreview.h"

using namespace cocos2d;

class HexusOpponentMenuMech : public HexusOpponentMenuBase
{
public:
	static HexusOpponentMenuMech * create();

protected:
	HexusOpponentMenuMech();
	~HexusOpponentMenuMech();

private:
	static const std::string StringKeyProgressSave;
};

