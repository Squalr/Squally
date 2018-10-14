#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentViking : public HexusOpponentData
{
public:
	static HexusOpponentViking* getInstance();

private:
	HexusOpponentViking();
	~HexusOpponentViking();

	static const std::string OpponentSaveKey;
	static HexusOpponentViking* instance;
};
