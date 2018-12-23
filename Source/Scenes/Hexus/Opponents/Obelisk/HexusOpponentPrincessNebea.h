#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentPrincessNebea : public HexusOpponentData
{
public:
	static HexusOpponentPrincessNebea* getInstance();

private:
	HexusOpponentPrincessNebea();
	~HexusOpponentPrincessNebea();

	static const std::string OpponentSaveKey;
	static HexusOpponentPrincessNebea* instance;
};
