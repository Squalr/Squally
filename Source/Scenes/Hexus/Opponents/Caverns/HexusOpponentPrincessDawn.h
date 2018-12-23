#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentPrincessDawn : public HexusOpponentData
{
public:
	static HexusOpponentPrincessDawn* getInstance();

private:
	HexusOpponentPrincessDawn();
	~HexusOpponentPrincessDawn();

	static const std::string OpponentSaveKey;
	static HexusOpponentPrincessDawn* instance;
};
