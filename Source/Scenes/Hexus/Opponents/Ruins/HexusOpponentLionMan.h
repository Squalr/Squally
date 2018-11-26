#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentLionMan : public HexusOpponentData
{
public:
	static HexusOpponentLionMan* getInstance();

private:
	HexusOpponentLionMan();
	~HexusOpponentLionMan();

	static const std::string OpponentSaveKey;
	static HexusOpponentLionMan* instance;
};
