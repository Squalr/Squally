#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentJungleGoblinGrunt : public HexusOpponentData
{
public:
	static HexusOpponentJungleGoblinGrunt* getInstance();

private:
	HexusOpponentJungleGoblinGrunt();
	~HexusOpponentJungleGoblinGrunt();

	static const std::string StringKeyOpponentName;
	static HexusOpponentJungleGoblinGrunt* instance;
};
