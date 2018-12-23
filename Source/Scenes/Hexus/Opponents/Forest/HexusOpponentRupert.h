#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentRupert : public HexusOpponentData
{
public:
	static HexusOpponentRupert* getInstance();

private:
	HexusOpponentRupert();
	~HexusOpponentRupert();

	static const std::string OpponentSaveKey;
	static HexusOpponentRupert* instance;
};
