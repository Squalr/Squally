#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


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
