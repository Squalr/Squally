#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentPrincessPepper : public HexusOpponentData
{
public:
	static HexusOpponentPrincessPepper* getInstance();

private:
	HexusOpponentPrincessPepper();
	~HexusOpponentPrincessPepper();

	static const std::string StringKeyOpponentName;
	static HexusOpponentPrincessPepper* instance;
};
