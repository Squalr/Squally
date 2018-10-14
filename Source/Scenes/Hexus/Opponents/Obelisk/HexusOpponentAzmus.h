#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentAzmus : public HexusOpponentData
{
public:
	static HexusOpponentAzmus* getInstance();

private:
	HexusOpponentAzmus();
	~HexusOpponentAzmus();

	static const std::string OpponentSaveKey;
	static HexusOpponentAzmus* instance;
};
