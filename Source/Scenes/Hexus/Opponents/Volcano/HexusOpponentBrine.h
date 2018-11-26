#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentBrine : public HexusOpponentData
{
public:
	static HexusOpponentBrine* getInstance();

private:
	HexusOpponentBrine();
	~HexusOpponentBrine();

	static const std::string OpponentSaveKey;
	static HexusOpponentBrine* instance;
};
