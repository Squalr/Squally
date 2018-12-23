#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentAbomination : public HexusOpponentData
{
public:
	static HexusOpponentAbomination* getInstance();

private:
	HexusOpponentAbomination();
	~HexusOpponentAbomination();

	static const std::string OpponentSaveKey;
	static HexusOpponentAbomination* instance;
};
