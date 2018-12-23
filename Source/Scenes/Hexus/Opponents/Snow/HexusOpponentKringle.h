#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentKringle : public HexusOpponentData
{
public:
	static HexusOpponentKringle* getInstance();

private:
	HexusOpponentKringle();
	~HexusOpponentKringle();

	static const std::string OpponentSaveKey;
	static HexusOpponentKringle* instance;
};
