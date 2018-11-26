#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentPrincessNebea : public HexusOpponentData
{
public:
	static HexusOpponentPrincessNebea* getInstance();

private:
	HexusOpponentPrincessNebea();
	~HexusOpponentPrincessNebea();

	static const std::string OpponentSaveKey;
	static HexusOpponentPrincessNebea* instance;
};
