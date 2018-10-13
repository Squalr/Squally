#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentDemonShaman : public HexusOpponentData
{
public:
	static HexusOpponentDemonShaman* getInstance();

private:
	HexusOpponentDemonShaman();
	~HexusOpponentDemonShaman();

	static const std::string StringKeyOpponentName;
	static HexusOpponentDemonShaman* instance;
};
