#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentKringle : public HexusOpponentData
{
public:
	static HexusOpponentKringle* getInstance();

private:
	HexusOpponentKringle();
	~HexusOpponentKringle();

	static const std::string OpponentSaveKey;
	static HexusOpponentKringle* instance;
};
