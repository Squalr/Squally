#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentJungleGoblinWarriorPig : public HexusOpponentData
{
public:
	static HexusOpponentJungleGoblinWarriorPig* getInstance();

private:
	HexusOpponentJungleGoblinWarriorPig();
	~HexusOpponentJungleGoblinWarriorPig();

	static const std::string StringKeyOpponentName;
	static HexusOpponentJungleGoblinWarriorPig* instance;
};
