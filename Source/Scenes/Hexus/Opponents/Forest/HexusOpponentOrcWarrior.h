#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentOrcWarrior : public HexusOpponentData
{
public:
	static HexusOpponentOrcWarrior* getInstance();

private:
	HexusOpponentOrcWarrior();
	~HexusOpponentOrcWarrior();

	static const std::string OpponentSaveKey;
	static HexusOpponentOrcWarrior* instance;
};
