#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentJungleHades : public HexusOpponentData
{
public:
	static HexusOpponentJungleHades* getInstance();

private:
	HexusOpponentJungleHades();
	~HexusOpponentJungleHades();

	static const std::string StringKeyOpponentName;
	static HexusOpponentJungleHades* instance;
};
