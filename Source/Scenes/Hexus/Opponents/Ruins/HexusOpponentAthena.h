#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentAthena : public HexusOpponentData
{
public:
	static HexusOpponentAthena* getInstance();

private:
	HexusOpponentAthena();
	~HexusOpponentAthena();

	static const std::string OpponentSaveKey;
	static HexusOpponentAthena* instance;
};
