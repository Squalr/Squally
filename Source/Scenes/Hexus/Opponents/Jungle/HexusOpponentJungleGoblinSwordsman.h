#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentJungleGoblinSwordsman : public HexusOpponentData
{
public:
	static HexusOpponentJungleGoblinSwordsman* getInstance();

private:
	HexusOpponentJungleGoblinSwordsman();
	~HexusOpponentJungleGoblinSwordsman();

	static const std::string StringKeyOpponentName;
	static HexusOpponentJungleGoblinSwordsman* instance;
};
