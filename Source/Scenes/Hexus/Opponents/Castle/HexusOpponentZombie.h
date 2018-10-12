#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentZombie : public HexusOpponentData
{
public:
	static HexusOpponentZombie* getInstance();

private:
	HexusOpponentZombie();
	~HexusOpponentZombie();

	static const std::string StringKeyOpponentName;
	static HexusOpponentZombie* instance;
};
