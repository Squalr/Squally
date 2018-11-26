#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentAsmodeus : public HexusOpponentData
{
public:
	static HexusOpponentAsmodeus* getInstance();

private:
	HexusOpponentAsmodeus();
	~HexusOpponentAsmodeus();

	static const std::string OpponentSaveKey;
	static HexusOpponentAsmodeus* instance;
};
