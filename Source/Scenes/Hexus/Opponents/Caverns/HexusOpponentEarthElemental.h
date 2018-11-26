#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentEarthElemental : public HexusOpponentData
{
public:
	static HexusOpponentEarthElemental* getInstance();

private:
	HexusOpponentEarthElemental();
	~HexusOpponentEarthElemental();

	static const std::string OpponentSaveKey;
	static HexusOpponentEarthElemental* instance;
};
