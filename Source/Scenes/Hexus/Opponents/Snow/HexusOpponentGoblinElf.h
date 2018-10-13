#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentGoblinElf : public HexusOpponentData
{
public:
	static HexusOpponentGoblinElf* getInstance();

private:
	HexusOpponentGoblinElf();
	~HexusOpponentGoblinElf();

	static const std::string StringKeyOpponentName;
	static HexusOpponentGoblinElf* instance;
};
