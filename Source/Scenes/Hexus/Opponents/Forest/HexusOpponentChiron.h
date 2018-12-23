#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentChiron : public HexusOpponentData
{
public:
	static HexusOpponentChiron* getInstance();

private:
	HexusOpponentChiron();
	~HexusOpponentChiron();

	static const std::string OpponentSaveKey;
	static HexusOpponentChiron* instance;
};
