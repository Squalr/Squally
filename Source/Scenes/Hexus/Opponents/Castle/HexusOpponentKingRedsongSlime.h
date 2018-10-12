#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentKingRedsongSlime : public HexusOpponentData
{
public:
	static HexusOpponentKingRedsongSlime* getInstance();

private:
	HexusOpponentKingRedsongSlime();
	~HexusOpponentKingRedsongSlime();

	static const std::string StringKeyOpponentName;
	static HexusOpponentKingRedsongSlime* instance;
};
