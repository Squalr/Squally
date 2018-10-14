#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentPrincessDawn : public HexusOpponentData
{
public:
	static HexusOpponentPrincessDawn* getInstance();

private:
	HexusOpponentPrincessDawn();
	~HexusOpponentPrincessDawn();

	static const std::string OpponentSaveKey;
	static HexusOpponentPrincessDawn* instance;
};
