#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentViking : public HexusOpponentData
{
public:
	static HexusOpponentViking* getInstance();

private:
	HexusOpponentViking();
	~HexusOpponentViking();

	static const std::string OpponentSaveKey;
	static HexusOpponentViking* instance;
};
