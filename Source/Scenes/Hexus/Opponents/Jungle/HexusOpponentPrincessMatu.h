#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentPrincessMatu : public HexusOpponentData
{
public:
	static HexusOpponentPrincessMatu* getInstance();

private:
	HexusOpponentPrincessMatu();
	~HexusOpponentPrincessMatu();

	static const std::string OpponentSaveKey;
	static HexusOpponentPrincessMatu* instance;
};
