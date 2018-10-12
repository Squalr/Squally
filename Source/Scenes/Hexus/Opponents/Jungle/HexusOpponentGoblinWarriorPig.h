#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentGoblinWarriorPig : public HexusOpponentData
{
public:
	static HexusOpponentGoblinWarriorPig* getInstance();

private:
	HexusOpponentGoblinWarriorPig();
	~HexusOpponentGoblinWarriorPig();

	static const std::string StringKeyOpponentName;
	static HexusOpponentGoblinWarriorPig* instance;
};
