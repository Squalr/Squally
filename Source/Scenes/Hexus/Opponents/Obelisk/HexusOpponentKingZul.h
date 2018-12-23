#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentKingZul : public HexusOpponentData
{
public:
	static HexusOpponentKingZul* getInstance();

private:
	HexusOpponentKingZul();
	~HexusOpponentKingZul();

	static const std::string OpponentSaveKey;
	static HexusOpponentKingZul* instance;
};
