#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentPrincessMittens : public HexusOpponentData
{
public:
	static HexusOpponentPrincessMittens* getInstance();

private:
	HexusOpponentPrincessMittens();
	~HexusOpponentPrincessMittens();

	static const std::string OpponentSaveKey;
	static HexusOpponentPrincessMittens* instance;
};
