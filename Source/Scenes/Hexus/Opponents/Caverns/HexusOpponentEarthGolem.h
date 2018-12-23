#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentEarthGolem : public HexusOpponentData
{
public:
	static HexusOpponentEarthGolem* getInstance();

private:
	HexusOpponentEarthGolem();
	~HexusOpponentEarthGolem();

	static const std::string OpponentSaveKey;
	static HexusOpponentEarthGolem* instance;
};
