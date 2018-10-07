#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentForestTroll : public HexusOpponentData
{
public:
	static HexusOpponentForestTroll* getInstance();

private:
	HexusOpponentForestTroll();
	~HexusOpponentForestTroll();

	static const std::string StringKeyOpponentName;
	static HexusOpponentForestTroll* instance;
};
