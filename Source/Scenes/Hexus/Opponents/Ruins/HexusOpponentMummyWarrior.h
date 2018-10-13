#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentMummyWarrior : public HexusOpponentData
{
public:
	static HexusOpponentMummyWarrior* getInstance();

private:
	HexusOpponentMummyWarrior();
	~HexusOpponentMummyWarrior();

	static const std::string StringKeyOpponentName;
	static HexusOpponentMummyWarrior* instance;
};
