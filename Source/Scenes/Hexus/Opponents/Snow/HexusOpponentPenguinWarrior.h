#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentPenguinWarrior : public HexusOpponentData
{
public:
	static HexusOpponentPenguinWarrior* getInstance();

private:
	HexusOpponentPenguinWarrior();
	~HexusOpponentPenguinWarrior();

	static const std::string StringKeyOpponentName;
	static HexusOpponentPenguinWarrior* instance;
};
