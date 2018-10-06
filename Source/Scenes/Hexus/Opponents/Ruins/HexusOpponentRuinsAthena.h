#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentRuinsAthena : public HexusOpponentData
{
public:
	static HexusOpponentRuinsAthena* getInstance();

private:
	HexusOpponentRuinsAthena();
	~HexusOpponentRuinsAthena();

	static const std::string StringKeyOpponentName;
	static HexusOpponentRuinsAthena* instance;
};
