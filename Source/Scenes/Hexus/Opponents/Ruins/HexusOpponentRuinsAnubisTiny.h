#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentRuinsAnubisTiny : public HexusOpponentData
{
public:
	static HexusOpponentRuinsAnubisTiny* getInstance();

private:
	HexusOpponentRuinsAnubisTiny();
	~HexusOpponentRuinsAnubisTiny();

	static const std::string StringKeyOpponentName;
	static HexusOpponentRuinsAnubisTiny* instance;
};
