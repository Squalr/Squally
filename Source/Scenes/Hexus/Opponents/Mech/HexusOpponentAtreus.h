#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentAtreus : public HexusOpponentData
{
public:
	static HexusOpponentAtreus* getInstance();

private:
	HexusOpponentAtreus();
	~HexusOpponentAtreus();

	static const std::string OpponentSaveKey;
	static HexusOpponentAtreus* instance;
};
