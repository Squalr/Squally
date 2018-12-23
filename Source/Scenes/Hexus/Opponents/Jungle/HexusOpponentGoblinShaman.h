#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentGoblinShaman : public HexusOpponentData
{
public:
	static HexusOpponentGoblinShaman* getInstance();

private:
	HexusOpponentGoblinShaman();
	~HexusOpponentGoblinShaman();

	static const std::string OpponentSaveKey;
	static HexusOpponentGoblinShaman* instance;
};
