#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentKingGrogg : public HexusOpponentData
{
public:
	static HexusOpponentKingGrogg* getInstance();

private:
	HexusOpponentKingGrogg();
	~HexusOpponentKingGrogg();

	static const std::string OpponentSaveKey;
	static HexusOpponentKingGrogg* instance;
};
