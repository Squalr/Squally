#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentFireElemental : public HexusOpponentData
{
public:
	static HexusOpponentFireElemental* getInstance();

private:
	HexusOpponentFireElemental();
	~HexusOpponentFireElemental();

	static const std::string OpponentSaveKey;
	static HexusOpponentFireElemental* instance;
};
