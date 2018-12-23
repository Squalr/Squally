#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentAnubisPup : public HexusOpponentData
{
public:
	static HexusOpponentAnubisPup* getInstance();

private:
	HexusOpponentAnubisPup();
	~HexusOpponentAnubisPup();

	static const std::string OpponentSaveKey;
	static HexusOpponentAnubisPup* instance;
};
