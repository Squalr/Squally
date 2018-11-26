#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentKingRedsongSlime : public HexusOpponentData
{
public:
	static HexusOpponentKingRedsongSlime* getInstance();

private:
	HexusOpponentKingRedsongSlime();
	~HexusOpponentKingRedsongSlime();

	static const std::string OpponentSaveKey;
	static HexusOpponentKingRedsongSlime* instance;
};
