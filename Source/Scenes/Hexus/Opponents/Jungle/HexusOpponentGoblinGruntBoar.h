#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentGoblinGruntBoar : public HexusOpponentData
{
public:
	static HexusOpponentGoblinGruntBoar* getInstance();

private:
	HexusOpponentGoblinGruntBoar();
	~HexusOpponentGoblinGruntBoar();

	static const std::string StringKeyOpponentName;
	static HexusOpponentGoblinGruntBoar* instance;
};
