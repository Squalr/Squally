#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentMabel : public HexusOpponentData
{
public:
	static HexusOpponentMabel* getInstance();

private:
	HexusOpponentMabel();
	~HexusOpponentMabel();

	static const std::string OpponentSaveKey;
	static HexusOpponentMabel* instance;
};
