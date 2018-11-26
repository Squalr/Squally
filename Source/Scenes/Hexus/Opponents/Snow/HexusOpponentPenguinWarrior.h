#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentPenguinWarrior : public HexusOpponentData
{
public:
	static HexusOpponentPenguinWarrior* getInstance();

private:
	HexusOpponentPenguinWarrior();
	~HexusOpponentPenguinWarrior();

	static const std::string OpponentSaveKey;
	static HexusOpponentPenguinWarrior* instance;
};
