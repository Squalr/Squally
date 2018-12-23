#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentCindra : public HexusOpponentData
{
public:
	static HexusOpponentCindra* getInstance();

private:
	HexusOpponentCindra();
	~HexusOpponentCindra();

	static const std::string OpponentSaveKey;
	static HexusOpponentCindra* instance;
};
