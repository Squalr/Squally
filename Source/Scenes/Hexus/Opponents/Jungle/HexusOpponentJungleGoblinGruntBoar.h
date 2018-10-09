#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentJungleGoblinGruntBoar : public HexusOpponentData
{
public:
	static HexusOpponentJungleGoblinGruntBoar* getInstance();

private:
	HexusOpponentJungleGoblinGruntBoar();
	~HexusOpponentJungleGoblinGruntBoar();

	static const std::string StringKeyOpponentName;
	static HexusOpponentJungleGoblinGruntBoar* instance;
};
