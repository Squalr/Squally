#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentRuinsTigerMan : public HexusOpponentData
{
public:
	static HexusOpponentRuinsTigerMan* getInstance();

private:
	HexusOpponentRuinsTigerMan();
	~HexusOpponentRuinsTigerMan();

	static const std::string StringKeyOpponentName;
	static HexusOpponentRuinsTigerMan* instance;
};
