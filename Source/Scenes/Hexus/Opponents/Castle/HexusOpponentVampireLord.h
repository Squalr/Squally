#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentVampireLord : public HexusOpponentData
{
public:
	static HexusOpponentVampireLord* getInstance();

private:
	HexusOpponentVampireLord();
	~HexusOpponentVampireLord();

	static const std::string OpponentSaveKey;
	static HexusOpponentVampireLord* instance;
};
