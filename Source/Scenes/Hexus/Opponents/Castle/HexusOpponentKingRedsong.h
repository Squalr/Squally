#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentKingRedsong : public HexusOpponentData
{
public:
	static HexusOpponentKingRedsong* getInstance();

private:
	HexusOpponentKingRedsong();
	~HexusOpponentKingRedsong();

	static const std::string OpponentSaveKey;
	static HexusOpponentKingRedsong* instance;
};
