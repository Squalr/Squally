#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentAres : public HexusOpponentData
{
public:
	static HexusOpponentAres* getInstance();

private:
	HexusOpponentAres();
	~HexusOpponentAres();

	static const std::string OpponentSaveKey;
	static HexusOpponentAres* instance;
};
