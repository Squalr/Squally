#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentDemonShaman : public HexusOpponentData
{
public:
	static HexusOpponentDemonShaman* getInstance();

private:
	HexusOpponentDemonShaman();
	~HexusOpponentDemonShaman();

	static const std::string OpponentSaveKey;
	static HexusOpponentDemonShaman* instance;
};
