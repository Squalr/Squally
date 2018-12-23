#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentKingRedsong : public HexusOpponentData
{
public:
	static HexusOpponentKingRedsong* getInstance();

private:
	HexusOpponentKingRedsong();
	~HexusOpponentKingRedsong();

	static const std::string OpponentSaveKey;
	static HexusOpponentKingRedsong* instance;
};
