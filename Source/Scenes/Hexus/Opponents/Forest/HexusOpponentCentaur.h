#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentCentaur : public HexusOpponentData
{
public:
	static HexusOpponentCentaur* getInstance();

private:
	HexusOpponentCentaur();
	~HexusOpponentCentaur();

	static const std::string OpponentSaveKey;
	static HexusOpponentCentaur* instance;
};
