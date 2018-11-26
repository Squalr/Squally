#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentDemonRogue : public HexusOpponentData
{
public:
	static HexusOpponentDemonRogue* getInstance();

private:
	HexusOpponentDemonRogue();
	~HexusOpponentDemonRogue();

	static const std::string OpponentSaveKey;
	static HexusOpponentDemonRogue* instance;
};
