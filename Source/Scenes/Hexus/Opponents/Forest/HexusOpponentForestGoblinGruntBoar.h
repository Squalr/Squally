#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentForestGoblinGruntBoar : public HexusOpponentData
{
public:
	static HexusOpponentForestGoblinGruntBoar* getInstance();

private:
	HexusOpponentForestGoblinGruntBoar();
	~HexusOpponentForestGoblinGruntBoar();

	static const std::string StringKeyOpponentName;
	static HexusOpponentForestGoblinGruntBoar* instance;
};
