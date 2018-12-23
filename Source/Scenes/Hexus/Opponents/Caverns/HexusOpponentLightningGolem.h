#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentLightningGolem : public HexusOpponentData
{
public:
	static HexusOpponentLightningGolem* getInstance();

private:
	HexusOpponentLightningGolem();
	~HexusOpponentLightningGolem();

	static const std::string OpponentSaveKey;
	static HexusOpponentLightningGolem* instance;
};
