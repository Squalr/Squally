#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentPoseidon : public HexusOpponentData
{
public:
	static HexusOpponentPoseidon* getInstance();

private:
	HexusOpponentPoseidon();
	~HexusOpponentPoseidon();

	static const std::string OpponentSaveKey;
	static HexusOpponentPoseidon* instance;
};
