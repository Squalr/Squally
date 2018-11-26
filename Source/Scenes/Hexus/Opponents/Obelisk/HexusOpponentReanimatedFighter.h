#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentReanimatedFighter : public HexusOpponentData
{
public:
	static HexusOpponentReanimatedFighter* getInstance();

private:
	HexusOpponentReanimatedFighter();
	~HexusOpponentReanimatedFighter();

	static const std::string OpponentSaveKey;
	static HexusOpponentReanimatedFighter* instance;
};
