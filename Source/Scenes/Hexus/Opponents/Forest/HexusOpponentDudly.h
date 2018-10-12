#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentForestEnt : public HexusOpponentData
{
public:
	static HexusOpponentForestEnt* getInstance();

private:
	HexusOpponentForestEnt();
	~HexusOpponentForestEnt();

	static const std::string StringKeyOpponentName;
	static HexusOpponentForestEnt* instance;
};
