#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentKrampus : public HexusOpponentData
{
public:
	static HexusOpponentKrampus* getInstance();

private:
	HexusOpponentKrampus();
	~HexusOpponentKrampus();

	static const std::string OpponentSaveKey;
	static HexusOpponentKrampus* instance;
};
