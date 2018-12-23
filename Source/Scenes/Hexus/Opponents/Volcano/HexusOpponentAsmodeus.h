#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentAsmodeus : public HexusOpponentData
{
public:
	static HexusOpponentAsmodeus* getInstance();

private:
	HexusOpponentAsmodeus();
	~HexusOpponentAsmodeus();

	static const std::string OpponentSaveKey;
	static HexusOpponentAsmodeus* instance;
};
