#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentPrincessPepper : public HexusOpponentData
{
public:
	static HexusOpponentPrincessPepper* getInstance();

private:
	HexusOpponentPrincessPepper();
	~HexusOpponentPrincessPepper();

	static const std::string OpponentSaveKey;
	static HexusOpponentPrincessPepper* instance;
};
