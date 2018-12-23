#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentLionMan : public HexusOpponentData
{
public:
	static HexusOpponentLionMan* getInstance();

private:
	HexusOpponentLionMan();
	~HexusOpponentLionMan();

	static const std::string OpponentSaveKey;
	static HexusOpponentLionMan* instance;
};
