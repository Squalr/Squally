#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentIgneus : public HexusOpponentData
{
public:
	static HexusOpponentIgneus* getInstance();

private:
	HexusOpponentIgneus();
	~HexusOpponentIgneus();

	static const std::string OpponentSaveKey;
	static HexusOpponentIgneus* instance;
};
