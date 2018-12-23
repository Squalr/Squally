#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentYeti : public HexusOpponentData
{
public:
	static HexusOpponentYeti* getInstance();

private:
	HexusOpponentYeti();
	~HexusOpponentYeti();

	static const std::string OpponentSaveKey;
	static HexusOpponentYeti* instance;
};
