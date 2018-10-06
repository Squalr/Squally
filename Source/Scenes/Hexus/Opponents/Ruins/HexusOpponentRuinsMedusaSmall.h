#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentRuinsMedusaSmall : public HexusOpponentData
{
public:
	static HexusOpponentRuinsMedusaSmall* getInstance();

private:
	HexusOpponentRuinsMedusaSmall();
	~HexusOpponentRuinsMedusaSmall();

	static const std::string StringKeyOpponentName;
	static HexusOpponentRuinsMedusaSmall* instance;
};
