#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentRoboGolem : public HexusOpponentData
{
public:
	static HexusOpponentRoboGolem* getInstance();

private:
	HexusOpponentRoboGolem();
	~HexusOpponentRoboGolem();

	static const std::string OpponentSaveKey;
	static HexusOpponentRoboGolem* instance;
};
