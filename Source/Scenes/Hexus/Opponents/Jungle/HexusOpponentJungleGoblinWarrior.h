#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentJungleGoblinWarrior : public HexusOpponentData
{
public:
	static HexusOpponentJungleGoblinWarrior* getInstance();

private:
	HexusOpponentJungleGoblinWarrior();
	~HexusOpponentJungleGoblinWarrior();

	static const std::string StringKeyOpponentName;
	static HexusOpponentJungleGoblinWarrior* instance;
};
