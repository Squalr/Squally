#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentSnowFiend : public HexusOpponentData
{
public:
	static HexusOpponentSnowFiend* getInstance();

private:
	HexusOpponentSnowFiend();
	~HexusOpponentSnowFiend();

	static const std::string OpponentSaveKey;
	static HexusOpponentSnowFiend* instance;
};
