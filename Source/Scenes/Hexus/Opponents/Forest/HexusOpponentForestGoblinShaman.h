#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentForestGoblinShaman : public HexusOpponentData
{
public:
	static HexusOpponentForestGoblinShaman* getInstance();

private:
	HexusOpponentForestGoblinShaman();
	~HexusOpponentForestGoblinShaman();

	static const std::string StringKeyOpponentName;
	static HexusOpponentForestGoblinShaman* instance;
};
