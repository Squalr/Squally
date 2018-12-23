#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentMummyPriest : public HexusOpponentData
{
public:
	static HexusOpponentMummyPriest* getInstance();

private:
	HexusOpponentMummyPriest();
	~HexusOpponentMummyPriest();

	static const std::string OpponentSaveKey;
	static HexusOpponentMummyPriest* instance;
};
