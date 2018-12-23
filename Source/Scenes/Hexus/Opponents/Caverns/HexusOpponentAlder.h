#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentAlder : public HexusOpponentData
{
public:
	static HexusOpponentAlder* getInstance();

private:
	HexusOpponentAlder();
	~HexusOpponentAlder();

	static const std::string OpponentSaveKey;
	static HexusOpponentAlder* instance;
};
