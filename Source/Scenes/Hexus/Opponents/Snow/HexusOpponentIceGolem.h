#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentIceGolem : public HexusOpponentData
{
public:
	static HexusOpponentIceGolem* getInstance();

private:
	HexusOpponentIceGolem();
	~HexusOpponentIceGolem();

	static const std::string OpponentSaveKey;
	static HexusOpponentIceGolem* instance;
};
