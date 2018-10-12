#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentForestOrcWarrior : public HexusOpponentData
{
public:
	static HexusOpponentForestOrcWarrior* getInstance();

private:
	HexusOpponentForestOrcWarrior();
	~HexusOpponentForestOrcWarrior();

	static const std::string StringKeyOpponentName;
	static HexusOpponentForestOrcWarrior* instance;
};
