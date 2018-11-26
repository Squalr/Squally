#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentHades : public HexusOpponentData
{
public:
	static HexusOpponentHades* getInstance();

private:
	HexusOpponentHades();
	~HexusOpponentHades();

	static const std::string OpponentSaveKey;
	static HexusOpponentHades* instance;
};
