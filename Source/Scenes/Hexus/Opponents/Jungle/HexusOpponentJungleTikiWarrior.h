#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentJungleTikiWarrior : public HexusOpponentData
{
public:
	static HexusOpponentJungleTikiWarrior* getInstance();

private:
	HexusOpponentJungleTikiWarrior();
	~HexusOpponentJungleTikiWarrior();

	static const std::string StringKeyOpponentName;
	static HexusOpponentJungleTikiWarrior* instance;
};
