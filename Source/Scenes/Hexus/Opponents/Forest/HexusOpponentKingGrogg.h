#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentKingGrogg : public HexusOpponentData
{
public:
	static HexusOpponentKingGrogg* getInstance();

private:
	HexusOpponentKingGrogg();
	~HexusOpponentKingGrogg();

	static const std::string OpponentSaveKey;
	static HexusOpponentKingGrogg* instance;
};
