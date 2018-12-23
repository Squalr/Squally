#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentAres : public HexusOpponentData
{
public:
	static HexusOpponentAres* getInstance();

private:
	HexusOpponentAres();
	~HexusOpponentAres();

	static const std::string OpponentSaveKey;
	static HexusOpponentAres* instance;
};
