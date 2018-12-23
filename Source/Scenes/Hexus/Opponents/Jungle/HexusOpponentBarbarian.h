#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentBarbarian : public HexusOpponentData
{
public:
	static HexusOpponentBarbarian* getInstance();

private:
	HexusOpponentBarbarian();
	~HexusOpponentBarbarian();

	static const std::string OpponentSaveKey;
	static HexusOpponentBarbarian* instance;
};
