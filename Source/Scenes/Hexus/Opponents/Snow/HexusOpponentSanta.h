#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentSanta : public HexusOpponentData
{
public:
	static HexusOpponentSanta* getInstance();

private:
	HexusOpponentSanta();
	~HexusOpponentSanta();

	static const std::string OpponentSaveKey;
	static HexusOpponentSanta* instance;
};
