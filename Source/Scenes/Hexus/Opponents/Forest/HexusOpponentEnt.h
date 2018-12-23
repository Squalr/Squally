#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentEnt : public HexusOpponentData
{
public:
	static HexusOpponentEnt* getInstance();

private:
	HexusOpponentEnt();
	~HexusOpponentEnt();

	static const std::string OpponentSaveKey;
	static HexusOpponentEnt* instance;
};
