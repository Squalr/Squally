#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentReanimatedFighter : public HexusOpponentData
{
public:
	static HexusOpponentReanimatedFighter* getInstance();

private:
	HexusOpponentReanimatedFighter();
	~HexusOpponentReanimatedFighter();

	static const std::string OpponentSaveKey;
	static HexusOpponentReanimatedFighter* instance;
};
