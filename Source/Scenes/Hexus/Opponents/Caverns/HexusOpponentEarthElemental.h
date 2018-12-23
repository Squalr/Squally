#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentEarthElemental : public HexusOpponentData
{
public:
	static HexusOpponentEarthElemental* getInstance();

private:
	HexusOpponentEarthElemental();
	~HexusOpponentEarthElemental();

	static const std::string OpponentSaveKey;
	static HexusOpponentEarthElemental* instance;
};
