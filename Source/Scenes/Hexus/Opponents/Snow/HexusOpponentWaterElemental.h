#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentWaterElemental : public HexusOpponentData
{
public:
	static HexusOpponentWaterElemental* getInstance();

private:
	HexusOpponentWaterElemental();
	~HexusOpponentWaterElemental();

	static const std::string OpponentSaveKey;
	static HexusOpponentWaterElemental* instance;
};
