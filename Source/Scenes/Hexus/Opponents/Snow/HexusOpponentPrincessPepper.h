#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentPrincessPepper : public HexusOpponentData
{
public:
	static HexusOpponentPrincessPepper* getInstance();

private:
	HexusOpponentPrincessPepper();
	~HexusOpponentPrincessPepper();

	static const std::string OpponentSaveKey;
	static HexusOpponentPrincessPepper* instance;
};
