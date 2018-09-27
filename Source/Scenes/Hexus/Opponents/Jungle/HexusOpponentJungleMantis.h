#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentJungleMantis : public HexusOpponentData
{
public:
	static HexusOpponentJungleMantis* getInstance();

private:
	HexusOpponentJungleMantis();
	~HexusOpponentJungleMantis();

	static const std::string StringKeyOpponentName;
	static HexusOpponentJungleMantis* instance;
};
