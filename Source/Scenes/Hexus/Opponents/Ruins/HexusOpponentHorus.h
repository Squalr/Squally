#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentHorus : public HexusOpponentData
{
public:
	static HexusOpponentHorus* getInstance();

private:
	HexusOpponentHorus();
	~HexusOpponentHorus();

	static const std::string OpponentSaveKey;
	static HexusOpponentHorus* instance;
};
