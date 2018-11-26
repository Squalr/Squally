#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentShen : public HexusOpponentData
{
public:
	static HexusOpponentShen* getInstance();

private:
	HexusOpponentShen();
	~HexusOpponentShen();

	static const std::string OpponentSaveKey;
	static HexusOpponentShen* instance;
};
