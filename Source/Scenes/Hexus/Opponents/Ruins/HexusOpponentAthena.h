#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentAthena : public HexusOpponentData
{
public:
	static HexusOpponentAthena* getInstance();

private:
	HexusOpponentAthena();
	~HexusOpponentAthena();

	static const std::string OpponentSaveKey;
	static HexusOpponentAthena* instance;
};
