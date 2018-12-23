#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentBlackbeard : public HexusOpponentData
{
public:
	static HexusOpponentBlackbeard* getInstance();

private:
	HexusOpponentBlackbeard();
	~HexusOpponentBlackbeard();

	static const std::string OpponentSaveKey;
	static HexusOpponentBlackbeard* instance;
};
