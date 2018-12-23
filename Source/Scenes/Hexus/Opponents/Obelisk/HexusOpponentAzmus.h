#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentAzmus : public HexusOpponentData
{
public:
	static HexusOpponentAzmus* getInstance();

private:
	HexusOpponentAzmus();
	~HexusOpponentAzmus();

	static const std::string OpponentSaveKey;
	static HexusOpponentAzmus* instance;
};
