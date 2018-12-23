#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentForestGolem : public HexusOpponentData
{
public:
	static HexusOpponentForestGolem* getInstance();

private:
	HexusOpponentForestGolem();
	~HexusOpponentForestGolem();

	static const std::string OpponentSaveKey;
	static HexusOpponentForestGolem* instance;
};
