#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentZombieErlic : public HexusOpponentData
{
public:
	static HexusOpponentZombieErlic* getInstance();

private:
	HexusOpponentZombieErlic();
	~HexusOpponentZombieErlic();

	static const std::string StringKeyOpponentName;
	static HexusOpponentZombieErlic* instance;
};
