#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentGoblinGruntBoar : public HexusOpponentData
{
public:
	static HexusOpponentGoblinGruntBoar* getInstance();

private:
	HexusOpponentGoblinGruntBoar();
	~HexusOpponentGoblinGruntBoar();

	static const std::string OpponentSaveKey;
	static HexusOpponentGoblinGruntBoar* instance;
};
