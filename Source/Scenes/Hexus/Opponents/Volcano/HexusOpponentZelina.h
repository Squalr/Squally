#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentZelina : public HexusOpponentData
{
public:
	static HexusOpponentZelina* getInstance();

private:
	HexusOpponentZelina();
	~HexusOpponentZelina();

	static const std::string OpponentSaveKey;
	static HexusOpponentZelina* instance;
};
