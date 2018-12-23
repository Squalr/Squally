#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentPrincessOpal : public HexusOpponentData
{
public:
	static HexusOpponentPrincessOpal* getInstance();

private:
	HexusOpponentPrincessOpal();
	~HexusOpponentPrincessOpal();

	static const std::string OpponentSaveKey;
	static HexusOpponentPrincessOpal* instance;
};
