#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentScarecrow : public HexusOpponentData
{
public:
	static HexusOpponentScarecrow* getInstance();

private:
	HexusOpponentScarecrow();
	~HexusOpponentScarecrow();

	static const std::string OpponentSaveKey;
	static HexusOpponentScarecrow* instance;
};
