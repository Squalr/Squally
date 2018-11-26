#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentAtreus : public HexusOpponentData
{
public:
	static HexusOpponentAtreus* getInstance();

private:
	HexusOpponentAtreus();
	~HexusOpponentAtreus();

	static const std::string OpponentSaveKey;
	static HexusOpponentAtreus* instance;
};
