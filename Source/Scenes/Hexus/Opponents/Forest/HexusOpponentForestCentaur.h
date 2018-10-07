#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentForestCentaur : public HexusOpponentData
{
public:
	static HexusOpponentForestCentaur* getInstance();

private:
	HexusOpponentForestCentaur();
	~HexusOpponentForestCentaur();

	static const std::string StringKeyOpponentName;
	static HexusOpponentForestCentaur* instance;
};
