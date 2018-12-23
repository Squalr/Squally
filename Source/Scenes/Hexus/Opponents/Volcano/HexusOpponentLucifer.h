#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentLucifer : public HexusOpponentData
{
public:
	static HexusOpponentLucifer* getInstance();

private:
	HexusOpponentLucifer();
	~HexusOpponentLucifer();

	static const std::string OpponentSaveKey;
	static HexusOpponentLucifer* instance;
};
