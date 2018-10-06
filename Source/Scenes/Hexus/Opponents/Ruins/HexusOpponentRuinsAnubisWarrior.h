#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentRuinsAnubisWarrior : public HexusOpponentData
{
public:
	static HexusOpponentRuinsAnubisWarrior* getInstance();

private:
	HexusOpponentRuinsAnubisWarrior();
	~HexusOpponentRuinsAnubisWarrior();

	static const std::string StringKeyOpponentName;
	static HexusOpponentRuinsAnubisWarrior* instance;
};
