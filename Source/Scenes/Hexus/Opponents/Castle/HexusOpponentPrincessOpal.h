#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentPrincessOpal : public HexusOpponentData
{
public:
	static HexusOpponentPrincessOpal* getInstance();

private:
	HexusOpponentPrincessOpal();
	~HexusOpponentPrincessOpal();

	static const std::string OpponentSaveKey;
	static HexusOpponentPrincessOpal* instance;
};
