#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentZombieErlic : public HexusOpponentData
{
public:
	static HexusOpponentZombieErlic* getInstance();

private:
	HexusOpponentZombieErlic();
	~HexusOpponentZombieErlic();

	static const std::string OpponentSaveKey;
	static HexusOpponentZombieErlic* instance;
};
