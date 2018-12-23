#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentScaldor : public HexusOpponentData
{
public:
	static HexusOpponentScaldor* getInstance();

private:
	HexusOpponentScaldor();
	~HexusOpponentScaldor();

	static const std::string OpponentSaveKey;
	static HexusOpponentScaldor* instance;
};
