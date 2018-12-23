#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentLeon : public HexusOpponentData
{
public:
	static HexusOpponentLeon* getInstance();

private:
	HexusOpponentLeon();
	~HexusOpponentLeon();

	static const std::string OpponentSaveKey;
	static HexusOpponentLeon* instance;
};
