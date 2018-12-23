#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentShaman : public HexusOpponentData
{
public:
	static HexusOpponentShaman* getInstance();

private:
	HexusOpponentShaman();
	~HexusOpponentShaman();

	static const std::string OpponentSaveKey;
	static HexusOpponentShaman* instance;
};
