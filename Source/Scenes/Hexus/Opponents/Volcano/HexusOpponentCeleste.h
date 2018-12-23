#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentCeleste : public HexusOpponentData
{
public:
	static HexusOpponentCeleste* getInstance();

private:
	HexusOpponentCeleste();
	~HexusOpponentCeleste();

	static const std::string OpponentSaveKey;
	static HexusOpponentCeleste* instance;
};
