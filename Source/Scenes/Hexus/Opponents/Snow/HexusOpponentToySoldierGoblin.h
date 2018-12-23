#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentToySoldierGoblin : public HexusOpponentData
{
public:
	static HexusOpponentToySoldierGoblin* getInstance();

private:
	HexusOpponentToySoldierGoblin();
	~HexusOpponentToySoldierGoblin();

	static const std::string OpponentSaveKey;
	static HexusOpponentToySoldierGoblin* instance;
};
