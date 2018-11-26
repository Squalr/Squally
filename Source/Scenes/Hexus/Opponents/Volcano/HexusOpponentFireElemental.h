#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentFireElemental : public HexusOpponentData
{
public:
	static HexusOpponentFireElemental* getInstance();

private:
	HexusOpponentFireElemental();
	~HexusOpponentFireElemental();

	static const std::string OpponentSaveKey;
	static HexusOpponentFireElemental* instance;
};
