#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentAnubisWarrior : public HexusOpponentData
{
public:
	static HexusOpponentAnubisWarrior* getInstance();

private:
	HexusOpponentAnubisWarrior();
	~HexusOpponentAnubisWarrior();

	static const std::string OpponentSaveKey;
	static HexusOpponentAnubisWarrior* instance;
};
