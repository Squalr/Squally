#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentZana : public HexusOpponentData
{
public:
	static HexusOpponentZana* getInstance();

private:
	HexusOpponentZana();
	~HexusOpponentZana();

	static const std::string OpponentSaveKey;
	static HexusOpponentZana* instance;
};
