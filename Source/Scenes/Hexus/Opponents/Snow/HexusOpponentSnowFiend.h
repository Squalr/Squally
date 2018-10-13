#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentSnowFiend : public HexusOpponentData
{
public:
	static HexusOpponentSnowFiend* getInstance();

private:
	HexusOpponentSnowFiend();
	~HexusOpponentSnowFiend();

	static const std::string StringKeyOpponentName;
	static HexusOpponentSnowFiend* instance;
};
