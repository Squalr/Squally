#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentMabel : public HexusOpponentData
{
public:
	static HexusOpponentMabel* getInstance();

private:
	HexusOpponentMabel();
	~HexusOpponentMabel();

	static const std::string OpponentSaveKey;
	static HexusOpponentMabel* instance;
};
