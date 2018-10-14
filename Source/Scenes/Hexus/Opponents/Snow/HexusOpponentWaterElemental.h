#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentWaterElemental : public HexusOpponentData
{
public:
	static HexusOpponentWaterElemental* getInstance();

private:
	HexusOpponentWaterElemental();
	~HexusOpponentWaterElemental();

	static const std::string OpponentSaveKey;
	static HexusOpponentWaterElemental* instance;
};
