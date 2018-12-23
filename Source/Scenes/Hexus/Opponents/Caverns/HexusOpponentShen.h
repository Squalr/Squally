#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentShen : public HexusOpponentData
{
public:
	static HexusOpponentShen* getInstance();

private:
	HexusOpponentShen();
	~HexusOpponentShen();

	static const std::string OpponentSaveKey;
	static HexusOpponentShen* instance;
};
