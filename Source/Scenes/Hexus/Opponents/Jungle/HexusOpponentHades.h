#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentHades : public HexusOpponentData
{
public:
	static HexusOpponentHades* getInstance();

private:
	HexusOpponentHades();
	~HexusOpponentHades();

	static const std::string OpponentSaveKey;
	static HexusOpponentHades* instance;
};
