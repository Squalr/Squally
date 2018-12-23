#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentZombie : public HexusOpponentData
{
public:
	static HexusOpponentZombie* getInstance();

private:
	HexusOpponentZombie();
	~HexusOpponentZombie();

	static const std::string OpponentSaveKey;
	static HexusOpponentZombie* instance;
};
