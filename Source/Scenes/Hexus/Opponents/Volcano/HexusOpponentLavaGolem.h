#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentLavaGolem : public HexusOpponentData
{
public:
	static HexusOpponentLavaGolem* getInstance();

private:
	HexusOpponentLavaGolem();
	~HexusOpponentLavaGolem();

	static const std::string OpponentSaveKey;
	static HexusOpponentLavaGolem* instance;
};
