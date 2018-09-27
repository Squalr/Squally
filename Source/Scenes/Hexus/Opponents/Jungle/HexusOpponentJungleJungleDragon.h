#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentJungleJungleDragon : public HexusOpponentData
{
public:
	static HexusOpponentJungleJungleDragon* getInstance();

private:
	HexusOpponentJungleJungleDragon();
	~HexusOpponentJungleJungleDragon();

	static const std::string StringKeyOpponentName;
	static HexusOpponentJungleJungleDragon* instance;
};
