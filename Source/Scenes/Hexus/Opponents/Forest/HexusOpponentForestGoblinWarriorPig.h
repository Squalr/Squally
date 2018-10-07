#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentForestGoblinWarriorPig : public HexusOpponentData
{
public:
	static HexusOpponentForestGoblinWarriorPig* getInstance();

private:
	HexusOpponentForestGoblinWarriorPig();
	~HexusOpponentForestGoblinWarriorPig();

	static const std::string StringKeyOpponentName;
	static HexusOpponentForestGoblinWarriorPig* instance;
};
