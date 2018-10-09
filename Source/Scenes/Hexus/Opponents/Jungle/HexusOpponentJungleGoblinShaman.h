#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentJungleGoblinShaman : public HexusOpponentData
{
public:
	static HexusOpponentJungleGoblinShaman* getInstance();

private:
	HexusOpponentJungleGoblinShaman();
	~HexusOpponentJungleGoblinShaman();

	static const std::string StringKeyOpponentName;
	static HexusOpponentJungleGoblinShaman* instance;
};
