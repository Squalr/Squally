#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentYetiWarrior : public HexusOpponentData
{
public:
	static HexusOpponentYetiWarrior* getInstance();

private:
	HexusOpponentYetiWarrior();
	~HexusOpponentYetiWarrior();

	static const std::string StringKeyOpponentName;
	static HexusOpponentYetiWarrior* instance;
};
