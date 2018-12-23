#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentKingRedsongSlime : public HexusOpponentData
{
public:
	static HexusOpponentKingRedsongSlime* getInstance();

private:
	HexusOpponentKingRedsongSlime();
	~HexusOpponentKingRedsongSlime();

	static const std::string OpponentSaveKey;
	static HexusOpponentKingRedsongSlime* instance;
};
