#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentToySoldierGoblin : public HexusOpponentData
{
public:
	static HexusOpponentToySoldierGoblin* getInstance();

private:
	HexusOpponentToySoldierGoblin();
	~HexusOpponentToySoldierGoblin();

	static const std::string OpponentSaveKey;
	static HexusOpponentToySoldierGoblin* instance;
};
