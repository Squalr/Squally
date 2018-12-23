#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentKrampus : public HexusOpponentData
{
public:
	static HexusOpponentKrampus* getInstance();

private:
	HexusOpponentKrampus();
	~HexusOpponentKrampus();

	static const std::string OpponentSaveKey;
	static HexusOpponentKrampus* instance;
};
